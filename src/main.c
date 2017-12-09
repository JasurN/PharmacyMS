#include <stdio.h>
#include "MySqlManager.h"

int main(int argc, char **argv) {

    mysqlConnect("192.168.17.24","admin", "adminos", "University_DB", "SHOW tables;");
    return 0;
}