#include "client.h"
#include "../parser/request_parser.h"

int main() {
    fromServer* fromServerObj = authorizationClient("admin", "lol");

    free(fromServerObj);
    return 0;
}
