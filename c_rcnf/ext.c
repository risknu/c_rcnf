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

char* read_file(const char* file_path) {
    FILE* file_pointer = fopen(file_path, "r");
    if (file_pointer == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        return NULL;
    }

    size_t full_str_size = MAX_BUFFER_SIZE;
    char* full_str = (char*)malloc(full_str_size * sizeof(char));
    if (full_str == NULL) {
        fclose(file_pointer);
        fprintf(stderr, "Memory allocation error.\n");
        return NULL;
    }
    
    full_str[0] = '\0';

    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), file_pointer) != NULL) {
        strcat(full_str, buffer);
    }
    
    fclose(file_pointer);
    return full_str;
}

map_array extract_from_file(char* file_path) {
    return extract_from(read_file(file_path));
} void process_to_env(char* file_path) {
    map_array file_array = extract_from_file(file_path);
    for (unsigned int ite; ite < file_array.count; ite++) {
        set_env(file_array.keys[ite], file_array.values[ite]);
    }
} map_array extract_from(char* file_cstring) {
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

static token* process_string(char** file_cstring) {
    char* end;
    if (**file_cstring == '\'') {
        end = strchr(*file_cstring + 1, '\'');
    } else {
        end = strchr(*file_cstring + 1, '"');
    }

    if (!end) {
        return create_token(err, "ERR_USL");
    }

    char* token_value = (char*)malloc(end - *file_cstring + 1);
    if (token_value) {
        int i = 0;
        char* curr = *file_cstring + 1;
        while (curr < end) {
            if (*curr == '\\') {
                curr++;
                switch (*curr) {
                    case 'n':
                        token_value[i++] = '\n';
                        break;
                    case 't':
                        token_value[i++] = '\t';
                        break;
                    case '\\':
                        token_value[i++] = '\\';
                        break;
                    default:
                        token_value[i++] = *curr;
                        break;
                }
            } else {
                token_value[i++] = *curr;
            }
            curr++;
        }
        token_value[i] = '\0';
        *file_cstring = end + 1;
        return create_token(string, token_value);
    } else {
        return create_token(err, "ERR_NTV");
    }
}

static token* process_untitled(char* start, char** file_cstring) {
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
        return create_token(err, "ERR_NTV");
    }
}

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
        case '\'':
        case '"':
            return process_string(file_cstring);
        default:
            return process_untitled(start, file_cstring);
    }
}
