#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "blf_handler.h"
#include "console-colors.h"
#include <zlib.h>


static uint32_t blf_bytes = HOW_MANY_TO_READ;

 char tab_to_find[] = {0x20, 0xfb, 0x47};
 const char * find_OBJ = "OBJ";



byte_find_t byte_find_def = {
    tab_to_find,
    3,
    NULL,
    0,
};


static fp_buffer_t fp_buf_container = {
    {NULL, 0},
    NULL,
    0,
};

static void find_byte_sequence(byte_find_t * def, fp_buffer_t * fp_buf );




 void blf_analyze_start(char *text)
 {
    byte_find_t byte_find_def_OBJ = 
    {
        find_OBJ,
        (const int )strlen(find_OBJ),
        NULL,
        0
    };
    fp_buf_container.file_pointer_to_read = file_binary_open(text);

    char * tab = calloc(BYTES_TO_STORE, sizeof(char));
    

    fp_buf_container.buffer_container.buffer = tab;
    while (( fp_buf_container.file_index < blf_bytes) && (tab != NULL))
    {
        fp_buf_container.buffer_container.buffer[fp_buf_container.buffer_container.buffer_index] = getc(fp_buf_container.file_pointer_to_read);
        if (feof(fp_buf_container.file_pointer_to_read))
        {
            printf("end of file %s reached \n", text);
            break;
        }
        // printf("%hhx ",tab[i]);
        // printf("%c ",tab[i]);

        find_byte_sequence(&byte_find_def_OBJ, &fp_buf_container );

        find_byte_sequence(&byte_find_def_header,&fp_buf_container);

        /*increase file location*/
        fp_buf_container.file_index++;
        fp_buf_container.buffer_container.buffer_index++;
        if (fp_buf_container.buffer_container.buffer_index == BYTES_TO_STORE)
        {
            fp_buf_container.buffer_container.buffer_index = 0;
        }
    }
    putchar('\n');
    free(tab);

    printf("current file position %d i_buffer %d\n",ftell(fp_buf_container.file_pointer_to_read), fp_buf_container.buffer_container.buffer_index);

    fclose(fp_buf_container.file_pointer_to_read);

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

static void find_byte_sequence(byte_find_t * def, fp_buffer_t * fp_buf )
 {
     if (fp_buf->buffer_container.buffer[fp_buf->buffer_container.buffer_index] == def->to_be_find[def->index_to_be_checked])
     {
        def->index_to_be_checked++;
        // cc_fprintf(CC_FG_CYAN, stdout, "\nfound one %c \n", buffer[i_buffer]);

        if (def->index_to_be_checked == def->length)
        {
            cc_fprintf(CC_FG_RED, stdout, "\nI have found %s at %d \n", def->to_be_find, ftell(fp_buf->file_pointer_to_read) - def->length + 1);
            if (def->call_function != NULL)     def->call_function(fp_buf);
        }
     }
     else
     {
        def->index_to_be_checked = 0;
     }
 }


 void blf_header(void)
 {
    /* translate blf header*/
 }