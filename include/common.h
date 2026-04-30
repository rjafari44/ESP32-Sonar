#pragma once

// Ultrasonic sensor pins
constexpr int ECHO_PIN{4};
constexpr int TRIG_PIN{5};

// Servo pin
constexpr int SERVO_PIN{10};

// Mode control pins
constexpr int BUTTON_PIN{8};
constexpr int POT_PIN{1};

// Functions
float getDistance();
bool handleButton();              // returns current mode (true = manual)
bool modeChangedToAuto();         // detects manual → auto transition