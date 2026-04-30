#include "common.h"
#include <ESP32Servo.h>

static Servo myServo;

// ---------------- STATE VARIABLES ----------------
static int angle{0};
static constexpr int stepSize{2};
static bool forward{true};

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
    // Declare variables once at top
    bool manualMode{handleButton()};
    int potValue{0};
    float distance{0};

    // Reset on transition back to auto mode
    if (modeChangedToAuto()) {
        int previousAngle = angle;  // Remember where we were
        angle = 0;
        forward = true;
        myServo.write(angle);
        
        // Calculate time needed: ~2ms per degree is safe for most servos
        int travelDistance = abs(previousAngle - angle);
        int settleTime = travelDistance * 2;  // 2ms per degree
        delay(settleTime);  // Wait for servo to actually reach position
    }

    if (manualMode) {
        // ---------------- MANUAL MODE ----------------
        potValue = analogRead(POT_PIN);
        angle = map(potValue, 0, 4095, 180, 0);
        
        myServo.write(angle);
        delay(30);  // Reduced for faster response
        
        distance = getDistance();
        
        Serial.print(angle);
        Serial.print(",");
        Serial.println(distance);
        
        delay(15);
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
        delay(30);  // Reduced - just enough for servo to start moving

        // Take measurement
        distance = getDistance();

        // Output for Processing
        Serial.print(angle);
        Serial.print(",");
        Serial.println(distance);

        delay(15);  // Small delay between readings
    }
}
