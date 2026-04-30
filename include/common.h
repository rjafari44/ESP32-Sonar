#pragma once

// Ultrasonic sensor pins
const int ECHO_PIN = 4;
const int TRIG_PIN = 5;

// Servo pin
const int SERVO_PIN = 10;

// Mode control pins
const int BUTTON_PIN = 8;
const int POT_PIN = 1;

// Functions
float getDistance();
bool handleButton();              // returns current mode (true = manual)
bool modeChangedToAuto();         // detects manual → auto transition