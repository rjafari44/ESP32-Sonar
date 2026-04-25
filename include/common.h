#pragma once

// include the necessary header files for the servo and arduino nano
#include <Servo.h>

// set ultrasonic pins of integer type
constexpr int trigPin{3};
constexpr int echoPin{4};

// set servo pin
constexpr int SERVO_PIN{5};

// declare the Servo object externally
inline Servo myServo;

// function for processing ultrasonic sensor data
void processData();