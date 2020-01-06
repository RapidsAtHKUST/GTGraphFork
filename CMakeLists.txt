cmake_minimum_required(VERSION 3.6)
project(GTGraphFork C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH}) # To allow CMake to locate our Find*.cmake files
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
include_directories(SSCA2)

include_directories(sprng2.0-lite/include)
include_directories(.)

set(SPRNG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/sprng2.0-lite/lib/libsprng.a)

message(${CMAKE_CURRENT_BINARY_DIR}/lib)
message(${CMAKE_CURRENT_SOURCE_DIR}/spring2.0-lite)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

# for the `util/ips4o` (parallel sort)
if (ATOMIC_FOUND)
    link_libraries(${ATOMIC_LIBRARY})
endif ()
add_library(yche-utils util/log/log.cpp util/md5.cpp)
find_package(atomic)

link_libraries(yche-utils)
link_libraries(m)   # e.g. pow functions and so on.
add_custom_command(OUTPUT ${SPRNG_LIB}
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/sprng2.0-lite
        )
add_custom_target(sprng ALL
        COMMAND echo "This is ALL target sprng and it depends on ${SPRNG_LIB}"
        DEPENDS ${SPRNG_LIB}
        VERBATIM)

### 1st: with-some-cliques
set(SSCA_CORE GTgraph-ssca2-logic)
add_library(${SSCA_CORE} SSCA2/globals.c SSCA2/graph.c SSCA2/init.c SSCA2/utils.c)
add_dependencies(${SSCA_CORE} sprng)
target_link_libraries(${SSCA_CORE} PRIVATE ${SPRNG_LIB})

add_executable(GTgraph-ssca2 SSCA2/drive.c)
target_link_libraries(GTgraph-ssca2 PRIVATE ${SSCA_CORE})
add_executable(GTgraph-ssca2-bin SSCA2/drive_bin.cpp)
target_link_libraries(GTgraph-ssca2-bin PRIVATE ${SSCA_CORE})
###############################################33

### 2nd: random graph (ER model)
set(RANDOM_CORE GTgraph-random-logic)
add_library(${RANDOM_CORE} random/globals.c random/graph.c random/init.c random/utils.c)
add_dependencies(${RANDOM_CORE} sprng)
target_link_libraries(${RANDOM_CORE} PRIVATE ${SPRNG_LIB})

add_executable(GTgraph-random random/drive.c)
target_link_libraries(GTgraph-random PRIVATE ${RANDOM_CORE})

add_executable(GTgraph-random-bin random/drive_bin.cpp)
target_link_libraries(GTgraph-random-bin PRIVATE ${RANDOM_CORE})
################################################3333

### 3rd: rmat graph (kronecker model, scale-free generator)
set(RMAT_CORE GTgraph-rmat-logic)
add_library(${RMAT_CORE} R-MAT/globals.c R-MAT/graph.c R-MAT/init.c R-MAT/utils.c)
add_dependencies(${RMAT_CORE} sprng)
target_link_libraries(${RMAT_CORE} PRIVATE ${SPRNG_LIB})

add_executable(GTgraph-rmat R-MAT/drive.c)
target_link_libraries(GTgraph-rmat PRIVATE ${RMAT_CORE})

add_executable(GTgraph-rmat-bin R-MAT/drive_bin.cpp)
target_link_libraries(GTgraph-rmat-bin PRIVATE ${RMAT_CORE})
#############################

## make-install
install(TARGETS
        GTgraph-ssca2-bin GTgraph-random-bin GTgraph-rmat-bin
        #        GTgraph-ssca2 GTgraph-random GTgraph-rmat
        RUNTIME DESTINATION .
        RUNTIME DESTINATION .
        RUNTIME DESTINATION .
        #        RUNTIME DESTINATION .
        #        RUNTIME DESTINATION .
        #        RUNTIME DESTINATION .
        )

# install config files
add_custom_command(TARGET GTgraph-ssca2-bin POST_BUILD
        COMMAND mkdir -p ${CMAKE_INSTALL_PREFIX}/configurations
        COMMAND cp ${CMAKE_SOURCE_DIR}/SSCA2/config ${CMAKE_INSTALL_PREFIX}/configurations/ssca2-config
        COMMAND cp ${CMAKE_SOURCE_DIR}/SSCA2/config ${CMAKE_INSTALL_PREFIX}/configurations/ssca2-config-template
        )

add_custom_command(TARGET GTgraph-random-bin POST_BUILD
        COMMAND mkdir -p ${CMAKE_INSTALL_PREFIX}/configurations
        COMMAND cp ${CMAKE_SOURCE_DIR}/random/config ${CMAKE_INSTALL_PREFIX}/configurations/random-config
        COMMAND cp ${CMAKE_SOURCE_DIR}/random/config ${CMAKE_INSTALL_PREFIX}/configurations/random-config-template
        )

add_custom_command(TARGET GTgraph-ssca2-bin POST_BUILD
        COMMAND mkdir -p ${CMAKE_INSTALL_PREFIX}/configurations
        COMMAND cp ${CMAKE_SOURCE_DIR}/R-MAT/config ${CMAKE_INSTALL_PREFIX}/configurations/rmat-config
        COMMAND cp ${CMAKE_SOURCE_DIR}/R-MAT/config ${CMAKE_INSTALL_PREFIX}/configurations/rmat-config-template
        )
