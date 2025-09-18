//==============================================================
//        Soil Moisture Sensor Calibration Sketch
//==============================================================

// Define the analog pin the sensor is connected to
#define SOIL_SENSOR_PIN A0

void setup() {
  // Start serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Print a startup message
  Serial.println("--- Soil Moisture Sensor Calibration ---");
  Serial.println("Reading values from pin A0...");
  Serial.println("Test the sensor in different conditions (dry air, dry soil, wet soil).");
}

void loop() {
  // Read the raw analog value from the sensor (0-1023)
  int sensorValue = analogRead(SOIL_SENSOR_PIN);

  // Print the value to the Serial Monitor
  Serial.print("Soil Sensor Value: ");
  Serial.println(sensorValue);
  
  // Wait for half a second before the next reading
  delay(500); 
}
