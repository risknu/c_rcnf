#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#ifdef _WIN32
    #include <windows.h>
    #define STRDUP _strdup
#else
    #include <unistd.h>
    #define STRDUP strdup
#endif

char* get_env(const char* key_string);
int unset_env(const char* key_string);
int set_env(const char* key_string, const char* value_string);
