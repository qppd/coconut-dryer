# Coconut Dryer

## Overview

An intelligent coconut drying system designed for the Southern Luzon State University (SLSU) Lucban BSME program. This Arduino-based embedded system provides automated temperature, humidity, and moisture control for efficient coconut drying operations using PID control algorithms and real-time sensor monitoring.

## Table of Contents

- [Features](#features)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
- [Software Dependencies](#software-dependencies)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Project Structure](#project-structure)
- [3D Models and Manufacturing](#3d-models-and-manufacturing)
- [Technical Specifications](#technical-specifications)
- [Contributing](#contributing)
- [License](#license)
- [Developer](#developer)

## Features

### Core Functionality
- **Automated Drying Process**: PID-controlled temperature regulation for optimal drying conditions
- **Multi-Parameter Monitoring**: Real-time tracking of temperature, humidity, and moisture levels
- **Smart Control System**: Automatic shutdown when target moisture levels are achieved
- **User Interface**: 20x4 LCD display with intuitive menu navigation
- **Status Indicators**: Real-time system status and operational feedback

### Technical Features
- **PID Control Algorithm**: Precise temperature control using industry-standard PID implementation
- **Sensor Integration**: SHT31 temperature/humidity sensor and soil moisture monitoring
- **Relay Control**: Multiple solid-state relay (SSR) control for heating elements and fans
- **Push Button Interface**: Multi-button navigation system for parameter adjustment
- **Serial Monitoring**: Real-time debugging and monitoring via serial communication

## System Architecture

The system employs a modular architecture with separate components for different functionalities:

```
CoconutDryer.ino (Main Controller)
├── LCD_CONFIG.h (Display Management)
├── SHT31_CONFIG.h (Temperature/Humidity Sensor)
├── SOIL_MOISTURE_CONFIG.h (Moisture Monitoring)
├── RELAY_CONFIG.h (Actuator Control)
├── PID_CONFIG.h (Control Algorithm)
├── BUZZER_CONFIG.h (Audio Feedback)
├── PUSH_BUTTON_CONFIG.h (User Input)
└── LIB.h (Utility Functions)
```

## Hardware Components

### Essential Components
- **Microcontroller**: Arduino-compatible board (ESP32/Arduino Uno)
- **Display**: 20x4 I2C LCD (Address: 0x27)
- **Temperature/Humidity Sensor**: Adafruit SHT31 (I2C Address: 0x44)
- **Moisture Sensor**: Analog soil moisture sensor
- **Relays**: Multiple solid-state relays for heating elements and fans
- **User Interface**: Push button array for navigation
- **Audio Feedback**: Buzzer for system alerts

### Power Requirements
- Operating Voltage: 5V/12V (depending on relay configuration)
- Power Consumption: Variable based on heating element usage
- Backup Power: Optional battery backup for data retention

## Software Dependencies

### Arduino Libraries
```cpp
#include <LiquidCrystal_I2C.h>  // LCD display control
#include <Adafruit_SHT31.h>     // Temperature/humidity sensor
#include <PID_v1.h>             // PID control algorithm
#include <Wire.h>               // I2C communication
```

### Installation Requirements
- Arduino IDE 1.8.x or higher
- ESP32/Arduino board support packages
- Required libraries (installable via Arduino Library Manager)

## Installation

### Hardware Setup
1. **Circuit Assembly**: Connect components according to the provided schematic
2. **Sensor Calibration**: Calibrate moisture sensors for coconut-specific readings
3. **Relay Configuration**: Set up solid-state relays for heating elements and fans
4. **Display Connection**: Wire I2C LCD to appropriate pins

### Software Installation
1. **Clone Repository**:
   ```bash
   git clone https://github.com/qppd/coconut-dryer.git
   cd coconut-dryer
   ```

2. **Open Arduino IDE**: Load `source/CoconutDryer/CoconutDryer.ino`

3. **Install Dependencies**: Install required libraries via Library Manager

4. **Board Configuration**: Select appropriate board and port

5. **Upload Firmware**: Compile and upload to microcontroller

## Usage

### Initial Setup
1. **Power On**: Connect power supply and initialize system
2. **Calibration**: Allow sensors to stabilize (approximately 30 seconds)
3. **Parameter Setting**: Use push buttons to set desired parameters:
   - Temperature Setpoint: Default 60°C
   - Humidity Setpoint: Default 20%
   - Moisture Setpoint: Default 6%

### Operation Modes
- **Standby Mode**: System monitoring without active drying
- **Drying Mode**: Active temperature control and moisture monitoring
- **Completion Mode**: Automatic shutdown when target moisture is achieved

### Display Information
```
T:XX.X°C    SP:XX.X°C
H:XX.X%     SP:XX.X%
M:XX.X%     SP:XX.X%
Status: [Standby/Drying]
```

## Configuration

### PID Parameters
Located in `PID_CONFIG.h`:
```cpp
double THRESHOLD_1 = 4;   // Proportional gain
double THRESHOLD_2 = 0;   // Integral gain
double THRESHOLD_3 = 22;  // Derivative gain
```

### Sensor Calibration
Modify calibration constants in respective configuration files:
- SHT31: Temperature offset adjustment
- Moisture sensor: Analog-to-percentage conversion

### Operational Parameters
Default setpoints can be modified in main code:
```cpp
double TEMPERATURE_SETPOINT = 60;  // °C
double HUMIDITY_SETPOINT = 20;     // %
double MOISTURE_SETPOINT = 6;      // %
```

## Project Structure

```
coconut-dryer/
├── LICENSE                          # Project license
├── README.md                        # Project documentation
├── models/                          # 3D models and manufacturing files
│   ├── gcode/                      # G-code files for 3D printing
│   │   ├── Coconut_Dryer_Board_Mount.gcode
│   │   ├── Coconut_Dryer_Button_Lock.gcode
│   │   ├── Coconut_Dryer_Case_Cover.gcode
│   │   └── Coconut_Dryer_Case.gcode
│   └── stl/                        # STL files for 3D printing
└── source/                         # Source code
    └── CoconutDryer/              # Main Arduino project
        ├── CoconutDryer.ino       # Main program file
        ├── BUZZER_CONFIG.h        # Audio feedback configuration
        ├── LCD_CONFIG.h           # Display configuration
        ├── LIB.h                  # Utility functions
        ├── PID_CONFIG.h           # PID control configuration
        ├── PUSH_BUTTON_CONFIG.h   # Input handling
        ├── RELAY_CONFIG.h         # Actuator control
        ├── SHT31_CONFIG.h         # Temperature/humidity sensor
        ├── SOIL_MOISTURE_CONFIG.h # Moisture sensor configuration
        ├── include/               # Header files
        │   ├── LCDController.h
        │   ├── MoistureSensor.h
        │   ├── RelayController.h
        │   └── TemperatureHumiditySensor.h
        └── src/                   # Implementation files
            ├── LCDController.cpp
            ├── MoistureSensor.cpp
            ├── RelayController.cpp
            └── TemperatureHumiditySensor.cpp
```

## 3D Models and Manufacturing

### Available Models
The project includes complete 3D models for manufacturing:

- **Board Mount**: Secure mounting for electronic components
- **Button Lock**: User interface protection and organization
- **Case Cover**: Protective housing for the control system
- **Main Case**: Primary enclosure for all components

### Manufacturing Files
- **STL Files**: Ready for 3D printing on standard FDM printers
- **G-code Files**: Pre-sliced for common 3D printer configurations
- **Material Recommendations**: PLA or PETG for durability and temperature resistance

## Technical Specifications

### Operating Parameters
- **Temperature Range**: 0-100°C (sensor range)
- **Humidity Range**: 0-100% RH
- **Moisture Detection**: Analog sensing with percentage conversion
- **Control Precision**: ±0.1°C temperature control
- **Response Time**: <60 seconds for temperature stabilization

### Communication Interfaces
- **Serial**: 9600 baud rate for debugging and monitoring
- **I2C**: For sensor and display communication
- **Digital I/O**: Push button inputs and relay outputs

### Performance Characteristics
- **Loop Interval**: 500ms for real-time monitoring
- **PID Update Rate**: Synchronized with main loop
- **Display Refresh**: Real-time parameter updates
- **Auto-completion**: Moisture-based process termination

## Contributing

We welcome contributions to improve the Coconut Dryer project. Please follow these guidelines:

### Development Process
1. Fork the repository
2. Create a feature branch
3. Make your changes with proper documentation
4. Test thoroughly with hardware setup
5. Submit a pull request with detailed description

### Code Standards
- Follow Arduino coding conventions
- Document all functions and major code blocks
- Test with actual hardware before submission
- Maintain backward compatibility when possible

## License

This project is open source and available under the [MIT License](LICENSE).

## Developer

**Sajed Lopez Mendoza** - Full Stack Developer & IoT Specialist

### Professional Background
- **Location**: Unisan, Quezon Province, Philippines
- **Specialization**: Embedded Systems, IoT Development, Full-Stack Web Development
- **Experience**: Freelance Developer at QPPD (Quezon Province Programmers/Developers)
- **Education**: Southern Luzon State University (SLSU) Lucban

### Technical Expertise
- **Embedded Systems**: ESP32, Arduino, Raspberry Pi development
- **IoT Solutions**: Sensor integration, real-time monitoring systems
- **Hardware Integration**: 3D printing, PCB design, solar power systems
- **Programming**: C/C++, Python, JavaScript, PHP, Java
- **Machine Learning**: TensorFlow, AI-powered applications
- **Mobile Development**: Android applications with hardware integration

### Notable Projects
- **IoT Smart Fan**: Intelligent climate control system
- **IoT Bike Tracker**: Solar-powered GPS tracking solution
- **CNC Jog Trainer**: GRBL-based CNC machine controller
- **Smart Cabinet**: Advanced automated storage solution
- **Umbrella Holder**: PID-controlled drying system

### Contact Information
- **Email**: quezon.province.pd@gmail.com
- **GitHub**: [github.com/qppd](https://github.com/qppd)
- **Portfolio**: [sajed-mendoza.onrender.com](https://sajed-mendoza.onrender.com/)
- **Facebook**: [facebook.com/qppd.dev](https://facebook.com/qppd.dev)
- **Community**: [facebook.com/QUEZONPROVINCEDEVS](https://facebook.com/QUEZONPROVINCEDEVS)

### Professional Focus
Sajed specializes in creating intelligent, efficient solutions that bridge software and hardware. His work focuses on practical IoT applications, renewable energy integration, and educational technology projects that serve real-world needs in rural and agricultural communities.

---

**Project Status**: Active Development | **Last Updated**: November 2025 | **Version**: 1.0