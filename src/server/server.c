#include "server.h"
#include "../parser/request_parser.h"

static int id_counter = 10;

client_t *clients[MAX_CLIENT];

void startServer() {
    int server_fd, new_socket, addrlen;
    int opt = 1;
    struct sockaddr_in server, client;
    pthread_t client_thread;

    printf("CREATING SERVER SOCKET...");
    // create a socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == FALSE || server_fd == -1) {
        perror("\tsocket creation failed!!!");
        exit(EXIT_FAILURE);
    }
    printf("\tDONE!!!\n");
// Forcefully attaching socket to the port 5000
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    // assigning types of the socket created using 'struct sockaddr_in'
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    printf("BINDING SERVER SOCKET TO PORT %d...", PORT);
    // binding socket to the port 5000 using bind()
    if (bind(server_fd, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("\tDONE!!!\n");

    printf("SERVER LISTENING ON PORT %d FOR NEW CONNECTION...", PORT);
    if (listen(server_fd, 5) < 0) {
        perror("socket listen failed");
        exit(EXIT_FAILURE);
    }
    printf("\tDONE!!!\n");

    // accepting the incoming connection
    addrlen = sizeof(struct sockaddr_in);
    printf("WAITING FOR CONNECTIONS...\n");
    while ((new_socket = accept(server_fd, (struct sockaddr *) &client, (socklen_t *) &addrlen))) {
        printf("CONNECTION ACCEPTED!!!\n");

        // Creating thread for a new clientOn (*cli)
        client_t *cli = (client_t *) malloc(sizeof(client_t));
        cli->addr = client;
        cli->connfd = new_socket;
        cli->uid = id_counter++;

        // Adding clientOn to the queue
        queue_add(cli);

        // Handling the new clientOn (new_sock)
        if (pthread_create(&client_thread, NULL, connection_handler, (void *) cli) < 0) {
            perror("could not create thread");
            exit(EXIT_FAILURE);
        }
        // Join the thread to avoid memory leak
        pthread_join(client_thread, NULL);
        printf("HANDLER ASSIGNED!!!\n");
    }

    if (new_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
}

void *connection_handler(void *sock_desc) {
    // Get the socket descriptor to server_fd
    client_t *cli = (client_t *) sock_desc;
    int valRead = 0;
    char buf[MAX_SIZE_BUFF] = {0};

    valRead = (int) recv(cli->connfd, buf, MAX_SIZE_BUFF, 0);

    char *serverMessage = jsonParser(buf);

    send(cli->connfd, serverMessage, str_length(serverMessage), 0);

/*
 *  while(1) {
 *
 *  Here can code that can be edited
 *
 *
 *
 *  }
 * */

    if (valRead == FALSE) {
        printf("CLIENT DISCONNECTED!!!\n");
        fflush(stdout);
    } else if (valRead == -1) {
        perror("receive failed");
    }
    // Close the socket
    close(cli->connfd);
    // Free the socket descriptor and buffer string
    free(serverMessage);
    free(sock_desc);
    return 0;
}

void queue_add(client_t *client) {
    int i;
    for (i = 0; i < MAX_CLIENT; ++i) {
        if (!clients[i]) {
            clients[i] = client;
            return;
        }
    }
}

size_t str_length(const char *buf) {
    size_t i;
    for (i = 0; buf[i] != '\0'; ++i);
    return i;
}

char *jsonParser(const char *jsonStr) {
    fromClient *fromClientObj = (fromClient *) malloc(sizeof(fromClient));

    clientStrToStruct(jsonStr, fromClientObj);

    toClient *toClientObj = requestHandler(fromClientObj);
    char *serverMessageToClient = serverStructToStr(toClientObj);

    free(toClientObj);
    free(fromClientObj);
    return serverMessageToClient;
}

toClient *requestHandler(fromClient *fromClientObj) {
    toClient *toClientObj = (toClient *) malloc(sizeof(toClient));
    if (fromClientObj->type == AUTHORIZATION) {

        toClientObj = authorizationServer(fromClientObj);
    } else if (fromClientObj->type == SEARCH) {
        toClientObj = searchInDbServer(fromClientObj);
    } else if (fromClientObj->type == INVENTORY) {

    } else if (fromClientObj->type == PURCHASE) {

    } else if (fromClientObj->type == JOURNAL) {

    }

    return toClientObj;
}

toClient *authorizationServer(fromClient *fromClientObj) { //todo: assign value of user from database
    int auth_result = authorization(fromClientObj->authorization.login,
                                    fromClientObj->authorization.password);
    toClient *toClientObj = (toClient *) malloc(sizeof(toClient));

    toClientObj->type = AUTHORIZATION;
    if (auth_result == TRUE) {
        toClientObj->authorization.isExist = TRUE;
        strcpy(toClientObj->authorization.name, "Jasurbek");
        strcpy(toClientObj->authorization.contact, "998979997507");
        strcpy(toClientObj->authorization.id, "u1510326");
        strcpy(toClientObj->authorization.address, "Sebzor");
        return toClientObj;
    }
        toClientObj->authorization.isExist = FALSE;
    return toClientObj;
}

toClient* searchInDbServer(fromClient *fromClientObj) {
    searchByName(fromClientObj->search.name);
}

