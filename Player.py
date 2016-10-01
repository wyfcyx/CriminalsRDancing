
import threading


class PlayerThread(threading.Thread):

    names(["system", "admin"])

    def __init__(self, sock, address):
        super().__init__()
        self.sock = sock
        self.address = address
        self.name = ""

    def run(self):
        print(self, "is running")

    def Listen(self):
        while True:
            data = self.sock.recv(1024)
            if data.lower() == "exit":
                break

        sock.close()

    def GetName():
        while True:
            # Do something to get name
            # and storage into self.name
            if self.name in PlayerThread.names:
                # Do something to re-get the name.
            else:
                PlayerThread.add(self.name)
                break

