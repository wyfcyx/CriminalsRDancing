#!/usr/bin/python3

import socket
import threading
import time

from Player import PlayerThread

DEFAULT_PORT = 2000

def main():

    localhost = '127.0.0.1'

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    port = input("Select a port to listen (default is 2000): ")
    if not port:
        port = DEFAULT_PORT
    else:
        port = int(port)

    s.bind((localhost, port))

    s.listen(10)
    print("\nStart listening on port", port, "...")
    print("Waiting for connection...")

    while True:
        (sock, addr) = s.accept()
        PlayerThread(sock, addr).start()

if __name__ == "__main__":
    main()

