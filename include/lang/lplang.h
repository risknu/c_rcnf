#pragma once

#include <lang/structs/lang_structs.h>

map_array extract_from_tokens(tokens_array array);
tokens_array extract_to_tokens(char* file_cstring);
static token* get_next_token(char** file_cstring);

static token* process_untitled(char* start, char** file_cstring);
static token* process_string(char** file_cstring);
