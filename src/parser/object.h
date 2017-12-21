//
// Created by malika on 12/18/17.
//

#ifndef PHARMACYMS_OBJECT_H
#define PHARMACYMS_OBJECT_H
#include "../dbManagement/dbManagement.h"
#include <string.h>
#include "../parser/request_parser.h"
#include "../define/define.h"

void *object_parser(char *tablename, MYSQL_RES *result);
void *medicine_parser(MYSQL_RES *result);
void *inventory_parser(MYSQL_RES *result);
void *drugstore_parser(MYSQL_RES *result);
void *journal_parser(MYSQL_RES *result);
void *user_parser(MYSQL_RES *result);
void *company_parser(MYSQL_RES *result);


#endif //PHARMACYMS_OBJECT_H
