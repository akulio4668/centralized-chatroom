#define BUFFER_SIZE 1000

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

int main(int argc, char **argv) {
    // Some influence taken from https://stackoverflow.com/questions/307692/how-to-open-and-use-a-socket-in-c
    char buffer[BUFFER_SIZE];
    struct protoent *protoent;
    char *protoname = "tcp";
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    unsigned port = 12345u;

    protoent = getprotobyname(protoname);
    if (!protoent) {
        perror("protoent not found!");
        exit(EXIT_FAILURE);
    }

    server_socket = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
    if (server_socket == -1) {
        perror("server socket not created!");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    int serv_bind = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (serv_bind < 0) {
        perror("server socket could not bind!");
        exit(EXIT_FAILURE);
    }

    int serv_listen = listen(server_socket, 3);
    if (serv_listen < 0) {
        perror("server socket could not listen!");
        exit(EXIT_FAILURE);
    }
    printf("listening on port %d\n", port);

    while (1) {
        socklen_t client_len = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_len);
        
        if (client_socket != -1) {
            printf("connected to socket!\n");
        }

        size_t num_bytes_read;
        while ((num_bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
            printf("%s\n", buffer);
        }
        close(client_socket);
    }

    close(server_socket);

    return 0;
}
