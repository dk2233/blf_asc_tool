/*


Files

playground
opening, closing files



*/

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include <time.h>
#include "files.h"
#include "assert.h"



long int file_length(FILE *file_hd)
{
    long int file_size = 0UL;

    if (file_hd != NULL)
    {
        printf("actual location %ld ",ftell(file_hd));

        if(0 == fseek(file_hd, 0U, SEEK_END ))
        {

            file_size = ftell(file_hd);

            printf("actual location %ld ",ftell(file_hd));

        }
        /*  We need to return position to beginnig of file */
        fseek(file_hd, 0U, SEEK_SET );
        printf("actual location %ld \n",ftell(file_hd));
    }
    else
    {
        printf("something is wrong");
    }
    return file_size; 
}


void func_open_file(char * name, char * mode, FILE ** file_hd)
{
    /* open file in given mode */
    *file_hd = fopen((char*)name,(const char *)mode);

    if (NULL == *file_hd)
    {
        printf(" file: %s cannot be open\n",(char*)name);
    }
}

void func_open_file_FILE(void * name, void ** file_handler )
{
    /*  this type of function to return FILE pointer
     *  cannot work
     *  we need to use here ** double pointer
     *  to be able to return a pointer to changed pointer to FILE */
    FILE **file_hd = (FILE **)file_handler;

    *file_hd = fopen((char*)name, "r") ;

    if (NULL != *file_hd)
    {
        printf("file handler address %p\n",file_hd);
        char char1 = fgetc(*file_hd);
        printf("line from file: %s\n",(char*)name);
        while( (char1 != '\n' ) && (char1 != '\0'))   
        { 
            char1 = fgetc(*file_hd);
            printf("%c",char1);
        }
    }
}


int whole_file_to_one_str( FILE *file_handler, char *table )
{
    int is_it_ok = 0;
    char *start_tab = table;

    if ((file_handler != NULL) && (table != NULL))
    {

        char character;
        do 
        {
            character = fgetc(file_handler);
            if ( (character != '\0') &&(character >-1 ) && (character != EOF))
            {
            *(table++) = character;
            // printf(" %p %c \n",table, *(table-1) );
            }
        }
        while( (character != '\0') &&(character >-1 ) );

    }
    else
    {
    is_it_ok = 1;
    }
    table = start_tab;

    return is_it_ok;


}

FILE * file_binary_open(char* file_name)
{
    FILE * file1 = fopen(file_name, "rb+");

    if (file1 == NULL)
    {
        /* there is no such file
        create new*/

    file1 = fopen(file_name, "w+b");
    }


    return file1;

}