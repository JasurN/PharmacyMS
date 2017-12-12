#ifndef USER_H_
#define USER_H_H

struct Authorize
{
     char username[30];
     char password[30];
};

int authorize(struct Authorize authorize);
#endif