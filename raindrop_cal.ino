//==============================================================
//        Raindrop Sensor Calibration Sketch
//==============================================================

// Define the analog pin the sensor is connected to
#define RAIN_SENSOR_PIN A1

void setup() {
  // Start serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Print a startup message
  Serial.println("--- Raindrop Sensor Calibration ---");
  Serial.println("Reading values from pin A1...");
  Serial.println("Test the sensor plate when dry and with water drops.");
}

void loop() {
  // Read the raw analog value from the sensor (0-1023)
  int sensorValue = analogRead(RAIN_SENSOR_PIN);

  // Print the value to the Serial Monitor
  Serial.print("Rain Sensor Value: ");
  Serial.println(sensorValue);
  
  // Wait for half a second before the next reading
  delay(500); 
}
