#ifndef PHARMACYMS_DATABASE_H
#define PHARMACYMS_DATABASE_H
#include </usr/include/mysql/mysql.h>
#include "stdio.h"

#include "stdbool.h"
#define TRUE 1
#define FALSE 0
#define serverAddr "localhost"
#define dbUser "admin"
#define dbPassword "adminos"
#define dbName "PharmacyDB"

MYSQL* connectToDB();
void finish_with_error(MYSQL * con);
bool authorization(char* login_id, char* login_password);
void addUser(char *user_id, char *user_password, char *user_name, char *user_adress, char * user_contact,
             int type);
bool isExistAlready(char *user_id, char *tablename,char *field);
void addNewMedicine(char *med_id, char *med_name, char *description, float price, char *comp_id);
void *searchFromTable(char *id, char *tablename, char *colname);
void viewInventory(char *id);
void viewOrders(char *id);
void viewStoreInventory(char *id);
void searchByName(char *med_name);
void searchById(char *med_id);
void orderRegister(char *med_id, char *comp_id, char *store_id, int quantity)
#endif //PHARMACYMS_DATABASE_H
