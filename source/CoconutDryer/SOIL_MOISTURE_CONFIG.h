#define SOIL_MOISTURE_PIN 39

// Define min and max ADC values (update based on your calibration)
const int DRY_VALUE = 4095;  // ADC value in dry soil
const int WET_VALUE = 950;     // ADC value in wet soil

void getMOISTURE() {
  int moistureValue = analogRead(SOIL_MOISTURE_PIN);  // Read the sensor value
  Serial.println("Moisture:" + String(moistureValue));
  // Map the raw ADC value to a percentage (0% = dry, 100% = wet)
  CURRENT_MOISTURE = map(moistureValue, DRY_VALUE, WET_VALUE, 0, 100);

  // Ensure the value is within the 0-100% range
  CURRENT_MOISTURE = constrain(CURRENT_MOISTURE, 0, 55);

  // Serial.print("Moisture: ");
  // Serial.print(CURRENT_MOISTURE);
  // Serial.println("%");
}
