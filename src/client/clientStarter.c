#include "client.h"
#include "../parser/request_parser.h"

int main() {
    toServer *toServerObj = (toServer *)malloc(sizeof(toServer));
    toServerObj->type = AUTHORIZATION;
    strcpy(toServerObj->authorization.password, "admin");
    strcpy(toServerObj->authorization.login, "admin");

    char* strToServer = clientStructToStr(toServerObj);

    char * strFromServer = clientStart(strToServer);
//struct from server with autorization
    fromServer *fromServerObj =  (fromServer *)malloc(sizeof(fromServer));
    printf("Client side: %s\n", strFromServer);
    serverStrToStruct(strFromServer, fromServerObj);
//there your can use it.

    free(strFromServer);
    free(toServerObj);
    free(fromServerObj);
    return 0;
}
