#include "server.h"
#include "../parser/object.h"
#include "../dbManagement/dbManagement.h"

int main() {
   struct authorizing *user = searchUser("hi123", "heyhey");
   printf("%s\n", user->login);
   printf("%s\n", user->password);
   printf("%d \n", user->type);

     // startServer();
}