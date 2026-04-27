# ESP32 Sonar

A simple sonar-style scanning system using an ESP32-C3, ultrasonic sensor, and servo motor. The sensor sweeps across an arc, measures distance, and streams data to a Processing visualization that displays a real-time radar-style interface. The servo rotates the ultrasonic sensor from 0° to 180°, taking distance measurements at each angle and sending them over serial, creating a physical scanning motion based on sonar principles. This was designed as part of the IEEE program at UCI, [Check them Out!](https://ieee.ics.uci.edu/)

---

## Table of Contents

- [Bill of Materials](#bill-of-materials)
- [Custom Mounts](#custom-mounts)
- [Electrical](#electrical)
- [Processing Setup](#processing-setup)
- [How to Run](#how-to-run)
- [Serial Note](#serial-note)
- [Troubleshooting](#troubleshooting)

---

## Bill of Materials

- ESP32-C3 development board  
- HC-SR04 ultrasonic sensor  
- SG90 servo motor  
- Jumper wires  
- Servo  
- Mounting hardware (appropriate screws)

---

## Custom Mounts

### Servo Mount (Custom)

A custom-designed mount was used to secure the servo and keep it stable during scanning. The STL file is included.

Servo mount assembly:
![diagram](/assets/servo-assembly.png)

### Ultrasonic Sensor Mount

The ultrasonic sensor mount was sourced online and is not included. You will need to download a similar model or design your own.

---

## Electrical

### Overview

This system requires stable power delivery, especially for the servo motor. Power instability is the most common cause of glitches or resets.

The electrical schematic was designed in **LTspice**, and the project includes the LTspice schematic files for reference and modification.

Schematic:
![schematic](/assets/schematic.png)

### Connections

**Ultrasonic Sensor (HC-SR04):**
- VCC → 5V  
- GND → GND  
- TRIG → GPIO 3  
- ECHO → GPIO 4  

**Servo Motor:**
- Signal → GPIO 5  
- VCC → 5V (external recommended but ESP32 can work in light load cases)  
- GND → shared ground with ESP32  

### Power Notes

- Do not rely on ESP32 3.3V for servo power  
- External 5V is strongly recommended for stable operation  
- All grounds must be shared (common ground)  
- Servo noise can affect sensor readings if power is unstable  

---

## Processing Setup

Processing is used to visualize the radar output.

- Download Processing from the official website  
- Open the `.pde` file  
- Select the correct serial port  
- Run the sketch  

The display shows sweep motion, detected objects, and distance scaling.

Sample sonar output on Processing:
![Processing Output]()

---

## How to Run

### 1. Hardware Setup
- Assemble ESP32-C3, servo, and ultrasonic sensor  
- Mount sensor securely on servo  
- Use external 5V power for servo stability  
- Ensure all grounds are shared  

### 2. Flash ESP32-C3
- Uploaded using arduino-cli  
- Arduino IDE workflow may differ depending on system  
- Non-Linux systems may require different setup steps  
- Added shell script to simplify running:
```bash
./run_sonar.sh
```

### 3. Run Visualization
- Open Processing  
- Load `.pde` file  
- Select serial port
- Run the code

---

## Serial Note

Only one program can use the serial port at a time.

If the port is in use:
- Close Serial Monitor  
- Close any terminal using the port  
- Disconnect other serial tools  

Processing will not connect otherwise.

---

## Troubleshooting

- Servo not moving → check external power  
- No data → verify wiring  
- Erratic readings → unstable ground or power noise  
- No connection → serial port already in use or wrong port  

---
