#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "../parser/request_parser.h"
#include "../client/client.h"


#define type2 "2"
#define target "Trimol"

GtkBuilder *builder;
GtkWidget *window, *window1, *window2, *window3;
GtkLabel *warnlabel;
GtkTextBuffer *buffer1, *buffer2, *buffer3, *buffer4, *buffer5, *buffer6, *buffer7;
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

        if (fromServerObj->authorization.user_type == ADMIN) {
            char *name = "OxyMed";

            window1 = GTK_WIDGET(gtk_builder_get_object(builder, "adminWindow"));
            GtkLabel *storename = (GtkLabel *) gtk_builder_get_object(builder, "drugstore");
            gtk_label_set_text(GTK_LABEL(storename), name);


            gtk_widget_show_all(window1);
            gtk_widget_destroy(window);

        }

        else if (fromServerObj->authorization.user_type == DRUGSTORE) {
            char *name = "OxyMed";

            window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
            GtkLabel *storename = (GtkLabel *) gtk_builder_get_object(builder, "drugstore");
            gtk_label_set_text(GTK_LABEL(storename), name);


            gtk_widget_show_all(window2);
            gtk_widget_destroy(window);

        }
        else if(fromServerObj->authorization.user_type == COMPANY) {
            char *name = "OxyMed";

            window3 = GTK_WIDGET(gtk_builder_get_object(builder, "companyWindow"));
            GtkLabel *storename = (GtkLabel *) gtk_builder_get_object(builder, "drugstore");
            gtk_label_set_text(GTK_LABEL(storename), name);


            gtk_widget_show_all(window3);
            gtk_widget_destroy(window);
        }
    } else {
        GtkLabel *warn = (GtkLabel *) gtk_builder_get_object(builder, "warning");
        const gchar *text = "Login or Password wrong";
        gtk_label_set_text(GTK_LABEL(warn), text);
        g_print("Wrong");

    }
}


void search_but_clicked() {//todo: make double price. Important
    printf("it is here");
    const char *searchedtext;
    GtkEntry *searchfield = (GtkEntry *) gtk_builder_get_object(builder, "search_entry");
    searchedtext = gtk_entry_get_text(searchfield);
    if (strcmp(searchedtext, "") != 0) {
        fromServer* fromServerObj = searchCompanyInventory(searchedtext);
        if(fromServerObj->search.isExist == TRUE ){
         char price[30];
            sprintf(price, "%lf", fromServerObj->search.price);
            filltable1(fromServerObj->search.med_id, fromServerObj->search.name,
                       price, fromServerObj->search.description);
        }
        free(fromServerObj);
    }
}

char order[1000] = "";

void add_but_clicked() {
    const char *amount, *date;
    GtkTextView *tab2 = (GtkTextView *) gtk_builder_get_object(builder, "display2");
    GtkEntry *amountfield = (GtkEntry *) gtk_builder_get_object(builder, "amount");
    GtkEntry *datefield = (GtkEntry *) gtk_builder_get_object(builder, "date");
    amount = gtk_entry_get_text(amountfield);
    date = gtk_entry_get_text(datefield);

    char temp[500] = "";
    strcat(temp, "123,   ");
    strcat(temp, "       ");
    strcat(temp, "Trimol");
    strcat(temp, "       ");
    strcat(temp, amount);
    strcat(temp, "       ");
    strcat(temp, date);
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


void regButClicked() {
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


/*    char order[500] = "   ";
    strcat(order, ID);
    strcat(order, "           ");
    strcat(order, password);
    strcat(order, "           ");
    strcat(order, name);
    strcat(order, "           ");
    strcat(order, contact);
    strcat(order, "           ");
    strcat(order, address);
    buffer7 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pharmlist));
    buffer6 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(comlist));
    if (strcmp(type, type1) == 0) {
        gtk_text_buffer_set_text(buffer7, order, -1);

    } else if (strcmp(type, type2) == 0) {
        gtk_text_buffer_set_text(buffer6, order, -1);
    } else {

    }*/
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

    produceMedicineByCompany(drugName, id, descript, price);

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
}

void adDelBut1Clicked() {
    const char *pharmId;
    GtkTextView *pharmlist = (GtkTextView *) gtk_builder_get_object(builder, "adPharmList");
    GtkEntry *pharmidfield = (GtkEntry *) gtk_builder_get_object(builder, "adPharmIDEntry");
    pharmId = gtk_entry_get_text(pharmidfield);

    char order[500] = "    ";
    strcat(order, pharmId);

    buffer4 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pharmlist));
    gtk_text_buffer_set_text(buffer4, order, -1);
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