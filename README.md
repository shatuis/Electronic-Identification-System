# Electronic Identification System for Multirrotor Aircraft

## Table of Contents

- [Overview](#overview)
- [Components](#components)
- [Features](#features)
- [Setup Instructions](#setup-instructions)
- [File Structure](#file-structure)
- [Notes](#notes)
- [License](#license)

## Overview

This project involves designing an electronic identification system for multirrotor aircraft using PIC16F887 microcontroller and ESP8266 module. The system facilitates communication and data exchange between the aircraft and a ground station via UART and WiFi respectively.

## Components

- **PIC16F887 Microcontroller**: Controls system operation and manages EEPROM data storage.
- **ESP8266 Module**: Provides WiFi connectivity to enable remote communication.
- **Sensors and Peripherals**: Connected to PIC16F887 for data acquisition and control.

## Features

- **UART Communication**: Implements serial communication for data exchange with PIC16F887.
- **WiFi Communication**: Utilizes ESP8266 for wireless data transfer between the aircraft and ground station.
- **EEPROM Data Storage**: Stores configuration and identification data persistently.
- **Web Interface**: Provides a web-based interface for monitoring and control.

## Setup Instructions

### Hardware Setup:

1. Connect PIC16F887 to necessary sensors and peripherals.
2. Interface ESP8266 module with PIC16F887 for WiFi communication.
3. Ensure proper power supply and grounding.

### Software Setup:

1. Configure PIC16F887 microcontroller using MPLAB IDE or similar.
2. Upload PIC16F887 firmware (`Main.C`) to the microcontroller.
3. Configure ESP8266 using Arduino IDE with necessary libraries.

## File Structure

- `Main.C`: Contains the main firmware for PIC16F887 microcontroller.
- `ESP8266_Code.ino`: Arduino sketch for ESP8266 module.
- `lib_usart_pic16_v1.0/usart_pic16.h`: Library for UART communication on PIC16F887.
- `README.md`: This file, providing an overview of the project.

## Notes

- Ensure proper grounding and isolation of electronic components to prevent interference.
- Regularly update firmware and software libraries for enhanced performance and security.
- Refer to datasheets and documentation for detailed specifications and usage guidelines.

## License

This project is developed by **Jorge Luis Gomez Perez** (GitHub: [Your GitHub Shatuis]). It is intended for personal portfolio use and cannot be copied or used without permission.