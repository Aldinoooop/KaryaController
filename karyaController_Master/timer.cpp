#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "common.h"

#ifndef ESP8266
#include "timer.h"
#include "freertos/FreeRTOS.h"  // Untuk RTOS support di ESP32
#include "driver/timer.h"       // Untuk menggunakan hardware timer di ESP32
// #include <esp_task_wdt.h>

hw_timer_t *timer1 = NULL;
hw_timer_t *timer2 = NULL;
#endif

// esp_task_wdt_config_t wdt_config = {
//   .timeout_ms = 2000000,      // 2-second timeout
//   .idle_core_mask = 0x03,  // Monitor both Core 0 and Core 1
//   .trigger_panic = false   // Trigger a panic on timeout
// };



// timer_t *timer1 = NULL;
// timer_t *timer2 = NULL;

// #endif








uint32_t lT = 0;

long spindle_pwm = 0;
int min_pwm_clock = 0;  // 2us to turn on anything
int zerocrosspin;
bool TOOLON = HIGH;
bool TOOLONS[3];
//#define motorz_servo
#ifdef motorz_servo
#define motorz_servo_pin zstep
long motorz_pwm = 0;
// range 50mm, mean pwm pulse 1ms = -25 1.5=0 2ms = 2.5
float motorz_zero = 0;  // actual position must be added with this, when job start, must be set
#define motorz_range 50.0
#define motorz_range_min -(motorz_range / 2)
#define motorz_range_max (motorz_range / 2)


uint32_t nextz_l;
bool motorz_servo_state = LOW;
#endif


extern int lastS;
bool RPM_PID_MODE = false;


#ifdef RPM_COUNTER

#include "pid.h"
double rSetpoint, rInput, rOutput;

//Specify the links and initial tuning parameters

PID RPM_PID(&rInput, &rOutput, &rSetpoint, 8, 2, 12, DIRECT);  //2, 5, 1, DIRECT);

uint32_t rev = 0;
uint32_t lastMillis = 0;
uint32_t RPM = 0;
int avgpw = 0;
int avgcnt = 0;
void THEISR isr_RPM() {
  rev++;
}

uint32_t get_RPM() {
  uint32_t milli = millis();
  uint32_t delta = milli - lastMillis;
  if (delta > 100) {
    lastMillis = milli;
    RPM = (rev * 60 * 1000 / delta);
    rev = 0;
    if (RPM_PID_MODE) {
      rSetpoint = lastS * 100;
      rInput = RPM;
      RPM_PID.Compute();
      if (lastS == 0) rOutput = 0;
      avgpw = (avgpw + rOutput * 0.01);
      avgcnt++;
#ifdef AC_SPINDLE
      spindle_pwm = 10000 - pow(rOutput * 0.0001, 2) * 10000;
#else
      spindle_pwm = rOutput;
#endif
    }
  }
  return RPM;
}
void setup_RPM() {
  attachInterrupt(digitalPinToInterrupt(RPM_COUNTER), isr_RPM, RISING);
  lastMillis = millis();
  RPM_PID.SetMode(AUTOMATIC);
  RPM_PID.SetOutputLimits(0, 10000);
}

#endif



uint32_t next_l = 0;
bool spindle_state = LOW;
int spindle_pct;

//PWM Freq is 1000000/20000 = 50Hz , 20mms pulse
// for servo, the LSCALE at least 10%

#define FREQPWM 400

int X9pos = 100;


#define PERIODPWM (1000000 / FREQPWM)
#define BYTETOPERIOD PERIODPWM / 255
#define PERIODTOPCA (180 / PERIODPWM)



bool in_pwm_loop = false;

void set_tool(int v) {
  extern int lasermode, uncompress;
  if (uncompress && v == 0 && lasermode == 0) v = 255;  // make sure its running when running job on router
  if (v > 255) v = 255;
  if (v < 0) v = 0;
  laserOn = v > 0;
  //

  // turn on tool pwm pin != tool pin
  if (pwm_pin != atool_pin && !uncompress) {
    TOOL1((laserOn && lasermode != 1 ? TOOLON : !TOOLON));
  }
  constantlaserVal = v;
  lastS = v;
  digitalWrite(atool_pin,v>0);
}

