#include "client.h"

int clientStart() {
    // Structure to connect to the server
    struct sockaddr_in server;
    int server_info = 0, valread;
    char *hello = "Hello from clientOn!";
    char buf[MAX_SIZE_BUF] = {0};

    printf("CREATING CLIENT SOCKET...\n");

    if((server_info = socket(AF_INET, SOCK_STREAM, 0)), 0) {
        printf("\tsocket creation failed!!!");
        exit(EXIT_FAILURE);
    }
    printf("\tDONE!!!\n");

    printf("DEFINING CLIENT SOCKET FAMILY, ADDRESS & PORT...\n");
    // assigning types of the socket created using 'struct sockaddr_in'
    memset(&server, '0', sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, SERVER_ADDRESS, &server.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    printf("CLIENT CONNECTING ON PORT 8080 TO COMMUNICATE WITH SERVER...\n");
    if(connect(server_info, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("\nConnection Failed\n");
        return -1;
    }
    return server_info;

}
char* sendStrToServer(int server_info, char* messageToServer) {
    // Send hello message to the sever
    send(server_info, messageToServer, str_length(messageToServer), 0);

    recv(server_info, messageToServer, MAX_SIZE_BUF, 0);


    char* returnToClient = (char *)malloc(sizeof(messageToServer));
    strcpy(returnToClient, messageToServer);
    return returnToClient;
}


size_t str_length(const char* buf) {
    size_t i;
    for (i = 0; buf[i] != '\0'; ++i);
    return i;
}
fromServer* authorizationClient(char * login, char * password) {
    toServer *toServerObj = (toServer *)malloc(sizeof(toServer));
    toServerObj->type = AUTHORIZATION;
    strcpy(toServerObj->authorization.password, login);
    strcpy(toServerObj->authorization.login, password);

    char* strToServer = clientStructToStr(toServerObj);

    int server_info = clientStart();

    char* strFromServer = sendStrToServer(server_info, strToServer);
//struct from server with autorization

    fromServer *fromServerObj =  (fromServer *)malloc(sizeof(fromServer));
    printf("Client side: %s\n", strFromServer);
    serverStrToStruct(strFromServer, fromServerObj);
//there your can use it.

    free(strFromServer);
    free(toServerObj);
    return fromServerObj;
}


