#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arg_parse.h"
#include "blf_config.h"



argument_config_t arg_config[] = {
    {"a=", blf_analyze_start, "open blf file for analyzing"},
    {"list=", blf_file_list, "only lists blf file"}, 
};


int main(int argc, char ** argv)
{
    parser_arguments(argc, argv);


    return 0;
}