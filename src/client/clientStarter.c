#include "client.h"

int main() {
    fromServer* fromServerObj = authorizationClient("1121", "12345");

    free(fromServerObj);
    return 0;
}
