#include "client.h"
#include "../parser/request_parser.h"

int main() {
    fromServer* fromServerObj = authorizationClient("admin", "lol");

    printf("name %s", fromServerObj->authorization.name);

    return 0;
}
