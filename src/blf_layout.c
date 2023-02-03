#include "blf_handler.h"
#include <stdio.h>
#include <stdint.h>

byte_find_t byte_find_def_header = {
    HEADER_MARKER,
    strlen(HEADER_MARKER),
    blf_header_parsing,
    0};


void blf_header_parsing(fp_buffer_t * fp_buf) 
{
    uint8_t i = HEADER_BYTE_SIZE;
    fseek(fp_buf->file_pointer_to_read, 0 , SEEK_SET);
    char byte;
    do 
    {
        byte = getc(fp_buf->file_pointer_to_read);
        printf("%hhx%c ",byte, byte);
        

    }  while(i--);
    putchar('\n');
}