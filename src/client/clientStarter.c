#include "client.h"

int main() {
    fromServer* fromServerObj = searchCompanyInventory("Trimol");


    free(fromServerObj);
    return 0;
}
