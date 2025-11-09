#define BUZZER_PIN 33

void initBUZZER() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void operateBUZZER(int BUZZER, bool open) {
  digitalWrite(BUZZER, open);
}


void playBUZZER(int BUZZER, int interval, int duration) {
  unsigned long startTime = millis();

  while (millis() - startTime < duration) {
    operateBUZZER(BUZZER_PIN, true);
    delay(interval);
    operateBUZZER(BUZZER_PIN, false);
    delay(interval);
  }
}
