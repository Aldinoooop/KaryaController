#include "freertos/FreeRTOS.h"  // Untuk RTOS support di ESP32
#include "driver/timer.h"       // Untuk menggunakan hardware timer di ESP32

// Deklarasi variabel timer
hw_timer_t *My_timer = NULL;
hw_timer_t *timer1 = NULL;
hw_timer_t *timer2 = NULL;

// Fungsi yang akan dipanggil saat interrupt timer terpicu
void IRAM_ATTR onTimer1() {
  // Tindakan yang akan dilakukan saat interrupt terpicu
  digitalWrite(26,HIGH);
  // Serial.println("Timer1 Interrupt Triggered");
  digitalWrite(26,LOW);
}

void IRAM_ATTR onTimer2() {
  // Tindakan yang akan dilakukan saat interrupt terpicu
  Serial.println("Timer2 Interrupt Triggered");
}

void timer_init() {
  // Inisialisasi timer dengan timer 0, prescaler 80 (1 tick = 1 µs)
  // My_timer = timerBegin(0, 80, true);
  // My_timer = timerBegin(1000000);
  timer1 = timerBegin(1000000);
  // timer2 = timerBegin(1000000);

  // Hubungkan fungsi interrupt ke timer
  // timerAttachInterrupt(My_timer, &onTimer, true);
  // timerAttachInterrupt(My_timer, &onTimer);
  timerAttachInterrupt(timer1, &onTimer1);
  // timerAttachInterrupt(timer2, &onTimer2);

  // Atur alarm timer untuk memicu interrupt setiap 12.000 µs (12 ms)
  timerAlarm(timer1, 100, true, 0);
  // timerAlarm(timer2, 2000000, true, 0);
  // timerAlarmWrite(My_timer, 12000, true);

  // // Aktifkan alarm timer
  // timerAlarmEnable(My_timer);

  Serial.println("Timer initialized");
  // timerAlarmEnable(stepperTimer);
  timerStart(timer1);
  // timerStart(timer2);
  // timerWrite(timer1, 0);
  // timerWrite(timer2, 0);
}

void setup() {
  // Inisialisasi komunikasi serial untuk debug output
  Serial.begin(115200);
  pinMode(26,OUTPUT);

  // Inisialisasi timer
  timer_init();
}

void loop() {
  // Serial.println("Timer 1 = " + String(timerRead(timer1)) + " Timer 2 = " + String(timerRead(timer2)));
  // Main loop kosong, karena semua fungsi ditangani oleh interrupt
}
