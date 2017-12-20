#include "client.h"
#include "../parser/request_parser.h"

int main() {
    //fromServer* fromServerObj = searchCompanyInventory("Teraflu");

    toClient *toClientObj = viewOrders("1124");
    printf("trans id %s", toClientObj->journal->trans_id);


    fromServer *fromServerObj = orderNewMedecine("Teraflu", 10);
    return 0;
}
