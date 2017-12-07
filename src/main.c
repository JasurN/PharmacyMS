#include <stdio.h>
#include "MySqlManager.h"
int main(int argc, char **argv) {

    printf("%s", "Hello World!");
    printf("MySQL client version: %s\n", mysql_get_client_info());
    mysqlConnect();
    return 0;
}