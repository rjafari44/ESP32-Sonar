#pragma once

// set ultrasonic pins of integer type
constexpr int trigPin{3};
constexpr int echoPin{4};

// set servo pin
constexpr int SERVO_PIN{5};

// --- Setup ---
void setupServo(int pin);
void setupUltrasonic(int trigPin, int echoPin);

// --- Servo control ---
void setServoAngle(int angle);

// --- Sensor ---
float getDistance();