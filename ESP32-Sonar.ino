#include "common.h"
#include <ESP32Servo.h>

static Servo myServo;

// ---------------- STATE VARIABLES ----------------
static int angle = 0;
static const int stepSize = 2;
static bool forward = true;

void setup() {
    Serial.begin(115200);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(POT_PIN, INPUT);

    myServo.attach(SERVO_PIN);

    // Initialize to starting position
    angle = 0;
    myServo.write(angle);
    delay(500);
}

void loop() {
    bool manualMode = handleButton();

    // Reset on transition back to auto mode
    if (modeChangedToAuto()) {
        angle = 0;
        forward = true;
        myServo.write(angle);
        delay(100);
    }

    if (manualMode) {
        // ---------------- MANUAL MODE ----------------
        int potValue = analogRead(POT_PIN);
        angle = map(potValue, 0, 4095, 180, 0);  // FLIPPED: 0→180, 4095→0
        
        myServo.write(angle);
        delay(50);
        
        float distance = getDistance();
        
        Serial.print(angle);
        Serial.print(",");
        Serial.println(distance);
        
        delay(30);
    } 
    else {
        // ---------------- AUTO SWEEP MODE ----------------
        
        // Update angle
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

        // Move servo
        myServo.write(angle);
        delay(50);

        // Take measurement
        float distance = getDistance();

        // Output for Processing
        Serial.print(angle);
        Serial.print(",");
        Serial.println(distance);

        delay(30);
    }
}
