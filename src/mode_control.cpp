#include "common.h"
#include <Arduino.h>

// ---------------- internal state ----------------
static bool manualMode{false};

static bool lastReading{HIGH};
static bool stableState{HIGH};
static unsigned long lastDebounceTime{0};
static const unsigned long debounceDelay{50};

static bool lastModeSnapshot{false};

// ---------------- button handling ----------------
bool handleButton() {
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
    bool currentMode{manualMode};
    bool transitioned{lastModeSnapshot && !currentMode};

    lastModeSnapshot = currentMode;

    return transitioned;
}