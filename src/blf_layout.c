#include "blf_handler.h"
#include <stdio.h>
#include <stdint.h>

byte_find_t byte_find_def_header = {
    HEADER_MARKER,
    strlen(HEADER_MARKER),
    blf_header_parsing,
    0};

byte_find_t byte_find_def_OBJ =
    {
        CONTAINER_MARKER,
        (const int)strlen(CONTAINER_MARKER),
        blf_object_parsing,
        0,
    };

void blf_header_parsing(fp_buffer_t * fp_buf) 
{
    uint8_t i = HEADER_BYTE_SIZE - strlen(byte_find_def_header.to_be_find);
    uint32_t start_header_index = 0;

    // fseek(fp_buf->file_pointer_to_read, 0 , SEEK_SET);
    char byte;
    do 
    {
        /* thanks to such condition incrementation after leaving this callout
        will work fine*/
        fp_buf->file_index++;

        byte = getc(fp_buf->file_pointer_to_read);
        printf("%hhx%c ",byte, byte);
        fp_buf->buffer_container.buffer[ ++(fp_buf->buffer_container.buffer_index) ] = byte;


    /* --i condition will make next byte after header to be also stored into buffer*/
    }  while(--i);
    putchar('\n');
    /*cast buffer to struct header_t*/

    header_t * blf_header = (header_t *) &fp_buf->buffer_container.buffer[start_header_index];

    printf("header file size has %ld \nblf file size %lld \nbytes unpacked file size %lld\n",blf_header->header_size, blf_header->blf_file_size, blf_header->blf_unpacked_file_size);
    printf("press key\n");
    (void)getc(stdin);

    /* after leaving this function we incresed also indexes - */
    fp_buf->file_index--;
    fp_buf->buffer_container.buffer_index--;
}


void blf_object_parsing(fp_buffer_t *fp_buf)
{
    uint8_t i = sizeof(hdr_base_t) - strlen(byte_find_def_header.to_be_find);
    uint32_t start_header_index = fp_buf->buffer_container.buffer_index +1 - strlen(byte_find_def_header.to_be_find);

    // fseek(fp_buf->file_pointer_to_read, 0 , SEEK_SET);
    char byte;
    do 
    {
        /* thanks to such condition incrementation after leaving this callout
        will work fine*/
        fp_buf->file_index++;

        byte = getc(fp_buf->file_pointer_to_read);
        printf("%hhx%c ",byte, byte);
        fp_buf->buffer_container.buffer[ ++(fp_buf->buffer_container.buffer_index) ] = byte;


    /* --i condition will make next byte after header to be also stored into buffer*/
    }  while(--i);
    putchar('\n');
    /*cast buffer to struct header_t*/

    hdr_base_t * blf_obj_hdr_b = (hdr_base_t *) &fp_buf->buffer_container.buffer[start_header_index];

    printf("object version is %d object size has %d \nblf object size %ld \n object type %ld\n",blf_obj_hdr_b->object_header_version, blf_obj_hdr_b->object_header_size, blf_obj_hdr_b->object_size, blf_obj_hdr_b->object_type );

    /* after leaving this function we incresed also indexes - */
    fp_buf->file_index--;
    fp_buf->buffer_container.buffer_index--;

}