#pragma once

// set ultrasonic pins of integer type
constexpr int TRIG_PIN{3};
constexpr int ECHO_PIN{4};

// set servo pin
constexpr int SERVO_PIN{5};

// function to ge the distance from the sensor
float getDistance();