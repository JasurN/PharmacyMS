#ifndef COMPANY_H
#define COMPANY_H_H

struct Company
{
    char company_id[15];
    char company_name[25];
    char company_address[50];
    char company_contact[25];
    char company_password[25];
};
// struct medicine which will hold information about medicine
struct Medicine
{
    char med_id[15];
    char med_name[25];
    char med_description[250];
    double med_price;
    char company_id[15];
};


void insertNewMedicine(struct Medicine newMedicine);     // the insertNewMedicine function declaration
void viewOrders();
void showInventory();
#endif // COMPANY_F