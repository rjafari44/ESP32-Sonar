#include <Arduino.h>
#include <ESP32Servo.h>
#include "common.h"

static Servo myServo;
static int servoPin;

void setupServo(int pin) {
    servoPin = pin;
    myServo.attach(servoPin);
}

void setServoAngle(int angle) {
    myServo.write(angle);
}