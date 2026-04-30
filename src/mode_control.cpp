#include "common.h"
#include <Arduino.h>

// ---------------- Shared state (must be at file scope) ----------------
static bool manualMode{false};  // Shared between handleButton() and modeChangedToAuto()

// ---------------- button handling ----------------
bool handleButton() {
    // Button debouncing state - local to this function
    static bool lastReading{HIGH};
    static bool stableState{HIGH};
    static unsigned long lastDebounceTime{0};
    static constexpr unsigned long debounceDelay{10};  // Reduced for faster response
    
    bool reading{digitalRead(BUTTON_PIN)};
    unsigned long now{millis()};

    if (reading != lastReading) {
        lastDebounceTime = now;
    }

    if ((now - lastDebounceTime) > debounceDelay) {
        if (reading != stableState) {
            stableState = reading;

            if (stableState == LOW) {
                manualMode = !manualMode;
            }
        }
    }

    lastReading = reading;

    return manualMode;
}

// ---------------- transition detection ----------------
bool modeChangedToAuto() {
    // Transition tracking - local to this function
    static bool lastModeSnapshot{false};
    
    bool currentMode{manualMode};
    bool transitioned{lastModeSnapshot && !currentMode};

    lastModeSnapshot = currentMode;

    return transitioned;
}