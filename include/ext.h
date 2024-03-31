#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <env.h>
#include <lang/lplang.h>
#include <lang/structs/lang_structs.h>

#define MAX_BUFFER_SIZE 124

char* read_file(const char* file_path);
void process_to_env(const char* file_path);
map_array extract_from_file(const char* file_path);
map_array extract_from(char* file_cstring);
