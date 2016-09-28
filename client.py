#!/usr/bin/python3

import socket

def main():
    print("Welcome to CriminalsRDancing(Python ver.).\n")

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    DEFAULT_PORT = 2000

    while True:
        user_input = input("Please input a server address to connect...")
        try:
            s.connect((user_input, DEFAULT_PORT))
        except KeyboardInterrupt:
            print("User stop connecting.")
        except BaseException:
            print("An error occured.")
        else:
            print("Connected!\n")
            break

    print(s.recv(1024))
    for data in [b'Michael', b'Tracy', b'Sarah']:
        s.send(data)
        print(s.recv(1024))
    s.send(b'exit')
    s.close()

if __name__ == "__main__":
    main()

