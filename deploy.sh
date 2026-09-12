#!/bin/bash
# ============================================================
# esp32-portal — one-command build/flash/verify deployment
# Usage: ./scripts/deploy.sh [PORT]
#   e.g. ./scripts/deploy.sh /dev/ttyUSB0
# ============================================================
set -e

PORT="${1:-/dev/ttyUSB0}"
FQBN="esp32:esp32:esp32"
CLI="$HOME/bin/arduino-cli"
PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SERVER_HOST="127.0.0.1"     # change if server runs on Termux/another box
SERVER_PORT=5000
BAUD=115200

cd "$PROJECT_ROOT"

banner() { echo -e "\n\033[1;36m==== $1 ====\033[0m"; }

# ---------- 0. Preflight ----------
banner "0. Preflight checks"

if [ ! -f firmware/portal/portal.ino ]; then
  echo "[-] firmware/portal/portal.ino not found"; exit 1
fi

if [ ! -f server/server.py ]; then
  echo "[-] server/server.py not found"; exit 1
fi

# Warn if captures would be committed
if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  if ! git check-ignore -q server/captures/captured.txt 2>/dev/null; then
    echo "[!] WARNING: .gitignore not active — captured.txt could leak to Git"
    echo "    Fix .gitignore before operating!"
  else
    echo "[+] .gitignore OK — captures are excluded from Git"
  fi
fi

# ---------- 1. Toolchain ----------
banner "1. Toolchain check"

if [ ! -x "$CLI" ]; then
  echo "[*] arduino-cli missing — running setup"
  bash scripts/setup_arduino_cli.sh
fi
export PATH="$PATH:$HOME/bin"

if ! "$CLI" core list 2>/dev/null | grep -q esp32; then
  echo "[*] ESP32 core missing — installing"
  "$CLI" core install esp32:esp32
fi
echo "[+] Toolchain ready"

# ---------- 2. Build ----------
banner "2. Compiling firmware"

"$CLI" compile --fqbn "$FQBN" firmware/portal
echo "[+] Build OK"

# ---------- 3. Port detection ----------
banner "3. Serial port: $PORT"

if [ ! -e "$PORT" ]; then
  echo "[!] $PORT not found. Available candidates:"
  ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null || echo "[-] none — plug in the ESP32"
  echo "    Re-run: ./scripts/deploy.sh /dev/ttyACM0"
  exit 1
fi

if [ "$USE_SUDO" = "1" ]; then SUDO=sudo; else SUDO=""; fi

# ---------- 4. Flash ----------
banner "4. Uploading firmware"

$SUDO "$CLI" upload -p "$PORT" --fqbn "$FQBN" firmware/portal
echo "[+] Flash OK"

# ---------- 5. Boot verification via serial ----------
banner "5. Verifying boot output (5s)"

timeout 8 "$CLI" monitor -p "$PORT" -c baudrate=$BAUD 2>/dev/null | head -30 || true

# ---------- 6. Server health check ----------
banner "6. Logging server health check"

if curl -s -o /dev/null -w "" "http://$SERVER_HOST:$SERVER_PORT/" 2>/dev/null; then
  echo "[+] Server responding on $SERVER_HOST:$SERVER_PORT"
else
  echo "[!] Server NOT reachable at http://$SERVER_HOST:$SERVER_PORT/"
  echo "    Start it:  python server/server.py"
  echo "    Then test: curl -X POST http://$SERVER_HOST:$SERVER_PORT/log -d 'ssid=t&password=t'"
fi

# ---------- 7. Summary ----------
banner "7. Deployment summary"
cat <<EOF
  Port        : $PORT
  Firmware    : firmware/portal (compiled + flashed)
  AP SSID     : see firmware/portal/config.h
  Portal URL  : http://192.168.4.1 (auto-popup for clients)
  Server      : http://$SERVER_HOST:$SERVER_PORT/log
  Captures    : server/captures/captured.txt  (gitignored)

  Next: power ESP32, start server.py, join AP from a test client.
  Monitor: $CLI monitor -p $PORT -c baudrate=$BAUD
EOF