void set_toolx(int v) {  // 0-255
  /*  
  if (v > 255)v = 255;
  if (v < 0)v = 0;
#ifdef PLASMA_MODE
	// no need pwm for plasma
	if (v > 10)v = 255;
	xdigitalWrite(spindle_pin,v>10);
	lastS = v;
#else  
	  next_l = micros();
	  {
		spindle_pct = v * 0.3922; // 0 - 100
		//if (! RPM_PID_MODE)
		lastS = v;
		extern float Lscale;
		float vf;
		if (int(100 * Lscale) == 0) {
		  vf = v > 5 ? 255 : 0;
		} else {
		  vf = fabs(v * Lscale);
		}
	      #ifdef pinX9C
	      extern void IR_end();
	      extern void IR_setup();
		    int newX9pos=spindle_pct;
		    if (newX9pos!=X9pos){
		      IR_end();

		    // set direction
		      int np=newX9pos;
		      newX9pos=(newX9pos==0?-100:X9pos);
		      
		      X9pos=np;
		      pinMode(pinX9C,OUTPUT);
		      xdigitalWrite(pinX9C,newX9pos>0?1:0);
		      #ifdef spindle_pin
		      #define pot_pin spindle_pin
		      #elif defined(laser_pin)
		      #define pot_pin laser_pin
		      #endif
		      somedelay(1);
		      pinMode(pot_pin,OUTPUT);
		      
		      
		      for (int i=abs(newX9pos);i>0;i--){
			// step the potensio
			xdigitalWrite(pot_pin,1);
			somedelay(1);
			xdigitalWrite(pot_pin,0);			
			somedelay(1);
		      }
		      IR_setup();
		    }
	      #else
		spindle_pwm = fmin(PERIODPWM, vf * BYTETOPERIOD);
		if (Lscale >= 0)spindle_pwm = PERIODPWM - spindle_pwm; // flip if inverse
		spindle_state = LOW;
		#ifdef spindle_pin
			xdigitalWrite(spindle_pin, v>10);
		#endif
	      #endif
	  
	#ifdef PCA9685
		pwm.setPWM(spindle_servo_pin, 0, pulseWidth(spindle_pwm * PERIODTOPCA)); // set 0 - 4095
		return;
	#endif
	  }
	  if (in_pwm_loop)return;
	#ifdef spindle_pin
	  pinMode(spindle_pin, OUTPUT);
	  //xdigitalWrite(spindle_pin, HIGH);
	#endif
#endif
*/
}
void pause_pwm(bool v) {
  in_pwm_loop = v;
}

void THEISR pwm_loop() {
  /*
#ifndef PLASMA_MODE
	#ifdef RPM_COUNTER
	  get_RPM();
	#endif
	if (in_pwm_loop)return;
	in_pwm_loop = true;



	uint32_t pwmc = micros(); // next_l contain last time target for 50Hz
	#if defined(spindle_pin) && !defined(pinX9C)
	    if (!spindle_state && (pwmc - next_l > spindle_pwm)  && (spindle_pwm < PERIODPWM)) { // if  current time - next time > delta time pwm, then turn it on
		  spindle_state = HIGH;
		  xdigitalWrite(spindle_pin, HIGH);
	    }

	    // if use zero_cross then in_pwm_loop will be true until a trigger happened
	    // basically replace all below using interrupt trigger
	  #ifndef ZERO_CROSS_PIN
	    if (pwmc - next_l >= PERIODPWM) { // 50hz on wemos then turn off
		  next_l = pwmc;
		  spindle_state = LOW;
		  xdigitalWrite(spindle_pin, LOW);
	    }
	  #endif
	#endif
	/*
	#ifdef motorz_servo
	    if (!motorz_servo_state && (pwmc - nextz_l > motorz_pwm)) { // if  current time - next time > delta time pwm, then turn it on
		  motorz_servo_state = HIGH;
		  xdigitalWrite(motorz_servo_pin, !HIGH);
	    }
	    if (pwmc - nextz_l > 19999) { // 50hz on wemos then turn off
		  nextz_l = pwmc;
		  motorz_servo_state = LOW;
		  xdigitalWrite(motorz_servo_pin, !LOW);
		  // update motor z pwm / position
		  float cz = info_z_s * perstepz+motorz_zero;
		  if (cz<motorz_range_min)cz=motorz_range_min;
		  if (cz>motorz_range_max)cz=motorz_range_max;
		  // map to pwm 1ms to 2ms
		  motorz_pwm =  100+(cz-motorz_range_min)*2500/motorz_range;
	    }
	
	#endif
	*-/  
	in_pwm_loop = false;
#endif
*/
}


