#include <stdio.h>
#include "c_rcnf/ext.h"
//gcc -o main main.c -L./build -lmathlib
int main() {
    // map_array array_of = extract_from("NAME=HAHA\nABC=TEST\n");
    // for (int i = 0; i < array_of.count; i++) {
    //     printf("%s: %s\n", array_of.keys[i], array_of.values[i]);
    // }

    map_array array_of = extract_from_file("C:\\Users\\risknumak\\Desktop\\rcnfdll\\.env");
    for (int i = 0; i < array_of.count; i++) {
          printf("%s: %s\n", array_of.keys[i], array_of.values[i]);
    }
    return 0;
}
