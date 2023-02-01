#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "console-colors.h"

#define HOW_MANY_TO_READ 90000 
#define BYTES_TO_STORE   5000

static uint32_t blf_bytes = HOW_MANY_TO_READ;

 char tab_to_find[] = {0x20, 0xfb, 0x47};

struct byte_find_tag {
    char * to_be_find;
    int length;
    int index_to_be_checked; /* which of bytes now I am checking*/

};

typedef struct byte_find_tag byte_find_t;

byte_find_t byte_find_def = {
    tab_to_find,
    3,
    0
};

 void blf_analyze_start(char *text)
 {
    int i = 0 ;
    int i_buffer = 0;
    FILE * blf_file = file_binary_open(text);

    char * tab = calloc(BYTES_TO_STORE, sizeof(char));
    
    while (( i < blf_bytes) && (tab != NULL))
    {
        tab[i_buffer] = getc(blf_file);
        // printf("%hhx ",tab[i]);
        printf("%c ",tab[i]);

        if  (tab[i_buffer] == byte_find_def.to_be_find[byte_find_def.index_to_be_checked])
        {
            byte_find_def.index_to_be_checked++;
            cc_fprintf(CC_FG_CYAN,stdout, "\nfound one %c \n", tab[i]);

            if (byte_find_def.index_to_be_checked == byte_find_def.length)
            {
                cc_fprintf(CC_FG_RED, stdout, "\n\n\nI have found at %d \n\n\n",i - byte_find_def.length);
                break;
            }
        }
        else
        {
            byte_find_def.index_to_be_checked = 0;
        }

        i++;
        i_buffer++;
        if (i_buffer == BYTES_TO_STORE)
        {
            i_buffer = 0;
        }
    }



    putchar('\n');
    free(tab);

    fclose(blf_file);

 }

 void blf_file_list(char *text)
 {
    FILE * blf_file = file_binary_open(text);

    file_length(blf_file);

    fclose(blf_file);

 }

 void blf_byte_number(char *text)
 {
     blf_bytes = atoi(text);

 }