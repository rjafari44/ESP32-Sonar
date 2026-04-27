#include "common.h"

void setup() {
    // setup the ultrasonic pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // setup the servo 
    myServo.attach(SERVO_PIN);
    myServo.write(90); // center
    delay(1000);
}

void loop() {
    
}