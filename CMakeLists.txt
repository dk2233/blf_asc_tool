cmake_minimum_required(VERSION 3.16.3)

project(ctests)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_COMPILER gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
add_compile_definitions(TESTS)

include(GNUInstallDirs)

include_directories(
    c_arg_parse
    deps/console-colors
    src
    )

#add_subdirectory(arrays)


add_executable(blf  
    deps/console-colors/console-colors.c
    c_arg_parse/arg_parse.c
    src/blf_analyse.c
    src/blf_handler.c
    src/files.c
    )
    
#target_include_directories(ctests 
#    $(CMAKE_CURRENT_LIST_DIR))

target_link_libraries(blf -Wall -Wextra)
 

