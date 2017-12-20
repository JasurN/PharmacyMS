#include "client.h"
#include "../parser/request_parser.h"

int main() {

    fromServer *fromServerObj = orderNewMedicine("Trimol", 100, "m001");
            free(fromServerObj);
    return 0;
}
