#include "client.h"

int main() {
   /* char login[10],password[10];
    printf("Please enter login: ");
    scanf("%s", login);
    printf("Please enter password: ");
    scanf("%s", password);*/
    toServer *toServerObj = (toServer *)malloc(sizeof(toServer));
    toServerObj->type = AUTHORIZATION;
    strcpy(toServerObj->authorization.password, "admin");
    strcpy(toServerObj->authorization.login, "admin");
    //memset(&toServerObj->authorization.password, '0', sizeof(char));
    printf("main: %s\npassword %s\ntype: %d", toServerObj->authorization.login, toServerObj->authorization.password, toServerObj->type);

    char * strToServer = clientStructToStr(toServerObj);

    clientStart(strToServer);
    free(toServerObj);
    return 0;
}
