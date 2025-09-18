# Automated Multi-Sensor Relay Controller for Arduino

This project is an Arduino Nano-based system designed to automate tasks like irrigation by controlling three relays based on input from two soil moisture sensors and one raindrop sensor. It uses a non-blocking coding approach, allowing it to monitor all sensors and act on their inputs concurrently without conflicts.

## 📝 Overview

The system independently monitors two separate soil zones. If the moisture in a zone drops below a predefined "dry" threshold, its corresponding relay is activated (e.g., turning on a water pump or valve). When the moisture rises above a "wet" threshold, the relay is deactivated.

Simultaneously, a raindrop sensor monitors for precipitation. When rain is detected, a third relay is activated, which can be used to override the watering system or trigger another action (like closing a window). The entire system is built on a non-blocking timer, making it responsive and efficient.

## ✨ Features

  * **Dual-Zone Soil Monitoring:** Controls two relays independently based on two soil moisture sensors.
  * **Rain Detection:** Uses a raindrop sensor to control a third relay, perfect for overriding irrigation during rain.
  * **Non-Blocking Code:** Employs the `millis()` function for cooperative multitasking, ensuring that no single task freezes the processor. This allows all sensors to be monitored seamlessly.
  * **Fully Configurable:** All sensor thresholds (`MIN` and `MAX` values) are defined at the top of the code for easy adjustment.
  * **Serial Debugging:** Provides continuous feedback to the Serial Monitor, showing sensor values and relay states, which is crucial for calibration and troubleshooting.
  * **Status Indicators:** Designed to control devices like pumps, valves, or indicator lights via a standard relay module.

## 🛠️ Hardware Requirements

  * 1 x Arduino Nano (or compatible board like Arduino Uno)
  * 2 x Soil Moisture Sensor Modules
  * 1 x Raindrop Sensor Module
  * 1 x 3-Channel 5V Relay Module (or three single-channel modules)
  * Jumper Wires
  * 5V Power Supply (via USB or external `Vin` pin)

## 🔌 Wiring Diagram

Connect the components to the Arduino Nano as described below.

![Wiring Diagram](https://raw.githubusercontent.com/gayan-tharuka/Rain-Harvest/refs/heads/main/Rain%20Harvest.png?token=GHSAT0AAAAAADHS7PQIIR4OOO557CH4PKT42GMJGPA)

| Component             | Sensor/Relay Pin | Arduino Nano Pin |
| --------------------- | ---------------- | ---------------- |
| Soil Moisture Sensor 1 | Analog Out (A0)  | `A0`             |
| Soil Moisture Sensor 2 | Analog Out (A0)  | `A1`             |
| Raindrop Sensor       | Analog Out (A0)  | `A2`             |
| Relay 1               | Input (IN1)      | `D2`             |
| Relay 2               | Input (IN2)      | `D3`             |
| Relay 3               | Input (IN3)      | `D4`             |
| **All Sensors/Relays** | **VCC / +** | **`5V`** |
| **All Sensors/Relays** | **GND / -** | **`GND`** |

-----

## ⚙️ Software Setup & Configuration

This project is written in C++ for the Arduino platform.

### 1\. Arduino IDE

  * Ensure you have the [Arduino IDE](https://www.arduino.cc/en/software) installed.
  * No external libraries are required for this project to compile.

### 2\. Configuration & Calibration (CRITICAL STEP)

The accuracy of this system depends entirely on proper calibration. The sensor values for "wet" and "dry" can vary significantly based on your specific sensors, soil type, and setup.

**You must calibrate your sensors before use\!**

Use the provided `calibration` sketches to find the correct values for your environment.

1.  Open the main `.ino` file.
2.  Locate the **CONFIGURATION & PIN DEFINITIONS** section at the top.
3.  Modify the threshold values based on your calibration tests:
    ```cpp
    // --- THRESHOLD VALUES (CALIBRATE THESE!) ---
    // NOTE: For most soil/rain sensors, a LOWER value means MORE moisture/rain.

    // Relay turns ON when moisture drops BELOW this value
    #define SOIL_MOISTURE_MIN 300
    // Relay turns OFF when moisture goes ABOVE this value
    #define SOIL_MOISTURE_MAX 700

    // Relay turns ON when rain value drops BELOW this value
    #define RAIN_DETECT_MIN 400
    // Relay turns OFF when rain value goes ABOVE this value (it's dry again)
    #define RAIN_DETECT_MAX 800
    ```
4.  Upload the main sketch to your Arduino Nano.

## 👨‍💻 How It Works

The core logic avoids using the `delay()` function, which freezes the Arduino. Instead, it operates like a state machine driven by a timer.

  * **`millis()` Timer:** The code uses `millis()` to track elapsed time.
  * **Scheduler in `loop()`:** The main `loop()` function runs thousands of times per second. It constantly checks if a set interval (e.g., 2 seconds) has passed since the last sensor reading.
  * **Task Handlers:** When the interval is reached, the `loop()` calls separate functions (`handleSoilSensor1()`, `handleSoilSensor2()`, `handleRainSensor()`). Each function is responsible for one task: reading its sensor and controlling its relay.
  * **Efficiency:** This structure ensures the Arduino is always ready to process new information without getting stuck, making the system highly responsive.

## 🚀 Usage

1.  Wire the hardware according to the diagram.
2.  Calibrate your sensors and update the thresholds in the code.
3.  Upload the main sketch to the Arduino Nano.
4.  Connect the devices you want to control (pumps, valves, lights, etc.) to the output terminals of the relay module.
5.  Power on the system.
6.  Open the **Serial Monitor** (baud rate 9600) to observe the sensor readings and relay statuses in real-time. The system will now operate automatically.
