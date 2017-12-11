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

void test1();
void test2();

struct reg_back {
    int isExist;
    __uid_t user_type;
};

struct search_back {

};

struct registering {
    char login[MAX_SIZE];
    char password[MAX_SIZE];
};

struct searching {
    char * name;
};

struct purchasing {
    char name[MAX_SIZE];
    int quantity;
};

typedef struct {
    struct registering registration;
    struct searching search;
    struct purchasing purchase;
    __uid_t type;
} toServer;

toServer *client_message;

int main() {
    client_message = (toServer *)malloc(sizeof(toServer));
    strcpy(client_message->registration.login, "login");
    strcpy(client_message->registration.password, "password");
    client_message->type = (__uid_t) 0;
    test2();
    //test1();
    free(client_message);
    return 0;
}

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

void test2() {
    cJSON *root;
    char *out;
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", cJSON_CreateNumber(client_message->type));
    cJSON_AddItemToObject(root, "login", cJSON_CreateString(client_message->registration.login));
    cJSON_AddItemToObject(root, "password", cJSON_CreateString(client_message->registration.password));


    out = cJSON_Print(root);
    printf("%s\n", out);
}

