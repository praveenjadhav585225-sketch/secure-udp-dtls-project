import socket
import psutil
import time

server_ip = "127.0.0.1"
server_port = 9999

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    cpu = psutil.cpu_percent()
    ram = psutil.virtual_memory().percent

    message = f"CPU:{cpu},RAM:{ram}"
    sock.sendto(message.encode(), (server_ip, server_port))

    time.sleep(5)
