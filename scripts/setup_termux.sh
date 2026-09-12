#!/data/data/com.termux/files/usr/bin/bash
set -e
pkg update -y && pkg upgrade -y
pkg install -y python git wget
pip install --upgrade pip
pip install -r server/requirements.txt
echo "[+] Termux setup complete. Start server: python server/server.py"
