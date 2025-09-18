//======================================================================
//        CONFIGURATION & PIN DEFINITIONS
//======================================================================

// --- Sensor Pins (Analog) ---
#define SOIL_SENSOR_PIN_1 A0 // Soil moisture sensor 1 to pin A0
#define SOIL_SENSOR_PIN_2 A1 // Soil moisture sensor 2 to pin A1
#define RAIN_SENSOR_PIN   A2 // Raindrop sensor to pin A2

// --- Relay Pins (Digital) ---
#define RELAY_PIN_1 2 // Relay for soil sensor 1 to pin D2
#define RELAY_PIN_2 3 // Relay for soil sensor 2 to pin D3
#define RELAY_PIN_3 4 // Relay for rain sensor to pin D4

// --- THRESHOLD VALUES (CALIBRATE THESE!) ---
// NOTE: For most soil/rain sensors, a LOWER value means MORE moisture/rain.

// Soil Moisture Thresholds (0-1023)
// Relay turns ON when moisture drops BELOW this value
#define SOIL_MOISTURE_MIN 300
// Relay turns OFF when moisture goes ABOVE this value
#define SOIL_MOISTURE_MAX 700

// Rain Sensor Thresholds (0-1023)
// Relay turns ON when rain value drops BELOW this value
#define RAIN_DETECT_MIN 400
// Relay turns OFF when rain value goes ABOVE this value (it's dry again)
#define RAIN_DETECT_MAX 800

// --- TIMING ---
// How often to check the sensors (in milliseconds)
const unsigned long CHECK_INTERVAL_MS = 2000; // Check every 2 seconds

//======================================================================
//        GLOBAL VARIABLES
//======================================================================

// Variable to store the last time sensors were checked
unsigned long previousMillis = 0;

//======================================================================
//        SETUP FUNCTION (runs once at the start)
//======================================================================

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  Serial.println("Initializing System...");

  // Set relay pins as outputs
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);

  // Initialize relays to the OFF state.
  // Most common relay modules are "active-LOW", meaning HIGH is OFF.
  // If your relays are active-HIGH, swap HIGH and LOW here and below.
  digitalWrite(RELAY_PIN_1, HIGH); // Set Relay 1 OFF
  digitalWrite(RELAY_PIN_2, HIGH); // Set Relay 2 OFF
  digitalWrite(RELAY_PIN_3, HIGH); // Set Relay 3 OFF
  
  Serial.println("System Ready.");
}

//======================================================================
//        MAIN LOOP (runs continuously)
//======================================================================

void loop() {
  // This is the core of the non-blocking "threading" method.
  // It checks if enough time has passed since the last sensor check.
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= CHECK_INTERVAL_MS) {
    // Save the current time for the next interval
    previousMillis = currentMillis;

    // Call the functions to handle each sensor/relay pair.
    // Because we don't use delay(), one function doesn't block the others.
    handleSoilSensor1();
    handleSoilSensor2();
    handleRainSensor();

    Serial.println("--------------------"); // Separator for readability
  }
}

//======================================================================
//        HELPER FUNCTIONS (our "processes")
//======================================================================

void handleSoilSensor1() {
  // Read the analog value from the sensor
  int soilValue1 = analogRead(SOIL_SENSOR_PIN_1);
  Serial.print("Soil 1 Value: ");
  Serial.print(soilValue1);

  // Logic for Relay 1
  if (soilValue1 < SOIL_MOISTURE_MIN) {
    digitalWrite(RELAY_PIN_1, LOW); // Turn Relay 1 ON (LOW for active-low)
    Serial.println(" -> DRY, Relay 1 ON");
  } else if (soilValue1 > SOIL_MOISTURE_MAX) {
    digitalWrite(RELAY_PIN_1, HIGH); // Turn Relay 1 OFF (HIGH for active-low)
    Serial.println(" -> WET, Relay 1 OFF");
  } else {
    Serial.println(" -> OK"); // In the middle, do nothing
  }
}

void handleSoilSensor2() {
  // Read the analog value from the sensor
  int soilValue2 = analogRead(SOIL_SENSOR_PIN_2);
  Serial.print("Soil 2 Value: ");
  Serial.print(soilValue2);

  // Logic for Relay 2
  if (soilValue2 < SOIL_MOISTURE_MIN) {
    digitalWrite(RELAY_PIN_2, LOW); // Turn Relay 2 ON
    Serial.println(" -> DRY, Relay 2 ON");
  } else if (soilValue2 > SOIL_MOISTURE_MAX) {
    digitalWrite(RELAY_PIN_2, HIGH); // Turn Relay 2 OFF
    Serial.println(" -> WET, Relay 2 OFF");
  } else {
    Serial.println(" -> OK");
  }
}

void handleRainSensor() {
  // Read the analog value from the sensor
  int rainValue = analogRead(RAIN_SENSOR_PIN);
  Serial.print("Rain Value:   ");
  Serial.print(rainValue);
  
  // Logic for Relay 3
  if (rainValue < RAIN_DETECT_MIN) {
    digitalWrite(RELAY_PIN_3, LOW); // Turn Relay 3 ON (It's raining)
    Serial.println(" -> RAINING, Relay 3 ON");
  } else if (rainValue > RAIN_DETECT_MAX) {
    digitalWrite(RELAY_PIN_3, HIGH); // Turn Relay 3 OFF (It's dry)
    Serial.println(" -> DRY, Relay 3 OFF");
  } else {
    Serial.println(" -> OK");
  }
}
