#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    struct protoent *protoent;
    char *protoname = "tcp";
    int client_socket;
    struct sockaddr_in server_address;
    unsigned port = 12345u;

    protoent = getprotobyname(protoname);
    if (!protoent) {
        perror("protoent not found!");
        exit(EXIT_FAILURE);
    }

    client_socket = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
    if (client_socket == -1) {
        perror("socket not created!");
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(port);

    int cl_connect = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (cl_connect == -1) {
        perror("could not connect to server!");
        exit(EXIT_FAILURE);
    } else {
        printf("connected to server!\n");
    }

    close(client_socket);

}