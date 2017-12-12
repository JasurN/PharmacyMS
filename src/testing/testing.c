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

#include "stdio.h"
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
    __uid_t user_type;
};

struct search_back {
    char med_id[MAX_SIZE];
    char name[MAX_SIZE];
    char description[MAX_TEXT];
    float price;
    char comp_id[MAX_SIZE];
};

struct search_back_inventory {

};

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
    struct search_back_inventory search_inventory;
    struct purchase_back purchase;
    __uid_t type;
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
    __uid_t type;
} toServer;

toServer *client_message;

void test1();
void test2(toServer*);
void test3(toClient*);

int main() {
    /*client_message = (toServer *)malloc(sizeof(toServer));
    strcpy(client_message->authorization.login, "login");
    strcpy(client_message->authorization.password, "password");
    client_message->type = (__uid_t) 0;
    test2(client_message);
    //test1();
    free(client_message);*/

    /*server_message = (toClient *)malloc(sizeof(toClient));

     // Here should be some assigning values to the struct

    free(server_message);
    */
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
            "        \"frame rate\": 35\n"
            "    }\n"
            "}";
    cJSON * root = cJSON_Parse(my_json_string);
    cJSON *format = cJSON_GetObjectItemCaseSensitive(root, "format");
    cJSON *type_item = cJSON_GetObjectItemCaseSensitive(format, "type");
    cJSON *framerate_item = cJSON_GetObjectItemCaseSensitive(format, "frame rate");
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
void test2(toServer* client_message) {
    cJSON *root;
    char *out;
    root = cJSON_CreateObject();
    cJSON* authorization = cJSON_CreateObject();
    cJSON* searching = cJSON_CreateObject();
    cJSON* purchasing = cJSON_CreateObject();

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
            cJSON_AddItemToObject(root, "searching", searching);
            cJSON_AddItemToObject(searching, "name",
                                  cJSON_CreateString(client_message->search.name));
            break;

        case 2:
            cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(client_message->type));
            break;

        case 3:
            cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(client_message->type));
            cJSON_AddItemToObject(root, "purchasing", purchasing);
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
    cJSON_Delete(root);
}

void test3(toClient* server_message) {
    cJSON *root;
    char *out;
    root = cJSON_CreateObject();
    cJSON* authorization = cJSON_CreateObject();
    cJSON* searching = cJSON_CreateObject();
    cJSON* searching_inventory = cJSON_CreateObject();
    cJSON* purchasing = cJSON_CreateObject();

    switch (server_message->type) {
        case 0:
            if(server_message->authorization.isExist == TRUE) {
                cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(server_message->type));
                cJSON_AddItemToObject(root, "authorization", authorization);
                cJSON_AddItemToObject(authorization, "isExist",
                                      cJSON_CreateNumber(server_message->authorization.isExist));
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
            } else if(server_message->authorization.isExist == FALSE) {
                cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(server_message->type));
                cJSON_AddItemToObject(root, "authorization", authorization);
                cJSON_AddItemToObject(authorization, "isExist",
                                      cJSON_CreateNumber(server_message->authorization.isExist));
            }
            break;
        case 1:
            cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(server_message->type));
            cJSON_AddItemToObject(root, "search", searching);
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
            break;
        case 2:

            break;
        case 3:
            if(server_message->purchase.success == TRUE) {
                cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(server_message->type));
                cJSON_AddItemToObject(root, "purchase", purchasing);
                cJSON_AddItemToObject(searching, "success",
                                      cJSON_CreateNumber(server_message->purchase.success));
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
            } else if (server_message->purchase.success == FALSE) {
                cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(server_message->type));
                cJSON_AddItemToObject(root, "purchase", purchasing);
                cJSON_AddItemToObject(searching, "success",
                                      cJSON_CreateNumber(server_message->purchase.success));
            }
            break;
        default:
            perror("Please enter proper type!");
            break;
    }
    out = cJSON_Print(root);
    printf("%s\n", out);
    cJSON_Delete(root);
}
