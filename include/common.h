#pragma once

// Ultrasonic sensor pins
const int TRIG_PIN = 3;
const int ECHO_PIN = 4;

// Servo pin
const int SERVO_PIN = 10;

// Mode control pins
const int BUTTON_PIN = 8;
const int POT_PIN = 5;

// Functions
float getDistance();
bool handleButton();              // returns current mode (true = manual)
bool modeChangedToAuto();         // detects manual → auto transition