void servo_set(int angle) {
#ifdef servo_pin
  pwm.setPWM(servo_pin, 0, spindle_pwm * 0.205);  // set 0 - 4095
  return;
#endif
}

void THEISR servo_loop() {
  //pwm_loop();
}

int somedelay(int32_t n) {
  /*  
  float f = 0;
  int m = 100;

  while (m--) {
    int nn = n;
    while (nn--) {
      f += n;
      asm("");
    }
  }
  return f + n;
*/
  auto m = micros();
  while ((micros() - m) < n) {};
  return 0;
}

//#define somedelay(n) delayMicroseconds(n);
int dogfeed = 0;

#include <Arduino.h>
#define dogfeedevery 2200  // loop
// ESP8266 specific code here


int feedthedog() {
  // ESP.wdtFeed();

  if (dogfeed++ > dogfeedevery) {
    dogfeed = 0;
    yield();
    // esp_task_wdt_reset();

#if defined(ESP8266)
    // ESP8266 specific code here
    ESP.wdtFeed();
#elif defined(ESP32)
    //  esp_task_wdt_reset();
#else
#endif
    // zprintf(PSTR("Feed the dog\n"));
    return 1;
  }

  return 0;
}


// ======================== TIMER for motionloop =============================
#define timerPause()
#define timerResume()

int busy1 = 0;
volatile uint32_t ndelay = 0;
volatile uint32_t n1delay = 0;
uint32_t next_step_time;

inline int THEISR timercode();
// -------------------------------------   ESP8266  ----------------------------------------------------------
// #ifdef ESP8266

#ifdef ESP8266

#define USETIMEROK
#define MINDELAY 100
#define usetmr1

int tm_mode=0;
extern int lasermode;
extern uint32_t pwm_val;
extern bool toolWasOn;
bool TMTOOL=false;
bool TMTOOL0=false;

void THEISR tm01()
{
  noInterrupts();
  TMTOOL0=!TMTOOL0;
  uint32_t t0=ESP.getCycleCount();
  if (pwm_val>0){
    if (pwm_val>200){
      TOOLPWM(TOOLON);
      t0+=100000;
      // always on
    } else {
      TOOLPWM(TMTOOL0);
      //int v=(pwm_val*pwm_val)>>2;
      int v=(pwm_val)<<10;
      t0+=(min_pwm_clock+1)*40+(TMTOOL0?v:300000-v);
    }
  } else {
    TOOLPWM(!TOOLON);
    t0+=100000;
  }
  timer0_write(t0);
  interrupts();
}

void THEISR tm()
{
  noInterrupts();
  /*
  int d=0;
  // laser timer
  if (tm_mode==1){
    tm_mode=0;
    // Turn off laser
    d=n1delay;
  }
  if (d==0) {
  // motor timer
    d = timercode();
    tm_mode=n1delay>0?1:0;
  } else {     
    //TMTOOL=!TOOLON;
    //TOOL1(!TOOLON);
  }*/
  int d = timercode();
  
  timer1_write(d);
  //TOOL1(TMTOOL)
  interrupts();
}

void timer_init()
{
  //Initialize Ticker every 0.5s
  noInterrupts();

  timer1_isr_init();
  timer1_attachInterrupt(tm);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
  timer1_write(1000); //200 us

  timer0_isr_init();
  timer0_attachInterrupt(tm01);
  timer0_write(ESP.getCycleCount() + 80 * 10); //10 us


#ifdef RPM_COUNTER
  setup_RPM();
#endif
  set_tool(0);
  interrupts();
}

#else
// #endif

int tm_mode = 0;
extern int lasermode;
extern uint32_t pwm_val;
extern bool toolWasOn;
bool TMTOOL = false;
bool TMTOOL0 = false;

// void THEISR tm01() {
void IRAM_ATTR tm01() {
  noInterrupts();
  TMTOOL0 = !TMTOOL0;
  uint32_t t0 = ESP.getCycleCount();
  if (pwm_val > 0) {
    if (pwm_val > 200) {
      TOOLPWM(TOOLON);
      t0 += 100000;
      // always on
    } else {
      TOOLPWM(TMTOOL0);
      //int v=(pwm_val*pwm_val)>>2;
      int v = (pwm_val) << 10;
      t0 += (min_pwm_clock + 1) * 40 + (TMTOOL0 ? v : 300000 - v);
    }
  } else {
    TOOLPWM(!TOOLON);
    t0 += 100000;
  }
  timerWrite(timer1, t0);
  // timer0_write(t0);
  interrupts();
}

