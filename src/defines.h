#ifndef DEFINES_H
#define DEFINES_H

#include "stdint.h"
/*
simplest possible use of offset calculation
it requires to define some instance of type
also it requires to performs subtraction*/
#define OFFSET(x, y) ((size_t) & (y) - (size_t) & (x))

/*
advanced version of offset
it casts NULL to checked type (datatype) and to calculate offset
it only needs to return address of member*/
#define OFFSET_NULL(type_struct, member)     (  (size_t)&(  ( (type_struct *)NULL )->member)  )

#define THIS_DOES_NOT_WORK  

#define MAX_LINE_SIZE   (1000U)


#define check_type(x) _Generic( (x), \
const int: "const int", \
char: "char",   \
char*: "char pointer *",    \
uint8_t: "uint8_t", \
int: "int",     \
default: "I am not sure")



enum TYPES_C {
    CHAR_TYPE,
    SHORT_TYPE,
    INT_TYPE,
};

#endif /* COMPONENT_H */

