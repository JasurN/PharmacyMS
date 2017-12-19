//
// Created by malika on 12/18/17.
//
#include "stdlib.h"
#include "object.h"
#include "request_parser.h"

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
    if (strcmp(tablename, "auth+comp") == 0)
        return user_parser(result);
}

void *user_parser(MYSQL_RES *result){
    MYSQL_ROW row;
    toClient *user;
    user = (toClient *)malloc(sizeof(toClient));
    user->authorization.isExist = FALSE;
    while ((row = mysql_fetch_row(result))) {
        strncpy(user->authorization.id, row[0],MAX_SIZE);
        if((user->authorization.user_type = (uid_t) atoi( row[2])) == ADMIN) {
            strncpy(user->authorization.name, "", MAX_SIZE);
            strncpy(user->authorization.address, "", MAX_TEXT);
            strncpy(user->authorization.contact, "", MAX_SIZE);
            break;
        }
        strncpy(user->authorization.name, row[3], MAX_SIZE);
        strncpy(user->authorization.address, row[4], MAX_TEXT);
        strncpy(user->authorization.contact, row[5], MAX_SIZE);
        user->authorization.isExist = TRUE;
    }
    return user;
}

void *company_parser(MYSQL_RES *result) {
    MYSQL_ROW row;
    toClient **stores;
    my_ulonglong num_rows = mysql_num_rows(result);
    stores = (toClient **) malloc(sizeof(toClient *) * num_rows);
    toClient *store = malloc(sizeof(toClient *));
    store->authorization.isExist = FALSE;
    int i = 0;
    while ((row = mysql_fetch_row(result))) {
        strncpy(store->authorization.id, row[0], MAX_SIZE);
        strncpy(store->authorization.name, row[1],MAX_SIZE);
        strncpy(store->authorization.address, row[2],MAX_TEXT);
        strncpy(store->authorization.contact, row[3],MAX_SIZE);
        store->authorization.user_type = 1;
        store->authorization.isExist = TRUE;
        stores[i] = store;
        store = malloc(sizeof(toClient *));
        i++;
    }
    return stores;
}

void *drugstore_parser(MYSQL_RES *result) {
    MYSQL_ROW row;
    my_ulonglong num_rows = mysql_num_rows(result);
    toClient **stores;
    stores = (toClient **) malloc(sizeof(toClient *) * num_rows);
    toClient *store = malloc(sizeof(toClient *));
    store->authorization.isExist=FALSE;
    int i = 0;
    while ((row = mysql_fetch_row(result))) {
        strncpy(store->authorization.id, row[0],MAX_SIZE);
        strncpy(store->authorization.name, row[1],MAX_SIZE);
        strncpy(store->authorization.address, row[2],MAX_TEXT);
        strncpy(store->authorization.contact, row[3],MAX_SIZE);
        store->authorization.user_type=2;
        store->authorization.isExist=TRUE;
        stores[i] = store;
        store = malloc(sizeof(toClient *));
        i++;
    }
    return stores;
}

void *medicine_parser(MYSQL_RES *result)
{
    MYSQL_ROW row;
    toClient *medicine;
    medicine = (toClient *) malloc(sizeof(toClient ) );

    medicine->search.isExist=FALSE;

    while ((row = mysql_fetch_row(result))) {

        strncpy(medicine->search.med_id, row[0], MAX_SIZE);
        strncpy(medicine->search.name, row[1], MAX_SIZE);
        strncpy(medicine->search.description, row[2], MAX_TEXT);
        medicine->search.price = atof(row[3]);
        strncpy(medicine->search.comp_id, row[4],MAX_SIZE);
        medicine->search.isExist=TRUE;

    }
    return medicine;
}

void *inventory_parser(MYSQL_RES *result)
{
    MYSQL_ROW row;
    my_ulonglong num_rows = mysql_num_rows(result);
    toClient *medicine;
    medicine = (toClient *) malloc(sizeof(toClient));
    medicine->search_inventory = (struct search_back_inventory *)malloc(sizeof(struct search_back_inventory) * num_rows);
    int i=0;
    while ((row = mysql_fetch_row(result))) {
        strncpy(medicine->search_inventory[i].store_id, row[0],MAX_SIZE);
        strncpy(medicine->search_inventory[i].med_id, row[1],MAX_SIZE);
        strncpy(medicine->search_inventory[i].name, row[2],MAX_SIZE);
        medicine->search_inventory[i].quantity = atoi(row[3]);
        i++;
    }
    return medicine;
}

void *journal_parser(MYSQL_RES *result)
{
    MYSQL_ROW row;
    my_ulonglong num_rows = mysql_num_rows(result);
    toClient *medicine;
    medicine = (toClient *) malloc(sizeof(toClient));
    medicine->journal = (struct journal_back*) malloc(sizeof(struct journal_back*) * num_rows);
    int i=0;
    while ((row = mysql_fetch_row(result))) {
        medicine = malloc(sizeof(struct purchase_back*));
        strncpy(medicine->journal[i].trans_id, row[0], MAX_SIZE);
        strncpy(medicine->journal[i].trans_date, row[1], MAX_SIZE);
        strncpy(medicine->journal[i].comp_id, row[2], MAX_SIZE);
        strncpy(medicine->journal[i].store_id, row[3], MAX_SIZE);
        strncpy(medicine->journal[i].med_id, row[4], MAX_SIZE);
        medicine->journal[i].quantity=atoi(row[5]);
        i++;
    }
    return medicine;
}


//struct search_back {
//    int isExist;
//    char med_id[MAX_SIZE];
//    char name[MAX_SIZE];
//    char description[MAX_TEXT];
//    float price;
//    char comp_id[MAX_SIZE];
//};