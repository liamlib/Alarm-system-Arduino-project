# Arduino Alarm System

This is a customizable alarm system built using Arduino Mega, designed to detect motion using ultrasonic and IR sensors, and trigger a buzzer alarm when intrusions are detected. The system can be armed or disarmed using a keypad. Additional plans include LCD/LED display support, remote control, and Wi-Fi notifications.

---

## Project Structure

### Components

#### Motion Detection
- **Ultrasonic Sensor (HC-SR04)**
- **IR Sensor (Infrared)**

#### Alarming
- **Buzzer**

#### Operating
- **4x4 Keypad**

#### Core Control
- **Arduino Mega**

#### Other Components
- Wires  
- OLED display (future upgrade)  
- Battery  

---

## System Functionality

### Features
- Motion detection via ultrasonic and infrared sensors
- Password-protected activation/deactivation via keypad
- Sound alarm with buzzer
- Password input displayed via 7-segment display (using digital pins)

### Future Features
- Add LCD or Dot Matrix Display to show keypad input and status
- Integrate ESP32/ESP8266 for Wi-Fi notifications
- Enable remote disarming using IR remote or phone
- Multiple password attempts and lockout system

---

## Wiring Overview

### Key Connections
| Component         | Pin on Arduino Mega     |
|------------------|-------------------------|
| Keypad Rows      | 9, 8, 7, 6              |
| Keypad Columns   | 5, 4, 3, 2              |
| Ultrasonic TRIG  | 10                      |
| Ultrasonic ECHO  | 11                      |
| Buzzer           | 12                      |
| 7-Segment Display| 22, 24, 26, 28, 30, 32, 34, 36 |

See the included schematic image `IMG_3545.png` for detailed physical and architectural layouts.

---

## Schematic Overview

The schematic on the whiteboard breaks down into:

### Architectural
A simplified diagram of how the components are wired together on the Arduino Mega.

### Physical (Front & Back)
- **Front**: Keypad mounted for user interaction.
- **Back**: Contains Arduino Mega, sensors, buzzer, and optional OLED display or Wi-Fi module.

---

## Arduino Code Overview

The logic includes:
- A predefined password: `{1, 2, 3, 4}`
- Keypad input validation
- Ultrasonic distance checking
- Buzzer alert if intruder detected
- 7-segment display feedback for entered digits

The sketch begins serial communication, initializes the keypad, sensor, and buzzer, and then continuously checks for input and sensor distance.

You can upload the provided `AlarmSystem.ino` to your Arduino Mega using the Arduino IDE.

---

## Getting Started

### Requirements
- Arduino IDE
- Arduino Mega board
- Breadboard and jumper wires
- All hardware components listed above

### Upload Steps
1. Connect your Arduino Mega via USB
2. Open `AlarmSystem.ino` in Arduino IDE
3. Select the correct board and port
4. Upload the sketch

---

## Future Enhancements

- Add ESP32 for cloud or app-based alert systems
- Add Dot Matrix to show current state & countdown timers
- Enable remote control using an IR remote module
- Add multi-level passwords or fingerprint module

---

## Reference Image

![System Schematic](IMG_3545.png)

---

## Author

**Sheelagh Liberboim**  
Built with love for learning, prototyping, and security tech.
