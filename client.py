#!/usr/bin/python3

import socket

DEFAULT_PORT = 2000

def main():
    print("Welcome to CriminalsRDancing(Python ver.).\n")

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    while True:
        user_input = input("Please input a server address to connect... ")

        content = user_input.split(':')
        if len(content) == 1:
            port = DEFAULT_PORT
        else:
            port = content[1]

        try:
            s.connect((content[0], port))
        except KeyboardInterrupt:
            print("User stop connecting.")
        except BaseException:
            print("An error occured.")
        else:
            print("Connected to the server", user_input, "successfully.")
            break

    print(s.recv(1024))
    s.send(b'echo')
    print(s.recv(1024))

if __name__ == "__main__":
    main()

