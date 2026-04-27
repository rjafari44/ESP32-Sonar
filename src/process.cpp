#include <Arduino.h>
#include "common.h"

static int trigPinGlobal{};
static int echoPinGlobal{};

void setupUltrasonic(int trigPin, int echoPin) {
    trigPinGlobal = trigPin;
    echoPinGlobal = echoPin;

    pinMode(trigPinGlobal, OUTPUT);
    pinMode(echoPinGlobal, INPUT);
}

float getDistance() {
    digitalWrite(trigPinGlobal, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPinGlobal, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinGlobal, LOW);

    long duration = pulseIn(echoPinGlobal, HIGH, 30000);

    if (duration == 0) {
        return -1;
    }

    float distance = (duration * 0.0343) / 2;
    return distance;
}