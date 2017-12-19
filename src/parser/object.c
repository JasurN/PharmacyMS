//
// Created by malika on 12/18/17.
//
#include "stdlib.h"
#include "object.h"
#define MAX_SIZE 30

void *object_parser(char *tablename, MYSQL_RES *result)
{
    if (strcmp(tablename, "medicine") == 0)
        return medicine_parser(result);
    if (strcmp(tablename, "inventory") == 0)
        return inventory_parser(result);
    if (strcmp(tablename, "journal") == 0)
        return journal_parser(result);
    if (strcmp(tablename, "drugstore") == 0)
        return drugstore_parser(result);
    if (strcmp(tablename, "company") == 0)
        return company_parser(result);
    if (strcmp(tablename, "authorization") == 0)
        return user_parser(result);
}
void *user_parser(MYSQL_RES *result){
    MYSQL_ROW row;
    struct authorizing *user;
    int i = 0;
    user = (struct authorizing *)malloc(sizeof(struct authorizing));
    while ((row = mysql_fetch_row(result))) {
        strncpy(user->login, row[0],MAX_SIZE) ;
        strncpy(user->password, row[1], MAX_SIZE);
        user->type = (uid_t) atoi( row[2]);

       i++;
    }
    return user;
}

void *company_parser(MYSQL_RES *result) {
    MYSQL_ROW row;
    //int num_fields = mysql_num_fields(result);
    my_ulonglong num_rows = mysql_num_rows(result);
    struct auth_back **stores;
    stores = (struct auth_back **) malloc(sizeof(struct auth_back *) * num_rows);
    struct auth_back *store;
    int i = 0;
    while ((row = mysql_fetch_row(result))) {
        store = malloc(sizeof(struct auth_back *));
        strncpy(store->id, row[0], MAX_SIZE);
        strncpy(store->name, row[1],MAX_SIZE);
        strncpy(store->address, row[2],MAX_TEXT);
        strncpy(store->contact, row[3],MAX_SIZE);

        stores[i] = store;
        i++;
    }
    return stores;
}

void *drugstore_parser(MYSQL_RES *result) {
    MYSQL_ROW row;
    //int num_fields = mysql_num_fields(result);
    my_ulonglong num_rows = mysql_num_rows(result);
    struct auth_back **stores;
    stores = (struct auth_back **) malloc(sizeof(struct auth_back *) * num_rows);
    struct auth_back *store;
    int i = 0;
    while ((row = mysql_fetch_row(result))) {
        store = malloc(sizeof(struct auth_back *));
        strncpy(store->id, row[0],MAX_SIZE);
        strncpy(store->name, row[1],MAX_SIZE);
        strncpy(store->address, row[2],MAX_TEXT);
        strncpy(store->contact, row[3],MAX_SIZE);

        stores[i] = store;
        i++;
    }
    return stores;
}
void *medicine_parser(MYSQL_RES *result)
{
    MYSQL_ROW row;
    //int num_fields = mysql_num_fields(result);
    my_ulonglong num_rows = mysql_num_rows(result);
    struct search_back **medicines;
    medicines = (struct search_back**) malloc(sizeof(struct search_back*) * num_rows);
    struct search_back *medicine;
    int i=0;
    while ((row = mysql_fetch_row(result))) {
        medicine = malloc(sizeof(struct search_back*));
        strncpy(medicine->med_id, row[0], MAX_SIZE);
        strncpy(medicine->name, row[1], MAX_SIZE);
        strncpy(medicine->description, row[2], MAX_TEXT);
        medicine->price = atof(row[3]);
        strncpy(medicine->comp_id, row[4],MAX_SIZE);

        medicines[i] = medicine;
        i++;
    }
    return medicines;
}

void *inventory_parser(MYSQL_RES *result)
{
    MYSQL_ROW row;
    my_ulonglong num_rows = mysql_num_rows(result);
    struct search_back_inventory **medicines;
    medicines = (struct search_back_inventory**) malloc(sizeof(struct search_back_inventory*) * num_rows);
    struct search_back_inventory *medicine;
    medicine = malloc(sizeof(struct search_back_inventory*));
    int i=0;
    while ((row = mysql_fetch_row(result))) {
        strncpy(medicine->store_id, row[0],MAX_SIZE);
        strncpy(medicine->med_id, row[1],MAX_SIZE);
        strncpy(medicine->name, row[2],MAX_SIZE);
        medicine->quantity = atoi(row[3]);

        medicines[i] = medicine;
        i++;
    }
    return medicines;
}

void *journal_parser(MYSQL_RES *result)
{
    MYSQL_ROW row;
    my_ulonglong num_rows = mysql_num_rows(result);
    struct purchase_back **medicines;
    medicines = (struct purchase_back**) malloc(sizeof(struct purchase_back*) * num_rows);
    struct purchase_back *medicine;
    int i=0;
    while ((row = mysql_fetch_row(result))) {
        medicine = malloc(sizeof(struct purchase_back*));
        strncpy(medicine->trans_id, row[0], MAX_SIZE);
        strncpy(medicine->trans_date, row[1], MAX_SIZE);
        strncpy(medicine->comp_id, row[2], MAX_SIZE);
        strncpy(medicine->store_id, row[3], MAX_SIZE);
        strncpy(medicine->med_id, row[4], MAX_SIZE);
        medicine->quantity=atoi(row[5]);

        medicines[i] = medicine;
        i++;
    }
    return medicines;
}


//struct search_back {
//    int isExist;
//    char med_id[MAX_SIZE];
//    char name[MAX_SIZE];
//    char description[MAX_TEXT];
//    float price;
//    char comp_id[MAX_SIZE];
//};