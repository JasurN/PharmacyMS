#include "client.h"

int main() {
    //fromServer *fromServerObj = authorizationClient("1124", "12345");
    fromServer *fromServerObj = addNewUser("1130", "12345", "Pharma","Tashkent", "2310000", 2);

    free(fromServerObj);
    return 0;
}
