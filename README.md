# Secure UDP Communication using DTLS

## 📌 Project Description
This project demonstrates secure communication between a client and server using UDP with DTLS (Datagram Transport Layer Security). It ensures data confidentiality and integrity over an unreliable network.

## 🎯 Objectives
- Implement UDP socket communication
- Add security using DTLS protocol
- Perform secure client-server data exchange

## ⚙️ Technologies Used
- C Programming
- OpenSSL Library
- Socket Programming (UDP)
- DTLS Protocol

## 📂 Project Structure
- `server.c` → DTLS server implementation
- `client.c` → DTLS client implementation
- `server.crt` → Server certificate (optional)

## 🚀 How to Run

### 1️⃣ Compile the code
gcc server.c -o server -lssl -lcrypto
gcc client.c -o client -lssl -lcrypto

### 2️⃣ Run the server
./server

### 3️⃣ Run the client (in another terminal)
./client

## 🔐 Security Note
Private keys are not included in this repository for security reasons. DTLS uses certificates and private keys for encryption.

## 📡 Output
- Secure DTLS handshake
- Encrypted message exchange between client and server

## 👨‍💻 Author
Your Name
