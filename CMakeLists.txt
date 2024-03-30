cmake_minimum_required(VERSION 3.10)
project(rcnf VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(rcnf_lib STATIC c_rcnf/ext.c
        c_rcnf/env.c
        c_rcnf/shared/c_rcnf.c)
target_include_directories(rcnf_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(rcnf_exec c_rcnf/ext.c
        c_rcnf/env.c
        c_rcnf/shared/c_rcnf.c
        test.c)
set_target_properties(rcnf_exec PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/shared")

set(SOURCES c_rcnf/ext.c
        c_rcnf/env.c
        c_rcnf/shared/c_rcnf.c)
add_library(rcnf_shared SHARED ${SOURCES})
set_target_properties(rcnf_shared PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/dll
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/dll
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/dll)
