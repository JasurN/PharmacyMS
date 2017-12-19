//
// Created by malika on 12/18/17.
//
#include "stdlib.h"
#include "object.h"


void *object_parser(char *tablename, MYSQL_RES *result)
{
    if (strcmp(tablename, "medicine") == 0)
        return medicine_parser(result);
    if (strcmp(tablename, "inventory") == 0)
        return inventory_parser(result);
    if (strcmp(tablename, "journal") == 0)
        return journal_parser(result);
}

void *medicine_parser(MYSQL_RES *result)
{
    MYSQL_ROW row;
    //int num_fields = mysql_num_fields(result);
    my_ulonglong num_rows = mysql_num_rows(result);
    struct search_back **medicines;
    medicines = (struct search_back**) malloc(sizeof(struct search_back*) * num_rows);
    struct search_back *medicine;
    medicine = malloc(sizeof(struct search_back*));
    int i=0;
    while ((row = mysql_fetch_row(result))) {
//        medicine->med_id = row[0];
//        medicine->name = row[1];
//        medicine->description = row[2];
//        medicine->price = atof(row[3]);
//        medicine->comp_id = row[4];


        medicines[i] = medicine;
        i++;
    }
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
//        medicine->store_id = row[0];
//        medicine->med_id = row[1];
//        medicine->name = row[2];
//        medicine->quantity = atoi(row[3]);

        medicines[i] = medicine;
        i++;
    }
}
void *journal_parser(MYSQL_RES *result)
{
    MYSQL_ROW row;
    my_ulonglong num_rows = mysql_num_rows(result);
    struct purchase_back **medicines;
    medicines = (struct purchase_back**) malloc(sizeof(struct purchase_back*) * num_rows);
    struct purchase_back *medicine;
    medicine = malloc(sizeof(struct purchase_back*));
    int i=0;
    while ((row = mysql_fetch_row(result))) {
/*        medicine->trans_id = row[0];
        medicine->trans_date = row[1];
        medicine->comp_id = row[2];
        medicine->store_id = row[3];
        medicine->med_id=row[4];
        medicine->quantity=atoi(row[5]);*/

        medicines[i] = medicine;
        i++;
    }
}

//struct search_back {
//    int isExist;
//    char med_id[MAX_SIZE];
//    char name[MAX_SIZE];
//    char description[MAX_TEXT];
//    float price;
//    char comp_id[MAX_SIZE];
//};