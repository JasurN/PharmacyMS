#include "client.h"

int main() {

    //fromServer *fromServerObj = authorizationClient("1124", "12345");
    fromServer *fromServerObj = orderNewMedecine("Parasetamol", 99, "1127");
            free(fromServerObj);
    return 0;
}
