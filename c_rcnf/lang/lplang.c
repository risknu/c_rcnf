#include <lang/lplang.h>

tokens_array extract_to_tokens(char* file_cstring);
static token* get_next_token(char** file_cstring);

map_array extract_from_tokens(tokens_array array) {
    map_array map_array_values;
    map_array_values.count = 0u;

    for (unsigned int ite = 0u; ite < array.count; ite++) {
        if (array.tokens[ite].type == equal) {
            char* key_string;
            char* value_string;
            if (ite-1 >= 0 && array.tokens[ite-1].type == untitled) {
                key_string = array.tokens[ite-1].value;
            } else {
                key_string = "ERR";
            }
            if (array.tokens[ite+1].type == untitled ||
                array.tokens[ite+1].type == string) {
                    value_string = array.tokens[ite+1].value;
            } else {
                value_string = "ERR_PAR";
            }
            append_map(&map_array_values, key_string, value_string);
        }
    }
    return map_array_values;
}

tokens_array extract_to_tokens(char* file_cstring) {
    tokens_array tokens_instances_array;
    tokens_instances_array.count = 0u;

    token* token_inst;
    do {
        token_inst = get_next_token(&file_cstring);
        if (token_inst) {
            append_token(&tokens_instances_array, *token_inst);
        }
    } while (token_inst && token_inst->type != endp);

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
        case '#':
            return process_comment(start, file_cstring);
        default:
            return process_untitled(start, file_cstring);
    }
}

static token* process_comment(char* start, char** file_cstring) {
    char* end = *file_cstring;
    while (*end && *end != '\n') {
        end++;
    }
    char* token_value = (char*)malloc(end - start + 1);
    if (token_value) {
        strncpy(token_value, start, end - start);
        token_value[end - start] = '\0';
        *file_cstring = end;
        return create_token(comment, token_value);
    } else {
        return create_token(err, "ERR_NTV");
    }
}
