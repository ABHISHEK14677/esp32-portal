#!/bin/bash
set -e
~/bin/arduino-cli compile --fqbn esp32:esp32:esp32 firmware/portal
