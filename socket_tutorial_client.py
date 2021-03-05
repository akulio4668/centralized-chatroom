import socket

def strip_bit_str(bit_str):
    return str(bit_str)[2:-1]

s = socket.socket()

port = int(input("Connect on port: "))

s.connect(('127.0.0.1', port))

player_name = input("Player name is: ")
s.send(b'NewPlayer ' + str.encode(player_name))

player_byte_name = str.encode(player_name)

while(True):
    try:
        print("What would you like to do?")
        print(" - Create New Game")
        print(" - Get Players")
        print(" - Get Games")
        print(" - Exit")

        curr_action = input()

        if curr_action == "Create New Game":
            s.send(b'NewGame ' + player_byte_name)
            print("New game has been created!\n")

        if curr_action == "Get Players":
            s.send(b'GetPlayers ' + player_byte_name)
            print("Getting players...")
            players = strip_bit_str(s.recv(1024)).split()
            print("Players: ")
            for player in players:
                print(" - " + player)

        if curr_action == "Get Games":
            s.send(b'GetGames ' + player_byte_name)
            print("Getting games...")
            game_string = strip_bit_str(s.recv(1024))
            games = [] if game_string == "Empty" else game_string.split()
            print("Games: ")
            for game in games:
                print(" - " + game)

        if curr_action == "Exit":
            s.send(b'Exit ' + player_byte_name)
            print("Thanks for playing!")
            s.close()
            break
        
    except KeyboardInterrupt:
        s.send(b'Exit ' + player_byte_name)
        print("Thanks for playing!")
        s.close()
        break
