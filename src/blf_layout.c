#include "blf_handler.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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


void blf_main_header_object_parsing(fp_buffer_t *fp_buf, hdr_base_t * hdr_base_struct)
{
    uint8_t i = sizeof(hdr_base_t) - strlen(byte_find_def_header.to_be_find);
    uint32_t start_header_index = fp_buf->buffer_container.buffer_index +1 - strlen(byte_find_def_header.to_be_find);

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

    memcpy((void*)hdr_base_struct, (const void * ) &fp_buf->buffer_container.buffer[start_header_index], sizeof(hdr_base_t));

    printf("object version is %d object size has %d \nblf object size %ld \n object type %ld\n",hdr_base_struct->object_header_version,\
     hdr_base_struct->object_header_size, hdr_base_struct->object_size, hdr_base_struct->object_type );

    /* after leaving this function we incresed also indexes - */
    fp_buf->file_index--;
    fp_buf->buffer_container.buffer_index--;
}


void blf_object_parse_V1(fp_buffer_t * fp_buf, object_hdr_v1_t *obj_v1_struct)
{
    uint8_t i = sizeof(object_hdr_v1_t);
    uint32_t start_header_index = fp_buf->buffer_container.buffer_index +1 - strlen(byte_find_def_header.to_be_find);
    do 
    {
        /* thanks to such condition incrementation after leaving this callout
        will work fine*/
        fp_buf->file_index++;
        fp_buf->buffer_container.buffer[ ++(fp_buf->buffer_container.buffer_index) ] = getc(fp_buf->file_pointer_to_read);
    /* --i condition will make next byte after header to be also stored into buffer*/
    }  while(--i);
    putchar('\n');
    /*cast buffer to struct header_t*/

    obj_v1_struct = (object_hdr_v1_t *) &fp_buf->buffer_container.buffer[start_header_index];

    printf("object flags is %ld object client index %d \n blf object version %d \n object timestamp %lld\n",obj_v1_struct->flags,\
     obj_v1_struct->client_index, obj_v1_struct->obj_version, obj_v1_struct->timestamp );

    /* after leaving this function we incresed also indexes - */
    fp_buf->file_index--;
    fp_buf->buffer_container.buffer_index--;

}

void blf_object_parse_V2(fp_buffer_t * fp_buf)
{
    
}

void blf_object_parsing(fp_buffer_t *fp_buf)
{

    hdr_base_t hdr_base_data;
    object_hdr_v1_t obj_v1_data;

    blf_main_header_object_parsing(fp_buf, &hdr_base_data);

    if (hdr_base_data.object_header_version == 1)
    {
        blf_object_parse_V1(fp_buf, &obj_v1_data);
    }
    else if (hdr_base_data.object_header_version == 2)
    {
        blf_object_parse_V2(fp_buf);

    }

}