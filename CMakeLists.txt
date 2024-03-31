cmake_minimum_required(VERSION 3.10)
project(rcnf VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)

add_library(rcnf_lib STATIC c_rcnf/ext.c
        c_rcnf/env.c
        c_rcnf/lang/lplang.c
        c_rcnf/lang/structs/lang_structs.c
        c_rcnf/shared/c_rcnf.c
        c_rcnf/rcnf.c)
target_include_directories(rcnf_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(rcnf_exec c_rcnf/ext.c
        c_rcnf/env.c
        c_rcnf/shared/c_rcnf.c
        c_rcnf/lang/lplang.c
        c_rcnf/lang/structs/lang_structs.c
        test.c
        c_rcnf/rcnf.c)
set_target_properties(rcnf_exec PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/shared")

set(SOURCES c_rcnf/ext.c
        c_rcnf/env.c
        c_rcnf/shared/c_rcnf.c
        c_rcnf/lang/lplang.c
        c_rcnf/lang/structs/lang_structs.c
        c_rcnf/rcnf.c)
add_library(rcnf_shared SHARED ${SOURCES})
set_target_properties(rcnf_shared PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/dll
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/dll
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/dll)
