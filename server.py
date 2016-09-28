#!/usr/bin/python3

import socket
import threading
import time

connected = 0

def tcplink(sock, addr):
    global connected

    print("Accept new connection from", addr)
    sock.send(b"Welcome")
    while True:
        data = sock.recv(1024)
        time.sleep(1)
        if data == "exit" or not data:
            break
        sock.send(b"Hello, " + data)

    sock.close()
    print("Connection from " + str(addr) + " closed.")
    connected -= 1
    print("Now connected:", connected)

def main():
    global connected

    localhost = '127.0.0.1'

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.bind((localhost, 2000))

    s.listen(10)
    print("Waiting for connection...")

    while True:
        (sock, addr) = s.accept()
        connected += 1
        print("Now connected:" ,connected)
        thread = threading.Thread(target = tcplink, args = (sock, addr))
        thread.start()

if __name__ == "__main__":
    main()

