#include "client.h"
#include "../parser/request_parser.h"

int main() {

    //fromServer *fromServerObj = authorizationClient("1124", "12345");
    //fromServer *fromServerObj = orderNewMedecine("Parasetamol", 99, "1127");
    fromServer *fromServerObj = viewCompanyMedicine("1123");
    printf("%s", fromServerObj->medicine[0].name);
            free(fromServerObj);
    return 0;
}
