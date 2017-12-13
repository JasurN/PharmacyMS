/*
 *  This is the function which is dealt with
 *  clients query to the Server,
 *  so this is the functions that is intermediate
 *  between GUI and Client's Socket.
 *  Also the structure is like:
 *  GUI ---> This function ---> Socket
 *  and GUI controls this function whereas
 *  this function controls Client's Socket
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../parser/cJSON.h"
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 30
#define MAX_TEXT 50

/* These structs are used by client (Company) */
struct auth_back {
    int isExist;
    char id[MAX_SIZE];
    char name[MAX_TEXT];
    char address[MAX_TEXT];
    char contact[MAX_TEXT];
    uid_t user_type;
};

struct search_back {
    int isExist;
    char med_id[MAX_SIZE];
    char name[MAX_SIZE];
    char description[MAX_TEXT];
    float price;
    char comp_id[MAX_SIZE];
};

struct search_back_inventory{
    char store_id[MAX_SIZE];
    char med_id[MAX_SIZE];
    char name[MAX_SIZE];
    int quantity;
} ;

struct purchase_back {
    int success;
    char trans_id[MAX_SIZE];
    char trans_date[MAX_SIZE];
    char comp_id[MAX_SIZE];
    char store_id[MAX_SIZE];
    char med_id[MAX_SIZE];
    int quantity;
};

typedef struct {
    struct auth_back authorization;
    struct search_back search;
    struct search_back_inventory* search_inventory;
    struct purchase_back purchase;
    uid_t type;
} toClient;

toClient *server_message;

/* These structs are used by client (Drugstore) */
struct authorizing {
    char login[MAX_SIZE];
    char password[MAX_SIZE];
};

struct searching {
    char name[MAX_SIZE];
};

struct purchasing {
    char name[MAX_SIZE];
    int quantity;
};

typedef struct {
    struct authorizing authorization;
    struct searching search;
    struct purchasing purchase;
    uid_t type;
} toServer;

toServer *client_message;

/* This struct is used when got answer from server by client (Drugstore) */
typedef struct {
    struct auth_back authorization;
    struct search_back search;
    struct search_back_inventory* search_inventory;
    struct purchase_back purchase;
    uid_t type;
} fromServer;

fromServer *server_answer;

/* This struct is used when got query from client (Company) */
typedef struct {
    struct authorizing authorization;
    struct searching search;
    struct purchasing purchase;
    uid_t type;
} fromClient;

fromClient *client_query;

void test1();
char* serialization1(const toServer*);
char* serialization2(const toClient*);
fromServer* deserialization1(const char*, fromServer*);
fromClient* deserialization2(const char*, fromClient*);

int main() {
    /*client_message = (toServer *)malloc(sizeof(toServer));
    strcpy(client_message->authorization.login, "login");
    strcpy(client_message->authorization.password, "password");
    client_message->type = (uid_t) 0;
    serialization1(client_message);
    //test1();
    //free(client_message);

    /*server_message = (toClient *)malloc(sizeof(toClient));

     // Here should be some assigning values to the struct

    free(server_message);


    //server_answer = (fromServer *)malloc(sizeof(fromServer));
    client_query = (fromClient *)malloc(sizeof(fromClient));
    client_query = deserialization2(serialization1(client_message), client_query);


    free(client_message);*/
    test1();
    return 0;
}
/*
 *  Just testing function
 *
 * */
void test1() {
    const char* my_json_string = "{\n"
            "    \"name\": \"Jack (\\\"Bee\\\") Nimble\",\n"
            "    \"format\": {\n"
            "        \"type\":       \"rect\",\n"
            "        \"width\":      1920,\n"
            "        \"height\":     1080,\n"
            "        \"interlace\":  false,\n"
            "        \"frame_rate\": 35\n"
            "    }\n"
            "}";
    cJSON * root = cJSON_Parse(my_json_string);
    cJSON *format = cJSON_GetObjectItemCaseSensitive(root, "format");
    cJSON *type_item = cJSON_GetObjectItemCaseSensitive(format, "type");
    cJSON *framerate_item = cJSON_GetObjectItemCaseSensitive(format, "frame_rate");
    char type[MAX_SIZE];
    int framerate = 0;
    //cJSON_SetNumberValue(framerate_item, 140);
    if (cJSON_IsString(type_item)) {
        strcpy(type, type_item->valuestring);
    }
    if (cJSON_IsNumber(framerate_item)) {
        framerate = framerate_item->valueint;
    }
    printf("value of framerate; %d\n", framerate);
    printf("value of type; %s", type);

    cJSON_Delete(root);
}
/*
 *  This function converts queries to be
 *  sent to the server from client (Drug Stores)
 *
 * */
