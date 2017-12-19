#ifndef PHARMACYMS_REQUEST_PARSER_H
#define PHARMACYMS_REQUEST_PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "../define/define.h"

#define MAX_SIZE 30
#define MAX_TEXT 50

/* These structs are used by clientOn (Company) */
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
    char *med_id;
    char *name;
    char *description;
    double price;
    char *comp_id;
};

struct search_back_inventory{
    char *store_id;
    char *med_id;
    char *name;
    int quantity;
} ;

struct purchase_back {
    int success;
    char *trans_id;
    char *trans_date;
    char *comp_id;
    char *store_id;
    char *med_id;
    int quantity;
    int status;
};

/* These structs are used by clientOn (Drugstore) */
struct authorizing {
    char login[MAX_SIZE];
    char password[MAX_SIZE];
    uid_t type;
};

struct searching {
    char name[MAX_SIZE];
};

struct purchasing {
    char name[MAX_SIZE];
    int quantity;
};

typedef struct {
    struct auth_back authorization;
    struct search_back search;
    struct search_back_inventory* search_inventory;
    struct purchase_back purchase;
    uid_t type;
} toClient;

typedef struct {
    struct authorizing authorization;
    struct searching search;
    struct purchasing purchase;
    uid_t type;
} toServer;

/* This struct is used when got answer from server by clientOn (Drugstore) */
typedef struct {
    struct auth_back authorization;
    struct search_back search;
    struct search_back_inventory* search_inventory;
    struct purchase_back purchase;
    uid_t type;
} fromServer;

/* This struct is used when got query from clientOn (Company) */
typedef struct {
    struct authorizing authorization;
    struct searching search;
    struct purchasing purchase;
    uid_t type;
} fromClient;

void test1();
char* clientStructToStr(const toServer *);
char* serverStructToStr(const toClient*);
void serverStrToStruct(const char *, fromServer *);
void clientStrToStruct(const char *, fromClient *);
#endif //PHARMACYMS_REQUEST_PARSER_H
