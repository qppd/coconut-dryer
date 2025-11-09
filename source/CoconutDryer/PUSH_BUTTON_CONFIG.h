#define BUTTON_COUNT 3
#define DEBOUNCE_DELAY 50

#define BUTTON_1 17
#define BUTTON_2 16
#define BUTTON_3 4

int inputState[BUTTON_COUNT];
int lastInputState[BUTTON_COUNT] = { LOW, LOW, LOW };
bool inputFlags[BUTTON_COUNT] = { LOW, LOW, LOW };
long lastDebounceTime[BUTTON_COUNT] = { 0, 0, 0 };
const int inputPins[BUTTON_COUNT] = { BUTTON_1, BUTTON_2, BUTTON_3 };

bool first_time = true;

void initBUTTONS() {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
    inputFlags[i] = LOW;
    inputState[i] = digitalRead(inputPins[i]);  // Read actual button state at start
  }
  delay(50);  // Allow readings to stabilize
  Serial.println("Push Buttons: Initialized!");
}

//-----------------------------------------------------------------
//FUNCTION FOR BUTTON OPERATION -----------------------------------
//-----------------------------------------------------------------

int CURRENT_DISPLAY = 0;

void inputAction(int SWITCH_PIN) {

  if (SWITCH_PIN == 0) {  // Button 1
    Serial.println("1 pressed!");

    if (CURRENT_DISPLAY == 0) {

      CURRENT_MENU = CURRENT_DISPLAY;
      arrowLCD(10, 0);
      setLCDText(" ", 10, 1);
      setLCDText(" ", 10, 2);
      CURRENT_DISPLAY++;
    } else if (CURRENT_DISPLAY == 1) {

      CURRENT_MENU = CURRENT_DISPLAY;
      arrowLCD(10, 1);
      setLCDText(" ", 10, 0);
      setLCDText(" ", 10, 2);
      CURRENT_DISPLAY++;
    } else if (CURRENT_DISPLAY == 2) {

      CURRENT_MENU = CURRENT_DISPLAY;
      arrowLCD(10, 2);
      setLCDText(" ", 10, 0);
      setLCDText(" ", 10, 1);
      CURRENT_DISPLAY = 0;
    }

  } else if (SWITCH_PIN == 1) {  // Button 2
    Serial.println("2 pressed!");

    if (CURRENT_MENU == 0) {

      if (TEMPERATURE_SETPOINT < 80) {
        TEMPERATURE_SETPOINT += 5;
      } else if (TEMPERATURE_SETPOINT == 80) {
        TEMPERATURE_SETPOINT = 60;
      }

    } else if (CURRENT_MENU == 1) {

      if (HUMIDITY_SETPOINT < 30) {
        HUMIDITY_SETPOINT += 1;
      } else if (HUMIDITY_SETPOINT == 30) {
        HUMIDITY_SETPOINT = 0;
      }


    } else if (CURRENT_MENU == 2) {
      if (MOISTURE_SETPOINT < 10) {
        MOISTURE_SETPOINT += 1;
      } else if (MOISTURE_SETPOINT == 10) {
        MOISTURE_SETPOINT = 1;
      }
    }

  } else if (SWITCH_PIN == 2) {  // Button 3
    Serial.println("3 pressed!");

    if (CURRENT_OPERATION == 1) {
      clearLCD();
      setLCDText("Drying done!", 0, 0);
      setLCDText("Turning off,", 0, 1);
      setLCDText("coconut dryer!", 0, 2);

      operateSSR(RELAY_1, false);
      operateSSR(RELAY_2, false);
      operateSSR(RELAY_3, false);

      delay(1500);
      clearLCD();
      setLCDText("T:0.0  C", 0, 0);
      setLCDText("H:0.0  %", 0, 1);
      setLCDText("M:0.0  %", 0, 2);

      setLCDText("SP:0.0  C", 11, 0);
      setLCDText("SP:0.0  %", 11, 1);
      setLCDText("SP:0.0  %", 11, 2);
      CURRENT_OPERATION = 0;
    } else if (CURRENT_OPERATION <= 0) {
      clearLCD();
      setLCDText("Drying started!", 0, 0);
      setLCDText("Caution! Hot!", 0, 1);

      delay(1500);
      clearLCD();
      setLCDText("T:0.0  C", 0, 0);
      setLCDText("H:0.0  %", 0, 1);
      setLCDText("M:0.0  %", 0, 2);

      setLCDText("SP:0.0  C", 11, 0);
      setLCDText("SP:0.0  %", 11, 1);
      setLCDText("SP:0.0  %", 11, 2);
      CURRENT_OPERATION = 1;
    }
  }
}

//-----------------------------------------------------------------
//FUNCTION FOR SETTING BUTTON STATE--------------------------------
//-----------------------------------------------------------------
void setInputFlags() {
  for (int i = 0; i < BUTTON_COUNT; i++) {    // loop until i is less than 4
    int reading = digitalRead(inputPins[i]);  // read pins
    if (reading != lastInputState[i]) {       // if reading is not equal to the lastInputState which are (ex: LOW,LOW,LOW,LOW
      lastDebounceTime[i] = millis();         // set lastDebounceTime equal to arduino's running time
    }
    if (millis() - lastDebounceTime[i] > DEBOUNCE_DELAY) {  // if arduino's running time and lastDebounceTime difference is greater than debounceDelay whis is 5 then
      if (reading != inputState[i]) {                       // if reading is not equal to inputState ex: 0,0,0,0
        inputState[i] = reading;                            // then make inputState equals to reading
        if (inputState[i] == HIGH) {                        // if inputState is equal to high which is Pressed switch then
          inputFlags[i] = HIGH;                             // make inputFlag equal to high
        }
      }
    }
    lastInputState[i] = reading;  // set last Input state equal to reading of every switches
  }                               // loop end
}



//-----------------------------------------------------------------
//FUNCTION FOR READING BUTTON STATE--------------------------------
//-----------------------------------------------------------------

void resolveInputFlags() {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    if (inputFlags[i] == HIGH) {
      if (i == 2 && first_time) {  // Only for first-time check
        CURRENT_MENU = -1;
        first_time = false;
      } else {
        inputAction(i);
      }
      inputFlags[i] = LOW;
    }
  }
}