char* serialization1(const toServer* client_message) {
    cJSON *root = cJSON_CreateObject();
    cJSON *authorization = cJSON_CreateObject();
    cJSON *searching = cJSON_CreateObject();
    cJSON *purchasing = cJSON_CreateObject();
    char *out;

    switch (client_message->type) {
        case 0:
            cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(client_message->type));
            cJSON_AddItemToObject(root, "authorization", authorization);
            cJSON_AddItemToObject(authorization, "login",
                                  cJSON_CreateString(client_message->authorization.login));
            cJSON_AddItemToObject(authorization, "password",
                                  cJSON_CreateString(client_message->authorization.password));
            break;
        case 1:
            cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(client_message->type));
            cJSON_AddItemToObject(root, "search", searching);
            cJSON_AddItemToObject(searching, "name",
                                  cJSON_CreateString(client_message->search.name));
            break;

        case 2:
            cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(client_message->type));
            break;

        case 3:
            cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(client_message->type));
            cJSON_AddItemToObject(root, "purchase", purchasing);
            cJSON_AddItemToObject(purchasing, "name",
                                  cJSON_CreateString(client_message->purchase.name));
            cJSON_AddItemToObject(purchasing, "quantity",
                                  cJSON_CreateNumber(client_message->purchase.quantity));
            break;

        default:
            perror("Please enter proper type!");
            break;
    }
    out = cJSON_Print(root);
    printf("%s\n", out);
    cJSON_Delete(authorization);
    cJSON_Delete(searching);
    cJSON_Delete(purchasing);
    cJSON_Delete(root);
    return out;
}

char* serialization2(const toClient* server_message) {
    cJSON *root = cJSON_CreateObject();
    cJSON *authorization = cJSON_CreateObject();
    cJSON *searching = cJSON_CreateObject();
    cJSON *searching_inventory = cJSON_CreateArray();
    cJSON *medical = cJSON_CreateObject();
    cJSON *purchasing = cJSON_CreateObject();
    char *out;

    cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(server_message->type));
    switch (server_message->type) {
        case 0:
            cJSON_AddItemToObject(root, "authorization", authorization);
            cJSON_AddItemToObject(authorization, "isExist",
                                  cJSON_CreateNumber(server_message->authorization.isExist));
            if(server_message->authorization.isExist == TRUE) {
                cJSON_AddItemToObject(authorization, "id",
                                      cJSON_CreateString(server_message->authorization.id));
                cJSON_AddItemToObject(authorization, "name",
                                      cJSON_CreateString(server_message->authorization.name));
                cJSON_AddItemToObject(authorization, "address",
                                      cJSON_CreateString(server_message->authorization.address));
                cJSON_AddItemToObject(authorization, "contact",
                                      cJSON_CreateString(server_message->authorization.contact));
                cJSON_AddItemToObject(authorization, "user_type",
                                      cJSON_CreateNumber(server_message->authorization.user_type));
            }
            break;
        case 1:
            cJSON_AddItemToObject(root, "search", searching);
            cJSON_AddItemToObject(searching, "isExist",
                                  cJSON_CreateNumber(server_message->search.isExist));
            if(server_message->search.isExist == TRUE) {
                cJSON_AddItemToObject(searching, "med_id",
                                      cJSON_CreateString(server_message->search.med_id));
                cJSON_AddItemToObject(searching, "name",
                                      cJSON_CreateString(server_message->search.name));
                cJSON_AddItemToObject(searching, "description",
                                      cJSON_CreateString(server_message->search.description));
                cJSON_AddItemToObject(searching, "price",
                                      cJSON_CreateNumber(server_message->search.price));
                cJSON_AddItemToObject(searching, "comp_id",
                                      cJSON_CreateString(server_message->search.comp_id));
            }
            break;
        case 2:
            cJSON_AddItemToObject(root, "inventory", searching_inventory);
            for (int i = 0; server_message->search_inventory; ++i) {
                cJSON_AddItemToArray(searching_inventory, medical = cJSON_CreateObject());
                cJSON_AddItemToObject(medical, "store_id",
                                      cJSON_CreateString(server_message->search_inventory[i].store_id));
                cJSON_AddItemToObject(medical, "med_id",
                                      cJSON_CreateString(server_message->search_inventory[i].med_id));
                cJSON_AddItemToObject(medical, "name",
                                      cJSON_CreateString(server_message->search_inventory[i].name));
                cJSON_AddItemToObject(medical, "quantity",
                                      cJSON_CreateNumber(server_message->search_inventory[i].quantity));
            }
            
            break;
        case 3:
            cJSON_AddItemToObject(root, "purchase", purchasing);
            cJSON_AddItemToObject(searching, "success",
                                  cJSON_CreateNumber(server_message->purchase.success));
            if(server_message->purchase.success == TRUE) {
                cJSON_AddItemToObject(searching, "trans_id",
                                      cJSON_CreateString(server_message->purchase.trans_id));
                cJSON_AddItemToObject(searching, "trans_date",
                                      cJSON_CreateString(server_message->purchase.trans_date));
                cJSON_AddItemToObject(searching, "comp_id",
                                      cJSON_CreateString(server_message->purchase.comp_id));
                cJSON_AddItemToObject(searching, "store_id",
                                      cJSON_CreateString(server_message->purchase.store_id));
                cJSON_AddItemToObject(searching, "med_id",
                                      cJSON_CreateString(server_message->purchase.med_id));
                cJSON_AddItemToObject(searching, "quantity",
                                      cJSON_CreateNumber(server_message->purchase.quantity));
            }
            break;
        default:
            perror("Please enter proper type!");
            break;
    }
    out = cJSON_Print(root);
    printf("%s\n", out);
    cJSON_Delete(authorization);
    cJSON_Delete(searching);
    cJSON_Delete(medical);
    cJSON_Delete(searching_inventory);
    cJSON_Delete(purchasing);
    cJSON_Delete(root);
    return out;
}

