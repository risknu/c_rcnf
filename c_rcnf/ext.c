#include "ext.h"

static tokens_array extract_to_tokens(char* file_cstring);
static token* get_next_token(char** file_cstring);

static token* create_token(types_of token_type, const char* token_value) {
    token* token_inst = (token*)malloc(sizeof(token));
    if (token_inst) {
        token_inst->type_of_token = token_type;
        token_inst->token_value = strdup(token_value);
    }
    return token_inst;
}

static void append_token(tokens_array* array, token t) {
    if (array->count < MAX_TOKENS_LENGTH) {
        array->tokens[array->count++] = t;
    }
}

static void append_map(map_array* array, char* key, char* val) {
    if (array->count < MAX_MAP_SIZE) {
        array->values[array->count] = val;
        array->keys[array->count] = key;
        array->count++;
    }
} 

static void free_token(token* token) {
    if (token) {
        free(token->token_value);
        free(token);
    }
}

map_array extract_from(char* file_cstring) {
    map_array map_values_array;
    map_values_array.count = 0u;

    tokens_array tokens = extract_to_tokens(file_cstring);
    
    return extract_from_tokens(tokens);
}

static map_array extract_from_tokens(tokens_array array) {
    map_array map_array_values;
    map_array_values.count = 0u;

    for (unsigned int ite = 0u; ite < array.count; ite++) {
        if (array.tokens[ite].type_of_token == equal) {
            char* key_string;
            char* value_string;
            if (ite-1 >= 0 && array.tokens[ite-1].type_of_token == untitled) {
                key_string = array.tokens[ite-1].token_value;
            } else {
                key_string = "ERR";
            }
            if (array.tokens[ite+1].type_of_token == untitled ||
                array.tokens[ite+1].type_of_token == string) {
                    value_string = array.tokens[ite+1].token_value;
            } else {
                value_string = "ERR_PAR";
            }
            append_map(&map_array_values, key_string, value_string);
        }
    }
    return map_array_values;
}

static tokens_array extract_to_tokens(char* file_cstring) {
    tokens_array tokens_instances_array;
    tokens_instances_array.count = 0u;

    token* token_inst;
    do {
        token_inst = get_next_token(&file_cstring);
        if (token_inst) {
            append_token(&tokens_instances_array, *token_inst);
        }
    } while (token_inst && token_inst->type_of_token != endp);

    return tokens_instances_array;
}

// TODO: add string and escape letters
static token* get_next_token(char** file_cstring) {
    char* start = *file_cstring;
    while (**file_cstring && isspace(**file_cstring)) {
        (*file_cstring)++;
    } if (**file_cstring == '\0') {
        return create_token(endp, "");
    }

    switch (**file_cstring) {
        case '=':
            (*file_cstring)++;
            return create_token(equal, "=");
        case '\n':
            (*file_cstring)++;
            return create_token(endl, ";");
        default:
            {
                char* end = *file_cstring;
                while (*end && *end != '\n' && *end != '=' && !isspace(*end)) {
                    end++;
                }
                char* token_value = (char*)malloc(end - start + 1);
                if (token_value) {
                    strncpy(token_value, start, end - start);
                    token_value[end - start] = '\0';
                    *file_cstring = end;
                    return create_token(untitled, token_value);
                } else {
                    return create_token(err, "ERR");
                }
            }
    }
}
