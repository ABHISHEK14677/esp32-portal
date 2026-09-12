#!/bin/bash
PORT=${1:-/dev/ttyUSB0}
~/bin/arduino-cli upload -p "$PORT" --fqbn esp32:esp32:esp32 firmware/portal
