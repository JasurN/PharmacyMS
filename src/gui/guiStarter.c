#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "../parser/request_parser.h"
#include "../client/client.h"
#define type1 "1"
#define type2 "2"
#define target "Trimol"

struct newMedicine{
    char ID[30];
    char NAME[30];
    double PRICE;
    char DESCRIPTION[300];
    int QUANTITY;
};

struct newMedicine *newMedicineObject;
char userID[4];

GtkBuilder *builder;
GtkWidget *window, *window1, *window2, *window3;
GtkLabel *warnlabel;
GtkTextBuffer *buffer1, *buffer2, *buffer3, *buffer4, *buffer5, *buffer6, *buffer7, *buffer8,*buffer9;
GtkTextIter start, end;
GtkTextIter *iter;

void filltable1(char *id, char *name, char *price, char *desc);

int main(int argc, char **argv) {


    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "../src/gui/login_frame.glade", NULL) == 0) {
        printf(".glade file is not exist");
        return (0);
    }


    window = GTK_WIDGET(gtk_builder_get_object(builder, "logwindow"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show_all(window);
    gtk_main();


    return (0);
}


void on_enter_but_clicked() {
    const char *login;
    const char *password;

    GtkEntry *log = (GtkEntry *) gtk_builder_get_object(builder, "login_field");
    GtkEntry *pass = (GtkEntry *) gtk_builder_get_object(builder, "password_field");
    login = gtk_entry_get_text(log);
    password = gtk_entry_get_text(pass);

    fromServer *fromServerObj = authorizationClient(login, password);

    if (fromServerObj->authorization.isExist == 1) {


        strcpy(userID, fromServerObj->authorization.id);
        if (fromServerObj->authorization.user_type == ADMIN) {
            window1 = GTK_WIDGET(gtk_builder_get_object(builder, "adminWindow"));

            gtk_widget_show_all(window1);
            gtk_widget_destroy(window);

        }

        else if (fromServerObj->authorization.user_type == DRUGSTORE) {
            fromServer *fromServerInventory = searchStoreInventory(fromServerObj->authorization.id);
            char inventory_table[5000]="";
            //Filling Inventory table in Drugstore
            int i=0;
            while(i<struct_length) {
                char temp[500]="";
                strcat(temp, fromServerInventory->search_inventory[i].med_id);
                strcat(temp, "                    ");
                strcat(temp, fromServerInventory->search_inventory[i].name);
                strcat(temp, "                          ");
                char quantity[8];
                sprintf(quantity, "%d", fromServerInventory->search_inventory[i].quantity);
                strcat(temp, quantity);
                strcat(temp, "\n");
                strcat(inventory_table, temp);
                i++;
            }

            GtkTextView *invent_tab = (GtkTextView*) gtk_builder_get_object(builder, "list_view");
            buffer7=gtk_text_view_get_buffer(GTK_TEXT_VIEW(invent_tab));
            gtk_text_buffer_set_text(buffer7, inventory_table, -1);





            window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
            GtkLabel *storename = (GtkLabel *) gtk_builder_get_object(builder, "drugstore");
            gtk_label_set_text(GTK_LABEL(storename), fromServerObj->authorization.name);


            gtk_widget_show_all(window2);
            gtk_widget_destroy(window);

        }
        else if(fromServerObj->authorization.user_type == COMPANY) {

            window3 = GTK_WIDGET(gtk_builder_get_object(builder, "companyWindow"));
            GtkLabel *companyname = (GtkLabel*) gtk_builder_get_object(builder, "comp_name");
            GtkLabel *companyname2 = (GtkLabel*) gtk_builder_get_object(builder, "comp_name2");
            GtkLabel *companyname3 = (GtkLabel*) gtk_builder_get_object(builder, "comp_name3");
            gtk_label_set_text(GTK_LABEL(companyname), fromServerObj->authorization.name);
            gtk_label_set_text(GTK_LABEL(companyname2), fromServerObj->authorization.name);
            gtk_label_set_text(GTK_LABEL(companyname3), fromServerObj->authorization.name);


            gtk_widget_show_all(window3);
            gtk_widget_destroy(window);

            fromServer *viewOrderObj = viewOrder(userID);
            char tableChar[5000] = "";

            int i = 0;
            while (i < struct_length) {
                // Code

                char temp[1000] = "";
                strcat(temp, viewOrderObj->journal[i].trans_id);

                    if(atoi(viewOrderObj->journal[i].trans_id) > 9) {

                        strcat(temp, "                                  ");
                    } else {
                        strcat(temp, "                                ");
                    }

                strcat(temp, viewOrderObj->journal[i].med_id);
                strcat(temp, "                                  ");


                strcat(temp, viewOrderObj->journal[i].store_id);
                strcat(temp, "                                      ");

                char quantity[8];
                sprintf(quantity, "%d", viewOrderObj->journal[i].quantity);
                strcat(temp, quantity);
                strcat(temp, "                                      ");


                strcat(temp, viewOrderObj->journal[i].trans_date);
                strcat(temp, "                  ");

                strcat(temp, "\n");
                strcat(tableChar, temp);
                i++;

            }

            GtkTextView *tablerequest = (GtkTextView *) gtk_builder_get_object(builder, "comReqList");
            buffer6 = gtk_text_view_get_buffer(tablerequest);
            gtk_text_buffer_set_text(buffer6, tableChar, -1);
            free(viewOrderObj  );

        }
    } else {
        GtkLabel *warn = (GtkLabel *) gtk_builder_get_object(builder, "warning");
        const gchar *text = "Login or Password wrong";
        gtk_label_set_text(GTK_LABEL(warn), text);
        g_print("Wrong");

    }
}


void search_but_clicked() {
    printf("it is here");
    newMedicineObject = malloc(sizeof(struct newMedicine));
    const char *searchedtext;
    GtkEntry *searchfield = (GtkEntry *) gtk_builder_get_object(builder, "search_entry");
    searchedtext = gtk_entry_get_text(searchfield);
    if (strcmp(searchedtext, "") != 0) {
        fromServer *fromServerObj = searchCompanyInventory(searchedtext);
        if (fromServerObj->search.isExist == TRUE) {
            char price[30];
            sprintf(price, "%lf", fromServerObj->search.price);
            filltable1(fromServerObj->search.med_id, fromServerObj->search.name,
                       price, fromServerObj->search.description);

            strcpy(newMedicineObject->DESCRIPTION, fromServerObj->search.description);
            strcpy(newMedicineObject->ID, fromServerObj->search.med_id);
            strcpy(newMedicineObject->NAME, fromServerObj->search.name);
            newMedicineObject->PRICE=fromServerObj->search.price;

        }
        free(fromServerObj);
    }
}

char order[1000] = "";

void order_clicked() {
    const char *amount;
    GtkTextView *tab2 = (GtkTextView *) gtk_builder_get_object(builder, "display2");
    GtkEntry *amountfield = (GtkEntry *) gtk_builder_get_object(builder, "amount");
    amount = gtk_entry_get_text(amountfield);


    char temp[500] = "";
    int quantity;
    quantity = atoi(amount);

    orderNewMedicine(newMedicineObject->NAME, quantity, userID);

    strcat(temp, newMedicineObject->ID);
    strcat(temp, "       ");
    strcat(temp, newMedicineObject->NAME);
    strcat(temp, "       ");
    strcat(temp, amount);
    strcat(order, temp);
    strcat(order, "\n");
    buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab2));
    gtk_text_buffer_set_text(buffer2, order, -1);
}

