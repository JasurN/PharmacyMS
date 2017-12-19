#include "client.h"

int main() {
    fromServer* fromServerObj = authorizationClient("admin", "admin");
    printf("name :%s\n", fromServerObj->authorization.name);
    free(fromServerObj);
    return 0;
}
