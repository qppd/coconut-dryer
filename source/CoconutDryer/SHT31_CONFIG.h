#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void initSHT31() {

  Serial.println("SHT31 test");
  if (!sht31.begin(0x44)) {  // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }

  Serial.print("Heater Enabled State: ");
  if (sht31.isHeaterEnabled())
    Serial.println("ENABLED");
  else
    Serial.println("DISABLED");
}


void getSHT31TempAnHum() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();
  CURRENT_TEMPERATURE = round(t * 10) / 10.0;
  CURRENT_TEMPERATURE += 5;
  CURRENT_HUMIDITY = round(h * 10) / 10.0;

  // if (!isnan(t)) {  // check if 'is not a number'
  //   Serial.print("Temp *C = ");
  //   Serial.print(t);
  //   Serial.print("\t\t");
  // } else {
  //   Serial.println("Failed to read temperature");
  // }

  // if (!isnan(h)) {  // check if 'is not a number'
  //   Serial.print("Hum. % = ");
  //   Serial.println(h);
  // } else {
  //   Serial.println("Failed to read humidity");
  // }
}
