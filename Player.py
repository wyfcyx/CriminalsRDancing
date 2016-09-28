
import threading

class PlayerThread(threading.Thread):

    def __init__(self, sock, address):
        super().__init__()
        self.sock = sock
        self.address = address

    def run(self):
        print(self, "is running")

    def Listen(self):
        while True:
            data = self.sock.recv(1024)
            if data.lower() == "exit":
                break

        sock.close()


    
    
    
