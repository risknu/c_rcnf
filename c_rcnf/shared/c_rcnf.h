#ifndef _C_RCNF_H
#define _C_RCNF_H

// functionality for c++ support(second)
#ifdef __cplusplus
    extern "C" {
#endif

#include <stdio.h>

#include "../env.h"
#include "../ext.h"

__declspec(dllexport) char* dll_get_env(const char* key_string);
__declspec(dllexport) int dll_unset_env(const char* key_string);
__declspec(dllexport) int dll_set_env(const char* key_string, const char* value_string);

__declspec(dllexport) map_array dll_extract_from(char* file_cstring);

#ifdef __cplusplus
    }
#endif

#endif
