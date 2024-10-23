#include "freertos/FreeRTOS.h"  // Untuk RTOS support di ESP32
#include "driver/timer.h"       // Untuk menggunakan hardware timer di ESP32

// Deklarasi variabel timer
hw_timer_t *My_timer = NULL;

// Fungsi yang akan dipanggil saat interrupt timer terpicu
void IRAM_ATTR onTimer() {
  // Tindakan yang akan dilakukan saat interrupt terpicu
  Serial.println("Timer Interrupt Triggered");
}

void timer_init() {
  // Inisialisasi timer dengan timer 0, prescaler 80 (1 tick = 1 µs)
  // My_timer = timerBegin(0, 80, true);

  // Hubungkan fungsi interrupt ke timer
  // timerAttachInterrupt(My_timer, &onTimer, true);
  timerAttachInterrupt(My_timer, &onTimer);

  // Atur alarm timer untuk memicu interrupt setiap 12.000 µs (12 ms)
  timerAlarm(My_timer, 12000, true); 
  // timerAlarmWrite(My_timer, 12000, true);

  // // Aktifkan alarm timer
  // timerAlarmEnable(My_timer);

  Serial.println("Timer initialized");
}

void setup() {
  // Inisialisasi komunikasi serial untuk debug output
  Serial.begin(115200);

  // Inisialisasi timer
  timer_init();
}

void loop() {
  // Main loop kosong, karena semua fungsi ditangani oleh interrupt
}
