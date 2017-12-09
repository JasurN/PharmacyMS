#include "MySqlManager.h"

void mysqlVersion() {
    printf("MySQL client version: %s\n", mysql_get_client_info());
}

void mysqlConnect(const char * server, const char * user,
                  const char * password, const char * database,
                  const char * query) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server,
                            user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    /* send SQL query */
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    /* output table name */
    printf("MySQL Tables in mysql database:\n");
    while ((row = mysql_fetch_row(res)) != NULL)
        printf("%s \n", row[0]);

    /* close connection */
    mysql_free_result(res);
    mysql_close(conn);
}
