#include "client.h"

int main() {
    fromServer* fromServerObj = authorizationClient("22", "22");

    free(fromServerObj);
    return 0;
}
