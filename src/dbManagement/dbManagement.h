#ifndef PHARMACYMS_DATABASE_H
#define PHARMACYMS_DATABASE_H
#include </usr/include/mysql/mysql.h>
#include "stdio.h"

#include "stdbool.h"
#define TRUE 1
#define FALSE 0
#define serverAddr "localhost"
#define dbUser "root"
#define dbPassword "Azikinhatashkent"
#define dbName "PharmacyDB"

void finish_with_error(MYSQL * con);
bool authorization(char* login_id, char* login_password);
void addUser(char *user_id, char *user_password, char *user_name, char *user_adress, char * user_contact,
             int type);
MYSQL* connectToDB();
void *searchFromTable(char *id, char *tablename, char *colname);

#endif //PHARMACYMS_DATABASE_H