fromServer* deserialization1(const char* message, fromServer* server_answer) {
    cJSON *root = cJSON_Parse(message);
    cJSON *type_item = cJSON_GetObjectItemCaseSensitive(root, "type");
    if (type_item->valueint == 0) {
        cJSON *authorization_item = cJSON_GetObjectItemCaseSensitive(root, "authorization");
        cJSON *isExist_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "isExist");
        if (isExist_item->valueint == TRUE) {
            cJSON *id_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "id");
            cJSON *name_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "name");
            cJSON *address_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "address");
            cJSON *contact_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "contact");
            cJSON *user_type_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "user_type");
            strcpy(server_answer->authorization.id, id_item->valuestring);
            strcpy(server_answer->authorization.name, name_item->valuestring);
            strcpy(server_answer->authorization.address, address_item->valuestring);
            strcpy(server_answer->authorization.contact, contact_item->valuestring);
            server_answer->authorization.user_type = (uid_t) user_type_item->valueint;
            cJSON_Delete(id_item);
            cJSON_Delete(name_item);
            cJSON_Delete(address_item);
            cJSON_Delete(contact_item);
            cJSON_Delete(user_type_item);
        }
        server_answer->authorization.isExist = (uid_t) isExist_item->valueint;
        cJSON_Delete(isExist_item);
        cJSON_Delete(authorization_item);
    } else if (type_item->valueint == 1) {
        cJSON *search_item = cJSON_GetObjectItemCaseSensitive(root, "search");
        cJSON *isExist_item = cJSON_GetObjectItemCaseSensitive(search_item, "isExist");
        if (isExist_item->valueint == TRUE) {
            cJSON *med_id_item = cJSON_GetObjectItemCaseSensitive(search_item, "med_id");
            cJSON *name_item = cJSON_GetObjectItemCaseSensitive(search_item, "name");
            cJSON *description_item = cJSON_GetObjectItemCaseSensitive(search_item, "description");
            cJSON *price_item = cJSON_GetObjectItemCaseSensitive(search_item, "price");
            cJSON *comp_id_item = cJSON_GetObjectItemCaseSensitive(search_item, "comp_id");
            strcpy(server_answer->search.med_id, med_id_item->valuestring);
            strcpy(server_answer->search.name, name_item->valuestring);
            strcpy(server_answer->search.description, description_item->valuestring);
            server_answer->search.price = price_item->valueint;
            strcpy(server_answer->search.comp_id, comp_id_item->valuestring);
            cJSON_Delete(med_id_item);
            cJSON_Delete(name_item);
            cJSON_Delete(description_item);
            cJSON_Delete(price_item);
            cJSON_Delete(comp_id_item);
        }
        server_answer->search.isExist = (uid_t) isExist_item->valueint;
        cJSON_Delete(isExist_item);
        cJSON_Delete(search_item);
    } else if (type_item->valueint == 2) {
        cJSON *inventory_item = cJSON_GetObjectItemCaseSensitive(root, "inventory");
        cJSON *medical;
        cJSON *store_id_item;
        cJSON *med_id_item;
        cJSON *name_item;
        cJSON *quantity_item;
        for (int i = 0; i < cJSON_GetArraySize(inventory_item); ++i) {
            medical = cJSON_GetArrayItem(inventory_item, i);
            store_id_item = cJSON_GetObjectItemCaseSensitive(inventory_item, "store_id");
            med_id_item = cJSON_GetObjectItemCaseSensitive(inventory_item, "med_id");
            name_item = cJSON_GetObjectItemCaseSensitive(inventory_item, "name");
            quantity_item = cJSON_GetObjectItemCaseSensitive(inventory_item, "quantity");
            strcpy(server_answer->search_inventory[i].store_id, store_id_item->valuestring);
            strcpy(server_answer->search_inventory[i].med_id, med_id_item->valuestring);
            strcpy(server_answer->search_inventory[i].name, name_item->valuestring);
            server_answer->search_inventory[i].quantity = quantity_item->valueint;
        }
        cJSON_Delete(store_id_item);
        cJSON_Delete(med_id_item);
        cJSON_Delete(name_item);
        cJSON_Delete(quantity_item);
        cJSON_Delete(inventory_item);
        cJSON_Delete(medical);
    } else if (type_item->valueint == 3) {
        cJSON *purchase_item = cJSON_GetObjectItemCaseSensitive(root, "purchase");
        cJSON *success_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "success");
        if (success_item->valueint == TRUE) {
            cJSON *trans_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "trans_id");
            cJSON *trans_date_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "trans_date");
            cJSON *comp_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "comp_id");
            cJSON *store_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "store_id");
            cJSON *med_id_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "med_id");
            cJSON *quantity_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "quantity");
            strcpy(server_answer->purchase.trans_id, trans_id_item->valuestring);
            strcpy(server_answer->purchase.trans_date, trans_date_item->valuestring);
            strcpy(server_answer->purchase.comp_id, comp_id_item->valuestring);
            strcpy(server_answer->purchase.store_id, store_id_item->valuestring);
            strcpy(server_answer->purchase.med_id, med_id_item->valuestring);
            server_answer->purchase.quantity = quantity_item->valueint;
            cJSON_Delete(trans_id_item);
            cJSON_Delete(trans_date_item);
            cJSON_Delete(comp_id_item);
            cJSON_Delete(store_id_item);
            cJSON_Delete(med_id_item);
            cJSON_Delete(quantity_item);
        }
        server_answer->purchase.success = success_item->valueint;
        cJSON_Delete(success_item);
        cJSON_Delete(purchase_item);
    }

    server_answer->type = (uid_t) type_item->valueint;
    cJSON_Delete(type_item);
    cJSON_Delete(root);
    return server_answer;
}

