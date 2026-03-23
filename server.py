import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", 9999))

while True:
    data, addr = sock.recvfrom(1024)
    message = data.decode()
    print(f"Received from {addr}: {message}")

    # Simple threshold
    cpu = float(message.split(",")[0].split(":")[1])
    if cpu > 80:
        print("ALERT: High CPU Usage!")
