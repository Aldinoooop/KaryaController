int val = 10000;

// Deklarasi variabel timer
// hw_timer_t *My_timer = NULL;
hw_timer_t *timer1 = NULL;
hw_timer_t *timer2 = NULL;

#include <esp_task_wdt.h>

esp_task_wdt_config_t wdt_config = {
  .timeout_ms = 2000,      // 2-second timeout
  .idle_core_mask = 0x02,  // Monitor both Core 0 and Core 1
  .trigger_panic = false   // Trigger a panic on timeout
};


unsigned long lastMillis = 0;
bool state = 0;
int i = 1000;
// Fungsi yang akan dipanggil saat interrupt timer terpicu
void IRAM_ATTR onTimer1() {
  // Tindakan yang akan dilakukan saat interrupt terpicu
  digitalWrite(14, HIGH);
  // Serial.print(".");
  digitalWrite(14, LOW);
}

void IRAM_ATTR onTimer2() {
  // Tindakan yang akan dilakukan saat interrupt terpicu
  digitalWrite(26, HIGH);
  // Serial.println("Timer 2 Interrupt Triggered");
  digitalWrite(26, LOW);
}

void timer_init() {

  esp_task_wdt_init(&wdt_config);  // enable panic so ESP32 restarts
  // esp_task_wdt_add(NULL);
  // esp_task_wdt_add(NULL);
  // Inisialisasi timer dengan timer 0, prescaler 80 (1 tick = 1 µs)
  // My_timer = timerBegin(0, 80, true);
  // My_timer = timerBegin(1000000);
  timer1 = timerBegin(1000000);
  timer2 = timerBegin(1000000);

  // Hubungkan fungsi interrupt ke timer
  // timerAttachInterrupt(My_timer, &onTimer, true);
  // timerAttachInterrupt(My_timer, &onTimer);
  timerAttachInterrupt(timer1, &onTimer1);
  timerAttachInterrupt(timer2, &onTimer2);

  // Atur alarm timer untuk memicu interrupt setiap 12.000 µs (12 ms)
  timerAlarm(timer1, 1000, false, 0);
  timerAlarm(timer2, 1000, true, 0);
  // timerWrite(timer1, 1000);

  // // Aktifkan alarm timer
  // timerAlarmEnable(My_timer);

  Serial.println("Timer initialized");
  // timerStop(timer1);
  // timerAlarmEnable(stepperTimer);
  // timerStart(timer1);
  // timerStart(timer2);
  // timerWrite(timer1, 0);
  // timerWrite(timer2, 0);
}

void setup() {
  // Inisialisasi komunikasi serial untuk debug output
  Serial.begin(115200);
  pinMode(26, OUTPUT);
  pinMode(14, OUTPUT);



  // Inisialisasi timer
  timer_init();
  // timerWrite(timer1, 5);
}

void loop() {
  // Serial.println(timerRead(timer1));

  if (Serial.available() > 0) {
    val = Serial.readStringUntil('\n').toInt();

    timerAlarm(timer1, val, true, 0);

    // timerWrite(timer1, val);
    // timerStart(timer1);
  }
  // Serial.println("Timer 1 = " + String(timerRead(timer1)) + " Timer 2 = " + String(timerRead(timer2)));
  // Main loop kosong, karena semua fungsi ditangani oleh interrupt

  // if (millis() - lastMillis >= 2000) {
  //   if (state == true) {
  //     Serial.println("ON");
  //     // timerStart(timer1);
  //     // timerWrite(timer1, i);
  //     timerAlarm(timer1, i, true, 0);
  //     i += 100;

  //     state = false;
  //   } else {
  //     Serial.println("OFF");
  //     // timerStop(timer1);

  //     state = true;
  //   }
  //   lastMillis = millis();
  // }
}
