double CURRENT_TEMPERATURE = 0;
double CURRENT_HUMIDITY = 0;
double CURRENT_MOISTURE = 0;

double TEMPERATURE_SETPOINT = 60;
double HUMIDITY_SETPOINT = 20;
double MOISTURE_SETPOINT = 6;

int CURRENT_MENU = -1;
int CURRENT_OPERATION = -1;

#include "LCD_CONFIG.h"
#include "SHT31_CONFIG.h"
#include "SOIL_MOISTURE_CONFIG.h"
#include "RELAY_CONFIG.h"
#include "PID_CONFIG.h"
#include "BUZZER_CONFIG.h"
#include "PUSH_BUTTON_CONFIG.h"
#include "LIB.h"


void setup() {
  Serial.begin(9600);
  Serial.println("Coconut Dryer - Serial Monitor");

  initLCD();


  setLCDText("Coconut Dryer", 0, 0);
  delay(1500);
  setLCDText("SLSU Lucban", 0, 1);
  delay(1500);
  setLCDText("BSME", 0, 2);
  delay(2000);
  clearLCD();
  setLCDText("T:0.0  C", 0, 0);
  setLCDText("H:0.0  %", 0, 1);
  setLCDText("M:0.0  %", 0, 2);

  setLCDText("SP:0.0  C", 11, 0);
  setLCDText("SP:0.0  %", 11, 1);
  setLCDText("SP:0.0  %", 11, 2);
  delay(1500);

  initSHT31();
  initPID();
  initRELAY();
  initBUTTONS();

  CURRENT_MENU = 0;
}

unsigned long loop_time_for_interval;
uint16_t loop_interval = 500;  // 1 second

void loop() {

  if (millis() > loop_time_for_interval + loop_interval) {
    loop_time_for_interval = millis();

    getSHT31TempAnHum();
    getMOISTURE();

    if (CURRENT_OPERATION == 1) {
      Serial.println("PID is computing!");
      pidCOMPUTE();

      setLCDText("Status: Drying", 0, 3);

      if (CURRENT_MOISTURE <= MOISTURE_SETPOINT) {
        Serial.println("Drying is done!");
        operateSSR(RELAY_1, false);
        operateSSR(RELAY_2, false);
        operateSSR(RELAY_3, false);

        

        clearLCD();
        setLCDText("Drying done!", 0, 0);
        setLCDText("Turning off,", 0, 1);
        setLCDText("coconut dryer!", 0, 2);

        delay(1500);
        clearLCD();
        setLCDText("T:0.0  C", 0, 0);
        setLCDText("H:0.0  %", 0, 1);
        setLCDText("M:0.0  %", 0, 2);

        setLCDText("SP:0.0  C", 11, 0);
        setLCDText("SP:0.0  %", 11, 1);
        setLCDText("SP:0.0  %", 11, 2);
        CURRENT_OPERATION = 0;
      }
    } else {
      setLCDText("Status: Stand by", 0, 3);
    }


    CURRENT_TEMPERATURE = round(CURRENT_TEMPERATURE * 10) / 10.0;
    CURRENT_HUMIDITY = round(CURRENT_HUMIDITY * 10) / 10.0;
    CURRENT_MOISTURE = round(CURRENT_MOISTURE * 10) / 10.0;
    TEMPERATURE_SETPOINT = round(TEMPERATURE_SETPOINT * 10) / 10.0;
    HUMIDITY_SETPOINT = round(HUMIDITY_SETPOINT * 10) / 10.0;
    MOISTURE_SETPOINT = round(MOISTURE_SETPOINT * 10) / 10.0;

    String ctemp = String(CURRENT_TEMPERATURE);
    ctemp = ctemp.substring(0, ctemp.length() - 1);

    setLCDText(ctemp, 2, 0);
    setLCDText(CURRENT_HUMIDITY, 2, 1);
    //setLCDText(CURRENT_MOISTURE, 2, 2);

    if (CURRENT_MOISTURE < 10) {
      setLCDText(String("0") + CURRENT_MOISTURE, 2, 2);

    } else {
      setLCDText(CURRENT_MOISTURE, 2, 2);
    }

    setLCDText(TEMPERATURE_SETPOINT, 14, 0);
    setLCDText(HUMIDITY_SETPOINT, 14, 1);

    if (MOISTURE_SETPOINT < 10) {
      setLCDText(String("0") + MOISTURE_SETPOINT, 14, 2);

    } else {
      setLCDText(MOISTURE_SETPOINT, 14, 2);
    }
  }

  setInputFlags();
  resolveInputFlags();
}
