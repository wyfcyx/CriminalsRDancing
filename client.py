#!/usr/bin/python3

import socket

DEFAULT_PORT = 2000

def main():
    print("Welcome to CriminalsRDancing(Python ver.).\n")

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    while True:
        user_input = input("Please input a server address to connect... ")
        try:
            try:
                pos = user_input.index(':')
            except ValueError:
                port = DEFAULT_PORT
            else:
                port = int(user_input[pos + 1:])
                user_input = user_input[:pos]

            s.connect((user_input, port))
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

