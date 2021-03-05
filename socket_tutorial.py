import socket
import sys
import threading

def strip_bit_str(bit_str):
    return str(bit_str)[2:-1]

player_list = []
games_list = []

def handle_client(conn, addr):
    while True:
        data = strip_bit_str(conn.recv(1024))
        print(data)

        split_data = data.split()

        if split_data[0] == 'NewPlayer':
            player_list.append(split_data[1])

        if split_data[0] == 'NewGame':
            games_list.append(split_data[1])

        if split_data[0] == 'GetPlayers':
            conn.send(str.encode(" ".join(player_list)))

        if split_data[0] == 'GetGames':
            if not len(games_list):
                conn.send(b'Empty')
            else:
                conn.send(str.encode(" ".join(games_list)))

        if split_data[0] == 'Exit':
            player_list.remove(split_data[1])
            conn.close()
            break

try:
    s = socket.socket()
    print("Socket successfully created")
except socket.error as err:
    print("Socket creation failed with error %s" %(err))

port = 12345

s.bind(('', port))
print("Socket bound to %s" %(port))

s.listen(5)
print("Socket is listening")

while True:
    try:
        print(threading.active_count())
        c, addr = s.accept()
    
        print("Got connection from", addr)

        t = threading.Thread(target=handle_client, args=(c,addr))
        t.start()
        
    except KeyboardInterrupt:
        print("Thanks for playing!")
        s.close()
        break
