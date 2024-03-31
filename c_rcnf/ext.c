#include <ext.h>

// TODO: add comments
// TODO: add comments blocks

char* read_file(const char* file_path) {
    FILE* file_pointer = fopen(file_path, "r");
    if (file_pointer == NULL) return "ERR=FR_ERR";

    size_t full_str_size = MAX_BUFFER_SIZE;
    char* full_str = (char*)malloc(full_str_size * sizeof(char));
    if (full_str == NULL) {
        fclose(file_pointer);
        return "ERR=ALLOC_ERR";
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
