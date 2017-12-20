#include "client.h"
#include "../parser/request_parser.h"

int main() {

    //fromServer *fromServerObj = authorizationClient("1124", "12345");
    fromServer *fromServerObj = orderNewMedecine("Trimol", 10, "1125");
    printf("result %d", fromServerObj->purchase.success);
            free(fromServerObj);
    return 0;
}
