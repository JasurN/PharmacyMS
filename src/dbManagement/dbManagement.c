#include "dbManagement.h"
#include "../define/define.h"
#include "../parser/object.h"

MYSQL *connectToDB() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    if (mysql_real_connect(con, serverAddr, dbUser, dbPassword,
                           dbName, 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }
    return con;
}

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

bool authorization(char *login_id, char *login_password) {
    MYSQL *con = connectToDB();
    char query[1024];
    sprintf(query, "SELECT * FROM authorization WHERE id = '%s' AND password = '%s'", login_id, login_password);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);
    my_ulonglong numrows = mysql_num_rows(result);

    if (numrows == 0) {
        return FALSE;
    } else {
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
        //MYSQL_FIELD *field;
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < num_fields; i++) {
                printf("%s ", row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
    }
    return TRUE;
}
bool isExistAlready(char *user_id, char *tablename,char *field){

    MYSQL *con = connectToDB();
    char query[1024];
    sprintf(query, "SELECT * FROM %s WHERE  %s = '%s'", tablename, field, user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    my_ulonglong numrows = mysql_num_rows(result);
    if (numrows==0)
        return FALSE;
    else
        return TRUE;
}

void addUser(char *user_id,char *user_password, char *user_name, char *user_adress, char *user_contact, int type) {
     MYSQL *con =connectToDB();
    if(!isExistAlready(user_id, "authorization", "id")){
        char query[1024];
        sprintf(query,"INSERT INTO authorization VALUES('%s','%s', %d)", user_id, user_password, type);
        if (mysql_query(con, query)) {
        finish_with_error(con);
        }
        char query1[1024];
        if (type == COMPANY) {
            sprintf(query1,"INSERT INTO company VALUES('%s','%s', '%s','%s')", user_id, user_name, user_adress, user_contact);
            if (mysql_query(con, query1)) {
            finish_with_error(con);
            }
        } else if (type == DRUGSTORE) {
            sprintf(query1,"INSERT INTO drugstore VALUES('%s','%s', '%s','%s')", user_id, user_name, user_adress, user_contact);
            if (mysql_query(con, query1)) {
            finish_with_error(con);
            }
        }
    }
    else printf("User is already exist!");
}

// company queries

void addNewMedicine(char *med_id, char *med_name, char *description, float price, char *comp_id){
    MYSQL *con =connectToDB();
    if(!isExistAlready(med_id, "medicine", "comp_id")) {
        char query[1024];
        sprintf(query,"INSERT INTO medicine VALUES('%s', '%s', '%s', %f, '%s')",med_id, med_name, description, price, comp_id);
        if (mysql_query(con, query)) {
            finish_with_error(con);
        }
    }
    else
        printf("Id is already exists");

}
void *searchFromTable(char *id, char *tablename, char *colname){
    MYSQL *con =connectToDB();
    char query[1024];
    sprintf(query,"SELECT * FROM %s WHERE %s='%s'", tablename, colname, id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    return object_parser(tablename, result);
}
void viewInventory(char *id){
    searchFromTable(id, "medicine", "comp_name");
}
void viewOrders(char *id){
    searchFromTable(id, "journal", "comp_name");
}

// Store queries

void viewStoreInventory(char *id){
    searchFromTable(id, "inventory","store_id" );
}
void searchByName(char *med_name){
    searchFromTable(med_name, "medicine", "med_name");
}
void searchById(char *med_id){
    searchFromTable(med_id, "medicine", "med_id");
}
void orderRegister(char *med_id, char *comp_id, char *store_id, int quantity){
    MYSQL *con=connectToDB();
    char query[1024];

    sprintf(query,"INSERT INTO journal(comp_id, store_id, med_id, quantity, status) VALUES ('%s', '%s', '%s', %d, %d)",
            comp_id, store_id, med_id, quantity, 0 );
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

}


/*
int main(int argc, char **argv)
{
   /* char id[10], description[20], name[10], adress[30], comp_id[30];
    float price;
    scanf("%s",id);
    scanf("%s" ,name);
    scanf("%s" ,description);
    scanf("%f",&price );
    scanf("%s" ,comp_id);
 /* bool a =authorization(id, pass);
  if(a)
  printf("registered");
  else
  printf("not found");
    viewOrders("hi123");
  
  exit(0);
}
*/

