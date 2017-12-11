#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <pthread.h>
#define PORT 5000
#define TRUE 1
#define FALSE 0
#define MAX_CLIENT 100
#define MAX_SIZE 2048

static int id_counter = 10;

typedef struct {
    struct sockaddr_in addr;    // Client remote address
    int connfd;                 // Connection file descriptor
    int uid;                    // Client unique identifier
} client_t;

void queue_add(client_t *);
void server();
void *connection_handler(void*);
size_t str_length(const char*);

client_t* clients[MAX_CLIENT];

int main() {
    server();
    return 0;
}

void server() {
    int server_fd, new_socket, addrlen;
    struct sockaddr_in server, client;
    pthread_t client_thread;

    printf("CREATING SERVER SOCKET...");
    // create a socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == FALSE || server_fd == -1) {
        perror("\tsocket creation failed!!!");
        exit(EXIT_FAILURE);
    }
    printf("\tDONE!!!\n");

    // assigning types of the socket created using 'struct sockaddr_in'
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    printf("BINDING SERVER SOCKET TO PORT 8080...");
    // binding socket to the port 8080 using bind()
    if(bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("\tDONE!!!\n");

    printf("SERVER LISTENING ON PORT %d FOR NEW CONNECTION...", PORT);
    if(listen(server_fd, 5) < 0) {
        perror("socket listen failed");
        exit(EXIT_FAILURE);
    }
    printf("\tDONE!!!\n");

    // accepting the incoming connection
    addrlen = sizeof(struct sockaddr_in);
    printf("WAITING FOR CONNECTIONS...\n");
    while ((new_socket = accept(server_fd, (struct sockaddr *) &client, (socklen_t *) &addrlen))) {
        printf("CONNECTION ACCEPTED!!!\n");

        // Creating thread for a new client (*cli)
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->addr = client;
        cli->connfd = new_socket;
        cli->uid = id_counter++;

        // Adding client to the queue
        queue_add(cli);

        // Handling the new client (new_sock)
        if(pthread_create(&client_thread, NULL, connection_handler, (void *) cli) < 0) {
            perror("could not create thread");
            exit(EXIT_FAILURE);
        }
        // Join the thread to avoid memory leak
        pthread_join(client_thread, NULL);
        printf("HANDLER ASSIGNED!!!\n");
    }

    if(new_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
}

void *connection_handler(void* sock_desc) {
    // Get the socket descriptor to server_fd
    client_t *cli = (client_t*) sock_desc;
    int valRead = 0;
    //char buf[MAX_SIZE] = {0};

    const char* my_json_string = "{\n"
            "    \"name\": \"Jack (\\\"Bee\\\") Nimble\",\n"
            "    \"format\": {\n"
            "        \"type\":       \"rect\",\n"
            "        \"width\":      1920,\n"
            "        \"height\":     1080,\n"
            "        \"interlace\":  false,\n"
            "        \"frame rate\": 24\n"
            "    }\n"
            "}";

    //valRead = (int) recv(cli->connfd, buf, MAX_SIZE, 0);

    //printf("%s\n", buf);

    send(cli->connfd, my_json_string, str_length(my_json_string), 0);

/*
 *  while(1) {
 *
 *  Here can code that can be edited
 *
 *
 *
 *  }
 * */

    if(valRead == FALSE) {
        printf("CLIENT DISCONNECTED!!!\n");
        fflush(stdout);
    } else if(valRead == -1) {
        perror("receive failed");
    }
    // Close the socket
    close(cli->connfd);
    // Free the socket descriptor
    free(sock_desc);
    return 0;
}

void queue_add(client_t* client) {
    int i;
    for (i = 0; i < MAX_CLIENT; ++i) {
        if(!clients[i]) {
            clients[i] = client;
            return;
        }
    }
}

size_t str_length(const char* buf) {
    size_t i;
    for (i = 0; buf[i] != '\0'; ++i);
    return i;
}