#include "common.h"
#include <ESP32Servo.h>

static Servo myServo;

void setup() {
    Serial.begin(115200);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(POT_PIN, INPUT);

    myServo.attach(SERVO_PIN);

    Serial.println("Sonar system starting...");
}

void loop() {
    // ---------------- variables (declared + initialized at top) ----------------
    int angle{0};
    int stepSize{2};
    bool forward{true};
    bool manualMode{false};
    int potValue{0};
    float distance{0};

    // ---------------- mode update ----------------
    manualMode = handleButton();

    // ---------------- AUTO re-entry reset ----------------
    if (modeChangedToAuto()) {
        angle = 0;
        forward = true;
    }

    // ---------------- mode behavior ----------------
    if (manualMode) {
        potValue = analogRead(POT_PIN);
        angle = map(potValue, 0, 4095, 0, 180);
    } 
    else {
        if (forward) {
            angle += stepSize;

            if (angle >= 180) {
                angle = 180;
                forward = false;
            }
        } 
        else {
            angle -= stepSize;

            if (angle <= 0) {
                angle = 0;
                forward = true;
            }
        }
    }

    // ---------------- output ----------------
    myServo.write(angle);

    delay(50);

    distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);

    delay(30);
}