// void THEISR tm() {
  void IRAM_ATTR tm() {
  noInterrupts();
  // zprintf(PSTR("\n Interupt OK! \n"));
  // zprintf(PSTR("."));
  /*
  int d=0;
  // laser timer
  if (tm_mode==1){
    tm_mode=0;
    // Turn off laser
    d=n1delay;
  }
  if (d==0) {
  // motor timer
    d = timercode();
    tm_mode=n1delay>0?1:0;
  } else {     
    //TMTOOL=!TOOLON;
    //TOOL1(!TOOLON);
  }*/
  int d = timercode();
  // zprintf(PSTR("\n %d \n"),d);
  // int d = 1000;
  // timerAlarmWrite(timer1, d, false);
  timerAlarm(timer1, d, true, 0);

  // timer1_write(d);
  //TOOL1(TMTOOL)
  interrupts();
}

void timer_init() {
  //Initialize Ticker every 0.5s
  noInterrupts();

  // esp_task_wdt_init(&wdt_config);  // enable panic so ESP32 restarts

  // disableCore0WDT();

  lT = micros()+1000;
  // timer1 = timerBegin(1000000); //jalan di 1Mhz
  // timerAttachInterrupt(timer1, &tm); //attachinterupt ke tm
  // timerAlarm(timer1, 1000000/16, true, 0); //alarm timer1 menjalankan void tm setiap 1Mhz/16.Auto reload = true , Jumlah reload = 0(artinya unlimited);
  // // timerAlarmWrite(timer1, 200);
  // zprintf(PSTR("\n Interupt OK! \n"));

  // timerStart(timer1);
  // timer1_isr_init();
  // timer1_attachInterrupt(tm);
  // timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
  // timer1_write(1000);  //200 us

  // timer2 = timerBegin(1000000);
  // timerAttachInterrupt(timer1, &tm01);
  // timerWrite(timer2, ESP.getCycleCount() + 80 * 10);

  // timer0_isr_init();
  // timer0_attachInterrupt(tm01);
  // timer0_write(ESP.getCycleCount() + 80 * 10);  //10 us

  // esp_intr_alloc(ETS_TIMER0_INTR_SOURCE, ESP_INTR_FLAG_IRAM, NULL, NULL, NULL);


#ifdef RPM_COUNTER
  setup_RPM();
#endif
  set_tool(0);
  interrupts();
}

#endif


#define USETIMEROK
#define MINDELAY 100
#define usetmr1



void tmloop(uint32_t T){
  if(T > lT){
    uint32_t d = timercode();
    if( d < MINDELAY)d = MINDELAY;
    lT = T+d;
  }

  analogWrite(tool_pin, constantlaserVal * (cmdve/(100 << 6)))
}

// inline int THEISR timercode() {
  inline int IRAM_ATTR timercode() {
  
  ndelay = MINDELAY;
  n1delay = 0;

  // zprintf(PSTR("|"));
  coreloopm();
  return ndelay;
}

// ==============================================

//

// Laser constant burn timer
// void THEISR timer_set(int32_t delay) {
  void IRAM_ATTR timer_set(int32_t delay) {
  
  n1delay = 0;     // delay laser
  ndelay = delay;  // delay total
}

// Laser constant burn timer
// void THEISR timer_set2(int32_t delay1, int32_t delay2) {
  void IRAM_ATTR timer_set2(int32_t delay1, int32_t delay2) {
  // delay1 delay of the laser
  // delay2 delay total
  if (delay1 > 0) {
    delay1 += min_pwm_clock;
    if (delay1 > delay2) delay1 = delay2;
    delay2 -= delay1;
    n1delay = delay2;  // laser on delay
    ndelay = delay1;   // rest delay (can be 0)
    //TMTOOL=TOOLON;
    TOOL1(TOOLON);
  } else {
    //TMTOOL=!TOOLON;
    n1delay = 0;
    ndelay = delay2;  // rest relay (can be 0)
  }
}
