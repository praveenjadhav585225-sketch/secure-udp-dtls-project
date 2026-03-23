import socket
import psutil
import time
import json
import sys
from cryptography.fernet import Fernet

# 🔑 Same key
key = b'e3r8_uDR0gbnCuk7nL903al4n7LgzrjoOy4p18_dXQM='
cipher = Fernet(key)

# Check ID
if len(sys.argv) != 2:
    print("Usage: python3 client_s.py <client_id>")
    sys.exit()

client_id = sys.argv[1]

SERVER_IP = "127.0.0.1"
PORT = 9999

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"🔐 Advanced Client {client_id} started...\n")

while True:
    try:
        # 📊 Collect system metrics
        data = {
            "client_id": client_id,
            "cpu": psutil.cpu_percent(interval=1),
            "ram": psutil.virtual_memory().percent,
            "disk": psutil.disk_usage('/').percent
        }

        message = json.dumps(data)

        # 🔐 Encrypt
        encrypted = cipher.encrypt(message.encode())

        # 📡 Send
        sock.sendto(encrypted, (SERVER_IP, PORT))

        print(f"[Client {client_id}] Sent encrypted data")

        time.sleep(5)

    except Exception as e:
        print("❌ Error:", e)
        time.sleep(5)
