#include "common.h"
#include <Arduino.h>

// function to ge the distance from the sensor
float getDistance() {
    // ensure clean low signal before trigger
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    // send 10us trigger pulse to start measurement
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // measure echo return time (timeout 30ms)
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);

    if (duration == 0) { // no echo received within timeout
        return -1;
    }

    // convert time to distance (cm), divide by 2 for round trip
    float distance = (duration * 0.0343) / 2;

    return distance;
}