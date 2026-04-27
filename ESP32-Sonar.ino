#include "common.h"
#include <ESP32Servo.h>

static Servo myServo;

void setup() {
    Serial.begin(115200);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    myServo.attach(SERVO_PIN);

    Serial.println("Sonar system starting...");

}

void loop() {
    static int angle{};
    static int stepSize{2};
    static bool forward{true};

    myServo.write(angle);

    delay(50); // allow servo to settle

    float distance = getDistance();

    // processing output
    Serial.print(angle);
    Serial.print(",");
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