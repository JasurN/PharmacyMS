#ifndef PHARMACYMS_DATABASE_H
#define PHARMACYMS_DATABASE_H
#include </usr/include/mysql/mysql.h>
#include "stdio.h"

#include "stdbool.h"
#define TRUE 1
#define FALSE 0
#define serverAddr "localhost"
#define dbUser "root"
#define dbPassword "malika"
#define dbName "pharmacy"

void finish_with_error(MYSQL * con);
bool authorization(char* login_id, char* login_password);
void addUser(char *user_id, char *user_name, char *user_adress, char * user_contact,
             int type, MYSQL *con);
MYSQL* connectToDB();

#endif //PHARMACYMS_DATABASE_H
