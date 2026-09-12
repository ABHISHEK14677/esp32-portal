#!/bin/bash
set -e
mkdir -p ~/bin && cd ~/bin
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
export PATH=$PATH:~/bin

arduino-cli config init
arduino-cli config add board_manager.additional_urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
arduino-cli core update-index
arduino-cli core install esp32:esp32
echo "[+] arduino-cli + ESP32 core installed"
