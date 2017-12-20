#include "client.h"

int main() {
    //fromServer* fromServerObj = searchCompanyInventory("Teraflu");
    fromServer* fromServerObj = viewOrder("1124");

            free(fromServerObj);
    return 0;
}
