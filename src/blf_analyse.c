#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arg_parse.h"
#include "blf_config.h"



argument_config_t arg_config[] = {
    {"b=", blf_byte_number, "number of bytes to be read"},
    {"ba=", blf_analyze_start, "open blf file for analyzing"},
    {"aa=", asc_analyze_start, "open asc file for analyzing"},
    {"listblf=", blf_file_list, "only lists blf file"}, 
    {"listasc=", asc_file_list, "only lists asc type file"}, 
    {"", NULL, ""}, 
};


int main(int argc, char ** argv)
{
    parser_arguments(argc, argv);


    return 0;
}