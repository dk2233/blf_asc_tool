#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arg_parse.h"
#include "blf_config.h"



argument_config_t arg_config[] = {
    {"b=", blf_byte_number, "number of bytes to be read"},
    {"a=", blf_analyze_start, "open blf file for analyzing"},
    {"list=", blf_file_list, "only lists blf file"}, 
    {"", NULL, ""}, 
};


int main(int argc, char ** argv)
{
    parser_arguments(argc, argv);


    return 0;
}