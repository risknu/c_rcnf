#include <shared/c_rcnf.h>

char* dll_read_file(const char* file_path) {
    return read_file(file_path);
}

map_array dll_extract_from_file(char* file_path) {
    return extract_from_file(file_path);
}

char* dll_get_env(const char* key_string) {
    return get_env(key_string);
}

int dll_unset_env(const char* key_string) {
    return unset_env(key_string);
}

int dll_set_env(const char* key_string, const char* value_string) {
    return set_env(key_string, value_string);
}

void dll_process_to_env(char* file_path) {
    process_to_env(file_path);
}

map_array dll_extract_from(char* file_cstring) {
    return extract_from(file_cstring);
}
