#!/bin/bash

# Get script directory (where this .sh file actually lives)
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$SCRIPT_DIR/.."

# Ask the user for their ESP32 board
read -p "Enter your ESP32 Port (e.g., /dev/ttyACM0): " PORT

# Compile the code with USB CDC enabled (ESP32-C3)
arduino-cli compile \
  --fqbn esp32:esp32:esp32c3:CDCOnBoot=cdc \
  --build-property "compiler.cpp.extra_flags=-Iinclude" \
  "$PROJECT_DIR"

# Upload the code to the board
arduino-cli upload \
  -p "$PORT" \
  --fqbn esp32:esp32:esp32c3 \
  "$PROJECT_DIR"

# Open the Serial Monitor
arduino-cli monitor \
  -p "$PORT" \
  --config baudrate=115200