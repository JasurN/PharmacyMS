#ifndef PHARMACYMS_DEFINE_H
#define PHARMACYMS_DEFINE_H

//Boolean operators
#include <my_global.h>

#define  FALSE 0
#define  TRUE 1

// Types of request
#define AUTHORIZATION 0
#define SEARCH 1
#define INVENTORY 2
#define PURCHASE 3
#define JOURNAL 4
#define MEDICINE 5
#define NEW_MEDICINE 6
#define USERS 7
#define ADD_USER 8
#define DELETE_USER 9

//User types
#define ADMIN 0
#define COMPANY 1
#define DRUGSTORE 2

#define  MAX_SIZE_BUF 2048
#endif //PHARMACYMS_DEFINE_H
