#include "client.h"

int main() {
    //fromServer *fromServerObj = authorizationClient("1124", "12345");
    fromServer *fromServerObj = viewOrder("1124");

    free(fromServerObj);
    return 0;
}
