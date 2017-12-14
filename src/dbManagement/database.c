
#include </usr/include/mysql/mysql.h>
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#define int bool
#define TRUE 1
#define FALSE 0

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

bool authorization(char* login_id, char* login_password, MYSQL *con)
{
    char query[1024];
    sprintf(query, "SELECT * FROM authorization WHERE id = '%s' AND password = '%s'",login_id,login_password);
    if (mysql_query(con, query))
    {
      finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);
    int numrows= mysql_num_rows(result);

  if (numrows == 0)
  {
      return FALSE;
  }
  else
  {
      int num_fields = mysql_num_fields(result);
      MYSQL_ROW row;
      MYSQL_FIELD *field;
      while ((row = mysql_fetch_row(result)))
      {
          for(int i = 0; i < num_fields; i++)
          {
              printf("%s ", row[i] ? row[i] : "NULL");
          }
          printf("\n");
      }
   }
 return TRUE;
}


void addUser(char *user_id, char *user_name, char *user_adress, char * user_contact, int type, MYSQL *con)
{
  if (mysql_query(con, "INSERT INTO authorization VALUES(user_id,user_name, type)"))
  {
      finish_with_error(con);
  }
  if(type==1)
      if (mysql_query(con, "INSERT INTO company VALUES(user_id,user_name, user_adress, user_contact)")) {
          finish_with_error(con);
      }
  if(type==2)
      if (mysql_query(con, "INSERT INTO drugstore VALUES(user_id,user_name, user_adress, user_contact)")) {
          finish_with_error(con);
      }
}


int main(int argc, char **argv)
{      
  MYSQL *con = mysql_init(NULL);
  
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, "localhost", "root", "malika", 
          "pharmacy", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  char id[10], pass[20];
  scanf("%s",id);
  scanf("%s",pass);
  bool a =authorization(id, pass, con);
  if(a)
  printf("registered");
  else
  printf("not found");
  mysql_close(con);
  
  exit(0);
}