void filltable1(char *id, char *name, char *price, char *desc) {
    char data[800] = "";
    char temp[40] = "";
    const char *space = "          ";
    const char *nextspace = "                         ";
    printf(id);
    strcat(data, id);
    strcat(data, space);
    strcat(data, name);
    strncpy(temp, nextspace, (strlen(nextspace) - strlen(name)));
    strcat(data, temp);
    strcat(data, price);
    memset(temp, 0, 40);
    strcat(data, space);
    strcat(data, desc);

    GtkTextView *tab1 = (GtkTextView *) gtk_builder_get_object(builder, "display1");
    buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab1));
    gtk_text_buffer_set_text(buffer1, data, -1);
}

// this button for registration new user.
void regButClicked()
{
    const char *ID, *password, *name, *contact, *address, *type;
    GtkTextView *pharmlist = (GtkTextView *) gtk_builder_get_object(builder, "adPharmList");
    GtkTextView *comlist = (GtkTextView *) gtk_builder_get_object(builder, "adComList");
    GtkEntry *idfield = (GtkEntry *) gtk_builder_get_object(builder, "adIDEntry");
    GtkEntry *passwordfield = (GtkEntry *) gtk_builder_get_object(builder, "adPasswordEntry");
    GtkEntry *namefield = (GtkEntry *) gtk_builder_get_object(builder, "adNameEntry");
    GtkEntry *contactfield = (GtkEntry *) gtk_builder_get_object(builder, "adContactEntry");
    GtkEntry *addressfield = (GtkEntry *) gtk_builder_get_object(builder, "adAddressEntry");
    GtkEntry *typefield = (GtkEntry *) gtk_builder_get_object(builder, "adTypeEntry");
    ID = gtk_entry_get_text(idfield);
    password = gtk_entry_get_text(passwordfield);
    name = gtk_entry_get_text(namefield);
    type = gtk_entry_get_text(typefield);
    contact = gtk_entry_get_text(contactfield);
    address = gtk_entry_get_text(addressfield);

    addNewUser(ID, password, name, address, contact, atoi(type));
}

