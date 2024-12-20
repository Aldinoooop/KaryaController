#pragma once
#ifndef timer_H
#define timer_H


#include <stdint.h>
#define TMSCALE 1024L
extern int somedelay(int32_t n);
//#define somedelay(n) delayMicroseconds(n);
extern int feedthedog();


#define timescale 1000000L


#if defined(ESP8266) && defined(WIFISERVER)
#define usetmr1
#endif

extern uint32_t get_RPM();



#define SUBMOTION 1
#define timescaleLARGE timescale *TMSCALE

extern void set_tool(int v);
extern void pause_pwm(bool v);
extern volatile uint32_t ndelay;


extern uint32_t next_step_time;
extern void timer_init();
extern void timer_set(int32_t delay);
extern void IRAM_ATTR timer_set2(int32_t delay1, int32_t delay2);
// extern void timer_set2(int32_t delay1, int32_t delay2);
extern void servo_loop();
extern void servo_set(int angle);
extern void tmloop(uint32_t T);
#ifndef MASK
/// MASKING- returns \f$2^PIN\f$
#define MASK(PIN) (1 << PIN)
#endif


#ifndef CLI
#define CLI
#define SEI
#define MEMORY_BARRIER()
#define ATOMIC_START
#define ATOMIC_END
#endif

// #ifdef ESP32
// extern void IRAM_ATTR timerPause();
// extern void IRAM_ATTR timerResume();
// #else
#define timerPause()
#define timerResume()
// #endif
#endif
