#ifndef BLF_CONFIG_H
#define BLF_CONFIG_H
#include "arg_parse.h"

extern void blf_analyze_start(char *text);
extern void asc_analyze_start(char *text);

extern void blf_file_list(char *text);
extern void asc_file_list(char *text);

extern void blf_byte_number(char *text);

#endif