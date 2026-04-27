#include "common.h"

#define TRIG_PIN 5
#define ECHO_PIN 18
#define SERVO_PIN 13

int angle = 0;
int stepSize = 2;
bool forward = true;

void setup() {
    Serial.begin(115200);

    setupServo(SERVO_PIN);
    setupUltrasonic(TRIG_PIN, ECHO_PIN);

    Serial.println("Sonar system starting...");
}

void loop() {
    setServoAngle(angle);

    delay(50); // allow servo to settle

    float distance = getDistance();

    // Debug + Processing output
    Serial.print("ANGLE:");
    Serial.print(angle);
    Serial.print(",DIST:");
    Serial.println(distance);

    // Sweep logic
    if (forward) {
        angle += stepSize;
        if (angle >= 180) {
            angle = 180;
            forward = false;
        }
    } else {
        angle -= stepSize;
        if (angle <= 0) {
            angle = 0;
            forward = true;
        }
    }

    delay(30);
}