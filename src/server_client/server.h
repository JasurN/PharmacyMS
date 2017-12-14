#ifndef PHARMACYMS_SERVER_H
#define PHARMACYMS_SERVER_H

typedef struct {
    struct sockaddr_in addr;    // Client remote address
    int connfd;                 // Connection file descriptor
    int uid;                    // Client unique identifier
} client_t;


void queue_add(client_t *);
void server();
void *connection_handler(void*);
size_t str_length(const char*);


#endif //PHARMACYMS_SERVER_H
