#include <rcnf.h>

static int file_ex(const char* file_path) {
    if (access(file_path, F_OK) != -1) {
        return 0;
    } else {
       return 1;
    }
}

const char* read_f(const char* file_path) {
    if (file_ex(file_path) == 1) {
        return "ERR=FNFE_ERR\n";
    }
    const char* return_to = read_file(file_path);
    return return_to;
}

void process_to(const char* file_path) {
    if (file_ex(file_path) == 1) {
        return;
    }
    process_to_env(file_path);
}

map_array extract_from_f(const char* file_path) {
    if (file_ex(file_path) == 1) {
        map_array null_tmp_array;
        append_map(&null_tmp_array, "ERR", "FNFE_ERR");
        return null_tmp_array;
    }
    return extract_from_file(file_path);
}

map_array extract_from_s(char* file_cstring) {
    return extract_from(file_cstring);
}
