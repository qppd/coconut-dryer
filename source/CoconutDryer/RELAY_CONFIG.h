uint16_t RELAY_1 = 19;
uint16_t RELAY_2 = 18;
uint16_t RELAY_3 = 5;

//-----------------------------------------------------------------
//FUNCTION FOR SETTING RELAY PIN MODE------------------------------
//-----------------------------------------------------------------
void initRELAY() {
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
}


//-----------------------------------------------------------------
//FUNCTION FOR OPERATING SOLID STATE RELAY-------------------------
//-----------------------------------------------------------------
void operateSSR(uint16_t RELAY, boolean OPENED) {
  if (OPENED) {
    digitalWrite(RELAY, HIGH);
    //Serial.println("ON");
  } else {
    digitalWrite(RELAY, LOW);
  }
}