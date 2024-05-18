import socket
import threading

def send_message():
    while True:
        msg = input()
        client.send(msg.encode('utf-8'))

def receive_message():
    while True:
        msg = client.recv(1024)
        print(msg.decode('utf-8'))

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 5555))

send_thread = threading.Thread(target=send_message)
send_thread.start()

receive_thread = threading.Thread(target=receive_message)
receive_thread.start()