#ifndef FILES_H
#define FILES_H

#include <stdio.h>

extern void files_playground(void);

extern long int file_length(FILE *file_hd);

void func_open_file(char * name, char * mode, FILE ** file_hd);

extern void func_open_file_FILE(void * name, void ** file_handler);

extern int whole_file_to_one_str( FILE *file_handler, char *table );

extern FILE * file_binary_open(char* file_name);

#endif