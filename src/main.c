#include <stdio.h>
#include "MySqlManager.h"
int main(int argc, char **argv) {

    printf("%s", "Hello World!");
    mysqlConnect();
    mysqlVersion();
    return 0;
}