void addButClicked() {//todo: Implement. produce new medicine button.
    const char *drugName, *id, *descript, *price;
    GtkTextView *inventlist = (GtkTextView *) gtk_builder_get_object(builder, "comInventList");
    GtkEntry *namefield = (GtkEntry *) gtk_builder_get_object(builder, "comNameEntry");
    GtkEntry *idfield = (GtkEntry *) gtk_builder_get_object(builder, "comIDEntr");
    GtkEntry *descriptfield = (GtkEntry *) gtk_builder_get_object(builder, "comDesEntry");
    GtkEntry *pricefield = (GtkEntry *) gtk_builder_get_object(builder, "comPriceEntry");
    drugName = gtk_entry_get_text(namefield);
    id = gtk_entry_get_text(idfield);
    descript = gtk_entry_get_text(descriptfield);
    price = gtk_entry_get_text(pricefield);


    fromServer *fromServerObj = addNewMed(id, drugName, descript, price, userID);

    if(fromServerObj->medicine->isExist == TRUE) {

    }
    else {

    }
    char order[500] = "   ";
    strcat(order, drugName);
    strcat(order, "           ");
    strcat(order, id);
    strcat(order, "           ");
    strcat(order, descript);
    strcat(order, "           ");
    strcat(order, price);
    buffer3 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(inventlist));
    gtk_text_buffer_set_text(buffer3, order, -1);
    free(fromServerObj);
}

void comDelButClicked() {
    const char *comId;
    GtkTextView *inventlist = (GtkTextView *) gtk_builder_get_object(builder, "comInventList");
    GtkEntry *comidfield = (GtkEntry *) gtk_builder_get_object(builder, "comIDEntry");
    comId = gtk_entry_get_text(comidfield);

    char order[500] = "                                                        ";
    strcat(order, comId);

    buffer4 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(inventlist));
    gtk_text_buffer_set_text(buffer4, order, -1);
}

