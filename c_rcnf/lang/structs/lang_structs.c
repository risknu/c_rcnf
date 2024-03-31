#include <lang/structs/lang_structs.h>

token* create_token(types_of token_type, const char* token_value) {
    token* token_inst = (token*)malloc(sizeof(token));
    if (token_inst) {
        token_inst->type_of_token = token_type;
        token_inst->token_value = strdup(token_value);
    }
    return token_inst;
}

void append_token(tokens_array* array, token t) {
    if (array->count < MAX_TOKENS_LENGTH) {
        array->tokens[array->count++] = t;
    }
}

void append_map(map_array* array, char* key, char* val) {
    if (array->count < MAX_MAP_SIZE) {
        array->values[array->count] = val;
        array->keys[array->count] = key;
        array->count++;
    }
} 

void free_token(token* token) {
    if (token) {
        free(token->token_value);
        free(token);
    }
}
