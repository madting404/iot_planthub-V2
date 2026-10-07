# iot_planthub
IoT Planthub — Automated Greenhouse Control System
A final year engineering project built to automate the environmental control of a small greenhouse using an Arduino UNO R4 WiFi. The system continuously monitors temperature and soil moisture, then triggers actuators automatically to maintain optimal growing conditions without human intervention.
What It Does
The system reads environmental data from sensors every 10 seconds and makes automated decisions:
Soil too dry — activates the water pump to irrigate
Temperature above 15°C – turns on the cooling fan
Temperature above 20°C — opens the roof panel via servo motor to ventilate
Temperature below 10°C — activates the enclosure heater to maintain warmth
All decisions run autonomously on the microcontroller using threshold based conditional logic with no cloud dependency required.
Hardware Components
Component    Purpose
Arduino UNO R4 WiFi    Microcontroller running the automation logic
DHT22 Sensor    Reads temperature and humidity
Capacitive Soil Moisture Sensor    Reads soil moisture level
Relay Module x3    Switches fan, pump, and heater on/off
DC Water Pump    Irrigates when soil is dry
Axial Fan    Cools greenhouse when temperature is high
Schneider Electric Enclosure Heater    Heats greenhouse when temperature drops
Servo Motor    Opens and closes roof panel for ventilation
How the Automation Logic Works
Soil Moisture:
The raw analog reading from the capacitive sensor is mapped across three zones: wet, moist, and dry, using calibrated boundary values. The pump activates only when the soil reaches the dry threshold, avoiding overwatering.
Temperature:
Three independent temperature thresholds control three separate actuators. The fan activates above 15°C. The servo opens the roof panel above 20°C, holds it open for 8 seconds to ventilate, then retracts. The heater activates below 10°C to protect against cold.
Serial Monitoring:
All sensor readings and actuator states are logged to the Serial Monitor in real time, allowing live debugging and system observation during development.
Known Limitations
Heater and fan overlap:
Between 10°C and 15°C both the heater and fan could theoretically run simultaneously. In practice this did not cause issues during testing but a more robust implementation would include a dead band or priority logic to prevent both running at once.
No hysteresis on pump threshold:
Near the soil moisture boundary the pump could toggle rapidly on and off. A hysteresis buffer requiring the reading to cross a slightly different threshold to turn off than to turn on would prevent this oscillation in a production system.
Servo blocking delay:
The servo open and retract sequence uses a blocking delay() call which pauses all other sensor reads for 8 seconds. A non-blocking implementation using millis() would be more robust.
What I Would Improve
Switch from Arduino to Raspberry Pi:
The most significant upgrade would be migrating from an Arduino microcontroller to a Raspberry Pi. This would enable running Python based machine learning models directly on the device, opening up several capabilities the current system cannot support:
Crop specific optimisation — train models on the optimal temperature, humidity, and moisture ranges for specific crops. The system could adjust its thresholds automatically based on which crop is selected rather than using fixed values
Predictive watering — use historical soil moisture trends to predict when irrigation will be needed before the soil reaches the dry threshold, reducing plant stress
Anomaly detection — identify unusual sensor patterns that might indicate sensor failure, disease, or pest activity before it becomes visible
Seasonal adaptation — adjust control logic based on time of day, season, and weather patterns rather than fixed thresholds
Improve physical enclosure and wiring:
The current build uses soldered connections with components mounted directly onto the polycarbonate structure. The Arduino is housed in a plastic cover adhered to the greenhouse wall. A future iteration would use a purpose built enclosure with proper cable management and strain relief for a cleaner and more robust physical installation.
Replace mechanical relays with solid state relays:
Faster switching, quieter operation, and longer lifespan than the mechanical relay modules used in this version.
Non-blocking loop:
Refactor all delay() calls to use millis() based timing so the system can respond to sensor changes more frequently without blocking.
Also Built
A second version of this project integrated with Arduino IoT Cloud, adding a real time monitoring dashboard with live sensor data visualisation and manual override controls for each actuator. This version demonstrated supervisory control concepts analogous to SCADA systems: automated responses at the device level with human override capability at the cloud layer.
Skills Demonstrated
Embedded C++ programming on Arduino
Sensor integration and calibration
Multi-actuator control via relay modules and PWM servo signals
Threshold based automation logic
Hardware debugging and serial monitoring
Soldering and physical component mounting
Enclosure design and hardware assembly
Technical documentation
Built With
Arduino IDE
C++
DHT sensor library
Servo library

