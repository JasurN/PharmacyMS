#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "../parser/request_parser.h"
#include "../client/client.h"

#define username "admin"
#define target "Trimol"

GtkBuilder *builder;
GtkWidget *window, *window1;
GtkTextBuffer *buffer1, *buffer2;
GtkTextIter start, end;
GtkTextIter *iter;

void filltable1(char*, char*,char*,char*);
int main(int argc, char **argv)
{


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

    printf("name :%s\n", fromServerObj->authorization.name);
    if (fromServerObj->authorization.isExist == 1) {

        if (fromServerObj->authorization.user_type == DRUGSTORE) {


        window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
        GtkLabel *storename = (GtkLabel *) gtk_builder_get_object(builder, "drugstore");
        gtk_label_set_text(GTK_LABEL(storename), fromServerObj->authorization.name);



        gtk_widget_show_all(window1);
        gtk_widget_destroy(window);
            free(fromServerObj);

        }
    } else {
        GtkLabel *warn = (GtkLabel *) gtk_builder_get_object(builder, "warning");
        const gchar *text = "Login or Password wrong";
        gtk_label_set_text(GTK_LABEL(warn), text);
        g_print("Wrong");

    }
}

void search_but_clicked(){
    const char *searchedtext;
    GtkEntry* searchfield = (GtkEntry*) gtk_builder_get_object(builder, "search_entry");
    searchedtext = gtk_entry_get_text(searchfield);
    if(strcmp(searchedtext,"")!=0) {
        if (strcmp(searchedtext, target) == 0) {
            filltable1("123", "Trimol", "5000", "Headache, Painkiller");
        }
    }
}

char order[1000]="";
void add_but_clicked(){
    const char *amount, *date;
    GtkTextView *tab2 = (GtkTextView*) gtk_builder_get_object(builder, "display2");
    GtkEntry* amountfield = (GtkEntry*) gtk_builder_get_object(builder, "amount");
    GtkEntry* datefield = (GtkEntry*) gtk_builder_get_object(builder, "date");
    amount=gtk_entry_get_text(amountfield);
    date=gtk_entry_get_text(datefield);

    char temp[500]="";
    strcat(temp, "123,   ");
    strcat(temp, "       ");
    strcat(temp, "Trimol");
    strcat(temp, "       ");
    strcat(temp, amount);
    strcat(temp, "       ");
    strcat(temp, date);
    strcat(order, temp);
    strcat(order, "\n");
    buffer2=gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab2));
    gtk_text_buffer_set_text(buffer2, order, -1);



}

void filltable1(char *id, char *name, char *price, char *desc){
    char data[800]="";
    char temp[40]="";
    const char *space="          ";
    const char *nextspace="                         ";
    printf(id);
    strcat(data, id);
    strcat(data, space);
    strcat(data, name);
    strncpy(temp, nextspace,(strlen(nextspace) - strlen(name)));
    strcat(data, temp);
    strcat(data, price);
    memset(temp, 0, 40);
    strcat(data, space);
    strcat(data, desc);

    GtkTextView *tab1 = (GtkTextView *) gtk_builder_get_object(builder, "display1");
    buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab1));
    gtk_text_buffer_set_text(buffer1, data, -1);
}

