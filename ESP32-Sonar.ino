#include "common.h"
#include <ESP32Servo.h>

// declare servo object
static Servo myServo;

void setup() {
    Serial.begin(115200);

    // setup the ultrasonic sensor
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // setup the servo
    myServo.attach(SERVO_PIN);

    // print for debug
    Serial.println("Sonar system starting...");

}

void loop() {
    static int angle{};        // variable for storing angles to move servo
    static int stepSize{2};    // variable for the amount the servo moves
    static bool forward{true}; // variable for setting the condition of which direction the servo moves

    myServo.write(angle);

    // allow servo to settle
    delay(50);

    // get the distance from the ultrasonic during movement
    float distance = getDistance();

    // processing output
    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);

    // sweep logic for rotating the servo (180 degrees)
    if (forward) { // moving one direction
        angle += stepSize;
        if (angle >= 180) {
            angle = 180;
            forward = false;
        }
    } else { // moving back the other direction
        angle -= stepSize;
        if (angle <= 0) {
            angle = 0;
            forward = true;
        }
    }

    delay(30);
}