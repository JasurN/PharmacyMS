#ifndef CUSTOMER_H_
#define CUSTOMER_H_H

struct Medicine
{
    char med_id[15];
    char med_name[25];
    char med_description[250];
    double med_price;
    char company_id[15];
};

void showCustomerInventory();
void orderMedicine(struct Medicine orderedMedicine);

#endif // CUSTOMER_H_