fromClient* deserialization2(const char* message, fromClient* client_query) {
    cJSON *root = cJSON_Parse(message);
    cJSON *type_item = cJSON_GetObjectItemCaseSensitive(root, "type");

    if(type_item->valueint == 0) {
        cJSON *authorization_item = cJSON_GetObjectItemCaseSensitive(root, "authorization");
        cJSON *login_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "login");
        cJSON *password_item = cJSON_GetObjectItemCaseSensitive(authorization_item, "password");
        strcpy(client_query->authorization.login, login_item->valuestring);
        strcpy(client_query->authorization.password, password_item->valuestring);
        cJSON_Delete(login_item);
        cJSON_Delete(password_item);
        cJSON_Delete(authorization_item);
    } else if (type_item->valueint == 1) {
        cJSON *search_item = cJSON_GetObjectItemCaseSensitive(root, "search");
        cJSON *name_item = cJSON_GetObjectItemCaseSensitive(search_item, "name");
        strcpy(client_query->search.name, name_item->valuestring);
        cJSON_Delete(name_item);
        cJSON_Delete(search_item);
    } else if (type_item->valueint == 2) {
        /*  In this condition do nothing as there is no
         *  additional information but type
         * */

    } else if (type_item->valueint == 3) {
        cJSON *purchase_item = cJSON_GetObjectItemCaseSensitive(root, "purchase");
        cJSON *name_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "name");
        cJSON *quantity_item = cJSON_GetObjectItemCaseSensitive(purchase_item, "quantity");
        strcpy(client_query->purchase.name, name_item->valuestring);
        client_query->purchase.quantity = quantity_item->valueint;
        cJSON_Delete(name_item);
        cJSON_Delete(quantity_item);
        cJSON_Delete(purchase_item);
    }

    server_answer->type = (uid_t) type_item->valueint;
    cJSON_Delete(type_item);
    cJSON_Delete(root);

    return client_query;
}
