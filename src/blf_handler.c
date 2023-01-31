#include "files.h"
#include <stdio.h>
#define HOW_MANY_TO_READ 100 

 void blf_analyze_start(char *text)
 {
    int i;
    FILE * blf_file = file_binary_open(text);

    while ( i < HOW_MANY_TO_READ)
    {
        printf("%x ",getc(blf_file));
    }

    fclose(blf_file);

 }

 void blf_file_list(char *text)
 {
    FILE * blf_file = file_binary_open(text);

    file_length(blf_file);

    fclose(blf_file);

 }