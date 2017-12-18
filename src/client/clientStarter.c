#include "client.h"

int main() {
   /* char login[10],password[10];
    printf("Please enter login: ");
    scanf("%s", login);
    printf("Please enter password: ");
    scanf("%s", password);*/
    toServer *toServerObj = (toServer *)malloc(sizeof(toServerObj));

    toServerObj->type = AUTHORIZATION;
    strcpy(toServerObj->authorization.login, "admin");
    strcpy(toServerObj->authorization.password, "admin");

    char * strToServer = clientStructToStr(toServerObj);

    clientStart(strToServer);
    return 0;
}
