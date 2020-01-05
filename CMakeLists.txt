cmake_minimum_required(VERSION 3.6)
project(GTGraphFork C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

option(DUMP_COMPILATION_TO_FILE "dump compilation to files" OFF)
if (NOT DUMP_COMPILATION_TO_FILE)
    set(CMAKE_VERBOSE_MAKEFILE ON)
else ()
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # dump compilation commands to compile_commands.json
endif ()

add_compile_options(-Wall -O3 -g -march=native)
add_definitions(-DUSE_LOG)

include_directories(R-MAT)
include_directories(random)
include_directories(sprng2.0-lite/include)
include_directories(sprng2.0-lite/src)
include_directories(SSCA2)

#add_executable(GTGraphFork
#        R-MAT/drive.c
#        R-MAT/globals.c
#        R-MAT/graph.c
#        R-MAT/init.c
#        R-MAT/utils.c
#
#        random/drive.c
#        random/globals.c
#        random/graph.c
#        random/init.c
#        random/utils.c
#
#        SSCA2/drive.c
#        SSCA2/globals.c
#        SSCA2/graph.c
#        SSCA2/init.c
#        SSCA2/utils.c
#        )

set(SPRNG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/sprng2.0-lite/lib/libsprng.a)

message(${CMAKE_CURRENT_BINARY_DIR}/lib)
message(${CMAKE_CURRENT_SOURCE_DIR}/spring2.0-lite)

link_libraries(m)
add_custom_command(OUTPUT ${SPRNG_LIB}
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/sprng2.0-lite
        )
add_custom_target(sprng ALL
        COMMAND echo "This is ALL target sprng and it depends on ${SPRNG_LIB}"
        DEPENDS ${SPRNG_LIB}
        VERBATIM)
add_executable(GTgraph-ssca2
        SSCA2/drive.c
        SSCA2/globals.c
        SSCA2/graph.c
        SSCA2/init.c
        SSCA2/utils.c
        )
add_dependencies(GTgraph-ssca2 sprng)
target_link_libraries(GTgraph-ssca2 PRIVATE ${SPRNG_LIB})
