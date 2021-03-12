#define BUFFER_SIZE 1000

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h> 


typedef struct server_info {
    int server_socket;
    struct sockaddr_in server_address;
    unsigned port; 
} server_info_t;

void* server_listen(void* arg) {
    server_info_t *server_info = (server_info_t*)(arg);
    int server_socket = server_info->server_socket; 
    struct sockaddr_in server_address = server_info->server_address; 
    unsigned port = server_info->port; 

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
    

    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_address; 
    while (1) {
        
        socklen_t client_len = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_len);
        
        if (client_socket != -1) {
            printf("connected to socket!\n");
        }

        size_t num_bytes_read;
        while ((num_bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) { //TODO wrap recv call 
            printf("%s\n", buffer);
        }
        close(client_socket);
    }

    return NULL; 
}

//thread: read user input from stdin and broadcast to server 
void* read_input (void* arg) {	
    int* arg_intp = (int*)(arg); 
    int client_socket = *arg_intp;
    while (1) {
        char* line_buf = NULL; 
        size_t line_buf_size = 0;
        int line_size = getline(&line_buf, &line_buf_size, stdin); 
        if (line_size == -1) {
            break;
        }
        line_buf[line_size-1] = '\0';
        send(client_socket, line_buf, line_size, 0); 
    }
    return NULL;
}

int main(int argc, char **argv) {
    // Some influence taken from https://stackoverflow.com/questions/307692/how-to-open-and-use-a-socket-in-c
    struct protoent *protoent;
    char *protoname = "tcp";
    int server_socket; 
    struct sockaddr_in server_address;
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
    
    //attempt to connect to server, if error, this proc assumes role as server 
    int cl_connect = connect(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (cl_connect == -1) { //TODO MAKE errno check for ECONNREFUSED
        server_info_t server_info;
        server_info.server_address = server_address; 
        server_info.server_socket = server_socket; 
        server_info.port = port; 
        pthread_t server_thread; 
        pthread_create(&server_thread, NULL, server_listen, (void*)(&server_info));
        pthread_join(server_thread, NULL); 
    } else {
        printf("connected to server!\n");
        pthread_t user_thread; 
        pthread_create(&user_thread, NULL, read_input, (void*)(&server_socket));
        pthread_join(user_thread, NULL); 
    }

    close(server_socket);    
    return 0;
}
