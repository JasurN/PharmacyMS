#ifndef PHARMACYMS_MYSQLTEST_H
#define PHARMACYMS_MYSQLTEST_H

#include "mysql/mysql.h"
#include "mysql/my_global.h"

void mysqlVersion(void);
void mysqlConnect(const char * server, const char * user,
                  const char * password, const char * database,
                  const char * query);
#endif //PHARMACYMS_MYSQLTEST_H
