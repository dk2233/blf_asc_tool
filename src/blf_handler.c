#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "console-colors.h"

#define HOW_MANY_TO_READ 90000 
#define BYTES_TO_STORE   5000

static uint32_t blf_bytes = HOW_MANY_TO_READ;

 char tab_to_find[] = {0x20, 0xfb, 0x47};
 char * find_LOGG = "LOGG";
 char * find_OBJ = "OBJ";

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


static void find_byte_sequence(byte_find_t * def, char * buffer,int i_buffer, int i );




 void blf_analyze_start(char *text)
 {
    int i = 0 ;
    int i_buffer = 0;
    byte_find_t byte_find_def_logg = {
        find_LOGG,
        strlen(find_LOGG),
        0};

    byte_find_t byte_find_def_OBJ = {
        find_OBJ,
        strlen(find_OBJ),
        0};
    FILE * blf_file = file_binary_open(text);

    char * tab = calloc(BYTES_TO_STORE, sizeof(char));
    
    while (( i < blf_bytes) && (tab != NULL))
    {
        tab[i_buffer] = getc(blf_file);
        if (feof(blf_file))
        {
            printf("end of file reached \n");
            break;
        }
        // printf("%hhx ",tab[i]);
        // printf("%c ",tab[i]);

        find_byte_sequence(&byte_find_def_OBJ, tab,i_buffer, i);

        find_byte_sequence(&byte_find_def_logg, tab, i_buffer, i);

        i++;
        i_buffer++;
        if (i_buffer == BYTES_TO_STORE)
        {
            i_buffer = 0;
        }
    }
    putchar('\n');
    free(tab);

    printf("current file position %d i_buffer %d\n",ftell(blf_file), i_buffer);

    fclose(blf_file);

 }


void asc_analyze_start(char * text)
{

}

 void blf_file_list(char *text)
 {
    FILE * blf_file = file_binary_open(text);

    file_length(blf_file);

    fclose(blf_file);

 }

 void asc_file_list(char *text)
 {
    FILE * asc_file;
    func_open_file(text, "r", &asc_file);

    file_length(asc_file);

    fclose(asc_file);

 }

 void blf_byte_number(char *text)
 {
     blf_bytes = atoi(text);

 }

static void find_byte_sequence(byte_find_t * def, char * buffer,int i_buffer, int i )
 {
     if (buffer[i_buffer] == def->to_be_find[def->index_to_be_checked])
     {
        def->index_to_be_checked++;
        // cc_fprintf(CC_FG_CYAN, stdout, "\nfound one %c \n", buffer[i_buffer]);

        if (def->index_to_be_checked == def->length)
        {
            cc_fprintf(CC_FG_RED, stdout, "\nI have found %s at %d \n", def->to_be_find, i - def->length + 1);
        }
     }
     else
     {
        def->index_to_be_checked = 0;
     }
 }