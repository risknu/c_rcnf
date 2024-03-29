#include <stdio.h>
#include "c_rcnf/ext.h"

int main() {
    map_array array_of = extract_from("NAME=HAHA\nABC=TEST\n");
    for (int i = 0; i < array_of.count; i++) {
        printf("%s: %s\n", array_of.keys[i], array_of.values[i]);
    }
    return 0;
}
