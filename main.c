#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#define username "admin"
#define target "Trimol"

GtkBuilder *builder;
GtkWidget *window, *window1;
GtkTextBuffer *buffer1, *buffer2;
GtkTextIter start, end;
GtkTextIter *iter;


int main(int argc, char **argv)
{


   gtk_init(&argc, &argv);
   builder=gtk_builder_new();
   if(gtk_builder_add_from_file(builder, "login_frame.glade", NULL) == 0)
   {
      printf(".glade file is not exist");
      return (0);
   }




   window=GTK_WIDGET( gtk_builder_get_object(builder, "logwindow"));
   gtk_builder_connect_signals(builder, NULL);
   gtk_widget_show_all(window);
   gtk_main();


   return (0);
}
void on_enter_but_clicked(){
   const char* login;
   const char* password;

   GtkEntry* log = (GtkEntry*) gtk_builder_get_object(builder, "login_field");
   GtkEntry* pass=(GtkEntry*) gtk_builder_get_object(builder, "password_field");
   login=gtk_entry_get_text(log);
   password=gtk_entry_get_text(pass);

   if (strcmp(login, username)==0 && strcmp(password, username)==0){
       char *name="OxyMed";

      window1=GTK_WIDGET( gtk_builder_get_object(builder, "window1"));
       GtkLabel* storename=(GtkLabel*) gtk_builder_get_object(builder, "drugstore");
       gtk_label_set_text(GTK_LABEL(storename), name);




      gtk_widget_show_all(window1);
      gtk_widget_destroy(window);

   } else{
       GtkLabel* warn=(GtkLabel*) gtk_builder_get_object(builder, "warning");
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
            char data[800]="";
            char *space="         |        ";
            char *id = " 123";
            char *name=" Trimol ";
            char *price= " 3500 ";
            char *producer= " NikaPharm ";
            strcat(data, id);
            strcat(data, space);
            strcat(data, name);
            strcat(data, space);
            strcat(data, price);
            strcat(data, space);
            strcat(data, producer);

            GtkTextView *tab1 = (GtkTextView *) gtk_builder_get_object(builder, "display1");
            buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab1));
            gtk_text_buffer_set_text(buffer1, data, -1);
        }
    }
}

void add_but_clicked(){
    const char *amount, *date;
    GtkTextView *tab2 = (GtkTextView*) gtk_builder_get_object(builder, "display2");
    GtkEntry* amountfield = (GtkEntry*) gtk_builder_get_object(builder, "amount");
    GtkEntry* datefield = (GtkEntry*) gtk_builder_get_object(builder, "date");
    amount=gtk_entry_get_text(amountfield);
    date=gtk_entry_get_text(datefield);

    char order[500]="123         Trimol        ";
    strcat(order, amount);
    strcat(order, ",       ");
    strcat(order, date);
    buffer2=gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab2));
    gtk_text_buffer_set_text(buffer2, order, -1);



}

