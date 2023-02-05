
/* 
parser handler  blf_header*/

#ifndef BLF_HANDLER_H
#define BLF_HANDLER_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>


/*
symbols
*/

#define HOW_MANY_TO_READ 90000 
#define BYTES_TO_STORE   5000



#define HEADER_BYTE_SIZE    144U
#define HEADER_MARKER "LOGG"
#define CONTAINER_MARKER "LOBJ"

/* 

typedefs 
*/
struct buffer_tag {
    char * buffer;
    uint32_t buffer_index;
};
typedef struct buffer_tag buffer_t;

struct file_buffer_tag {
    buffer_t buffer_container;
    FILE * file_pointer_to_read;
    uint32_t file_index;
};
typedef struct file_buffer_tag fp_buffer_t; 

struct byte_find_tag {
    const char * to_be_find;
    const int length;
    void (*call_function)(fp_buffer_t *fp_buff);
    int index_to_be_checked; /* which of bytes now I am checking*/
};

typedef struct byte_find_tag byte_find_t;


struct _header_t 
{
    char name[4]; /* 4 bytes*/
    uint32_t  header_size; /*4*/
    uint8_t  B_array1[8]; /* 8 */
    uint64_t blf_file_size; /*8 */
    uint64_t blf_unpacked_file_size; /*8*/
    uint32_t L_data2; /*4*/
    uint32_t L_data3; /*4*/
    uint16_t H_data_1[8]; /* 16*/
    uint16_t H_data_2[8]; /* 16 */

};

typedef struct _header_t header_t;
/*
external definition
*/
extern byte_find_t byte_find_def_header; 

/*
external functiona
*/
extern void blf_header_parsing(fp_buffer_t * fp_buf); 
#endif