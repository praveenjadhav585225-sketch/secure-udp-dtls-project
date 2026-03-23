import socket
import json
from cryptography.fernet import Fernet
from datetime import datetime

# 🔑 Encryption key
key = b'e3r8_uDR0gbnCuk7nL903al4n7LgzrjoOy4p18_dXQM='
cipher = Fernet(key)

# Thresholds
CPU_THRESHOLD = 80
RAM_THRESHOLD = 85
DISK_THRESHOLD = 90

# Create UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", 9999))

print("🔐 Advanced Secure Server Started...\n")

# Log file
log_file = "server_log.txt"

while True:
    try:
        data, addr = sock.recvfrom(4096)

        # 🔓 Decrypt
        decrypted = cipher.decrypt(data)

        # Convert JSON
        message = json.loads(decrypted.decode())

        client_id = message["client_id"]
        cpu = message["cpu"]
        ram = message["ram"]
        disk = message["disk"]

        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        log_msg = f"[{timestamp}] Client {client_id} ({addr[0]}) -> CPU:{cpu}% RAM:{ram}% DISK:{disk}%"
        print(log_msg)

        # Save log
        with open(log_file, "a") as f:
            f.write(log_msg + "\n")

        # 🚨 Alerts
        if cpu > CPU_THRESHOLD:
            print(f"⚠ ALERT: High CPU from Client {client_id}")

        if ram > RAM_THRESHOLD:
            print(f"⚠ ALERT: High RAM from Client {client_id}")

        if disk > DISK_THRESHOLD:
            print(f"⚠ ALERT: High DISK from Client {client_id}")

    except Exception as e:
        print("❌ Error:", e)
