#include "client.h"

char* clientStart(char * clientStr) {
    // Structure to connect to the server
    struct sockaddr_in server;
    int server_fd = 0;
    char buf[MAX_SIZE_BUF] = {0};

    printf("CREATING CLIENT SOCKET...\n");

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)), 0) {
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
        return NULL;
    }

    printf("CLIENT CONNECTING ON PORT %d TO COMMUNICATE WITH SERVER...\n", PORT);
    if(connect(server_fd, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("\nConnection Failed\n");
        return NULL;
    }

    // Send hello message to the sever
    send(server_fd, clientStr, str_length(clientStr), 0);

    recv(server_fd, buf, MAX_SIZE_BUF, 0);

    char* returnToClient = (char *)malloc(sizeof(buf));
    strcpy(returnToClient, buf);
    return returnToClient;
}

size_t str_length(const char* buf) {
    size_t i;
    for (i = 0; buf[i] != '\0'; ++i);
    return i;
}

fromServer* authorizationClient(const char * login, const char * password) {
    toServer *toServerObj = (toServer *)malloc(sizeof(toServer));
    toServerObj->type = AUTHORIZATION;

    strcpy(toServerObj->authorization.login, login);
    strcpy(toServerObj->authorization.password, password);


    char* strToServer = clientStructToStr(toServerObj);

    char * strFromServer = clientStart(strToServer);
//struct from server with autorization
    fromServer *fromServerObj =  (fromServer *)malloc(sizeof(fromServer));
    printf("Client side: %s\n", strFromServer);
    serverStrToStruct(strFromServer, fromServerObj);
//there your can use struct.

    free(strFromServer);
    free(toServerObj);
    return fromServerObj;
}

fromServer* searchCompanyInventory(char* searchString) {
    toServer *toServerObj = (toServer *) malloc(sizeof(toServer));
    toServerObj->type = SEARCH;
    strcpy(toServerObj->search.name, searchString);

    char *strToServer = clientStructToStr(toServerObj);
    char *strFromServer = clientStart(strToServer);

    fromServer *fromServerObj = (fromServer *) malloc(sizeof(fromServer));
    printf("Message from server: %s\n", strFromServer);
    serverStrToStruct(strFromServer, fromServerObj);

    free(toServerObj);
    free(strFromServer);
    return fromServerObj;
}
