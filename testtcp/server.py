import socket
import threading

def handle_client(client_socket, addr):
    while True:
        msg = client_socket.recv(1024)
        if not msg:
            break
        formatted_msg = f"Сообщение от {addr[0]}:{addr[1]}: {msg.decode('utf-8')}"
        print(formatted_msg)
        for client in clients:
            if client != client_socket:
                client.send(formatted_msg.encode('utf-8'))

def client_acceptance():
    while True:
        client, addr = server.accept()
        print(f"Установлено соединение с {addr}")
        clients.append(client)
        client_thread = threading.Thread(target=handle_client, args=(client, addr))
        client_thread.start()

def send_to_all(message):
    formatted_msg = f"Сообщение от сервера: {message}"
    print(formatted_msg)
    for client in clients:
        client.send(formatted_msg.encode('utf-8'))

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 5555))
server.listen(5)
print("Сервер запущен и ожидает подключения клиентов...")

clients = []
accept_thread = threading.Thread(target=client_acceptance)
accept_thread.start()