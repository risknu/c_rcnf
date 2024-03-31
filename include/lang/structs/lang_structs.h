#pragma once

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MAP_SIZE 124
#define MAX_TOKENS_LENGTH (MAX_MAP_SIZE * 3u)

typedef enum {
    untitled, string, equal,
    endp, endl, err, comment
} types_of;

typedef struct {
    char* keys[MAX_MAP_SIZE];
    char* values[MAX_MAP_SIZE];
    unsigned int count;
} map_array;

typedef struct {
    types_of type;
    char* value;
} token;

typedef struct {
    token tokens[MAX_TOKENS_LENGTH];
    unsigned int count;
} tokens_array;

token* create_token(types_of token_type, const char* token_value);
void free_token(token* token);
void append_token(tokens_array* array, token t);

void append_map(map_array* array, char* key, char* val);
