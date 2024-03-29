#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_MAP_SIZE 124
#define MAX_TOKENS_LENGTH (MAX_MAP_SIZE * 3u)

#define FALSE 0
#define TRUE 1

typedef enum {
    untitled, string, equal,
    endp, endl, err
} types_of;

typedef struct {
    char* keys[MAX_MAP_SIZE];
    char* values[MAX_MAP_SIZE];
    unsigned int count;
} map_array;

typedef struct {
    types_of type_of_token; 
    char* token_value;
} token;

typedef struct {
    token tokens[MAX_TOKENS_LENGTH];
    unsigned int count;
} tokens_array;

static token* create_token(types_of token_type, const char* token_value);
static void free_token(token* token);
static void append_token(tokens_array* array, token t);

static void append_map(map_array* array, char* key, char* val);

map_array extract_from(char* file_cstring);
static map_array extract_from_tokens(tokens_array array);
static tokens_array extract_to_tokens(char* file_cstring);
static token* get_next_token(char** file_cstring);
