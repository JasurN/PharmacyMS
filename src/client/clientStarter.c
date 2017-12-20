#include "client.h"

int main() {
    //fromServer* fromServerObj = searchCompanyInventory("Teraflu");
    fromServer* fromServerObj = searchStoreInventory("1125");

            free(fromServerObj);
    return 0;
}
