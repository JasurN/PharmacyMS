#include "client.h"

int main() {
    fromServer* fromServerObj = searchCompanyInventory("Teraflu");

    free(fromServerObj);
    return 0;
}
