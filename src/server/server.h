#ifndef PHARMACYMS_SERVER_H
#define PHARMACYMS_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "../parser/request_parser.h"
#include "../define/define.h"
#include "../dbManagement/dbManagement.h"

#define PORT 5000
#define TRUE 1
#define FALSE 0
#define MAX_CLIENT 100
#define MAX_SIZE_BUFF 2048

typedef struct {
    struct sockaddr_in addr;    // Client remote address
    int connfd;                 // Connection file descriptor
    int uid;                    // Client unique identifier
} client_t;

void queue_add(client_t *);
void startServer();
void *connection_handler(void*);
size_t str_length(const char*);
char * jsonParser(const char *);
toClient* requestHandler(fromClient *);
toClient* authorizationServer(fromClient *);

toClient* searchInDbServer(fromClient *);
toClient* searchCompanyInventory(fromClient *);
toClient* showInventoryDrugStore(fromClient *);
toClient* showCompanyOrders(fromClient *);
toClient* showInventoryServer(fromClient *);
toClient* produceMedicine(fromClient *);
toClient* orderMedicine(fromClient *);

#endif //PHARMACYMS_SERVER_H