void comRefButClicked() {
    fromServer *viewOrderObj = viewOrder(userID);
    char tableChar[5000] = "";

    int i = 0;
    while (i < struct_length) {
        // Code

        char temp[1000] = "";
        strcat(temp, viewOrderObj->journal[i].trans_id);
        strcat(temp, "                          ");


        strcat(temp, viewOrderObj->journal[i].med_id);
        strcat(temp, "                                  ");


        strcat(temp, viewOrderObj->journal[i].store_id);
        strcat(temp, "                                      ");

        char quantity[8];
        sprintf(quantity, "%d", viewOrderObj->journal[i].quantity);
        strcat(temp, viewOrderObj->journal[i].store_id);
        strcat(temp, "                                      ");


        strcat(temp, viewOrderObj->journal[i].trans_date);
        strcat(temp, "                  ");

        strcat(temp, "\n");
        strcat(tableChar, temp);
        i++;

    }


    GtkTextView *ordersincomp = (GtkTextView *) gtk_builder_get_object(builder, "comReqList");
    buffer8 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(ordersincomp));
    gtk_text_buffer_set_text(buffer8, tableChar, -1);

}

void adDelBut1Clicked() {
    const char *pharmId;
    GtkTextView *pharmlist = (GtkTextView *) gtk_builder_get_object(builder, "adPharmList");
    GtkEntry *pharmidfield = (GtkEntry *) gtk_builder_get_object(builder, "adPharmIDEntry");
    pharmId = gtk_entry_get_text(pharmidfield);


}

void adDelBut2Clicked() {
    const char *comId2;
    GtkTextView *adcomlist = (GtkTextView *) gtk_builder_get_object(builder, "adComList");
    GtkEntry *adcomidfield = (GtkEntry *) gtk_builder_get_object(builder, "adComIDEntry");
    comId2 = gtk_entry_get_text(adcomidfield);

    char order[500] = "    ";
    strcat(order, comId2);

    buffer5 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(adcomlist));
    gtk_text_buffer_set_text(buffer5, order, -1);
}
void refresh_store_clicked(){

    fromServer *fromServerInventory = searchStoreInventory(userID);
    char inventory_table[5000]="";
    //Filling Inventory table in Drugstore
    int i=0;
    while(i<struct_length) {
        char temp[500]="";
        strcat(temp, fromServerInventory->search_inventory[i].med_id);
        strcat(temp, "                    ");
        strcat(temp, fromServerInventory->search_inventory[i].name);
        strcat(temp, "                          ");
        char quantity[8];
        sprintf(quantity, "%d", fromServerInventory->search_inventory[i].quantity);
        strcat(temp, quantity);
        strcat(temp, "\n");
        strcat(inventory_table, temp);
        i++;
    }

    GtkTextView *invent_tab = (GtkTextView*) gtk_builder_get_object(builder, "list_view");
    buffer7=gtk_text_view_get_buffer(GTK_TEXT_VIEW(invent_tab));
    gtk_text_buffer_set_text(buffer7, inventory_table, -1);

}
void company_refresh_inv(){
    fromServer *viewOrderObj = viewOrder(userID);
    char comp_inventory_table[5000]="";
    //Filling Inventory table in Drugstore
    int i=0;
    while(i<struct_length) {
        char temp[500]="";
        strcat(temp, viewOrderObj->journal[i].med_id);
        strcat(temp, "                    ");
        strcat(temp, viewOrderObj->journal[i].trans_id);
        strcat(temp, "                          ");
        char quantity[8];
        sprintf(quantity, "%d", viewOrderObj->journal[i].quantity);
        strcat(temp, quantity);
        strcat(temp, "\n");
        strcat(comp_inventory_table, temp);
        i++;
    }

    GtkTextView *com_invent_tab = (GtkTextView*) gtk_builder_get_object(builder, "comInventList");
    buffer9=gtk_text_view_get_buffer(GTK_TEXT_VIEW(com_invent_tab));
    gtk_text_buffer_set_text(buffer9, comp_inventory_table, -1);

}


