#include <env.h>

char* get_env(const char* key_string) {
    #ifdef _WIN32
        DWORD size = GetEnvironmentVariable(key_string, NULL, 0);
        if (size == 0) return NULL;
        char* value = (char*)malloc(size);
        if (!value) return NULL;
        GetEnvironmentVariable(key_string, value, size);
        return value;
    #else
        return getenv(key_string);
    #endif
}

int set_env(const char* key_string, const char* value_string) {
    #ifdef _WIN32
        if (!SetEnvironmentVariable(key_string, value_string)) {
            return GetLastError();
        }
        return 0;
    #else
        return setenv(key_string, value_string, 1);
    #endif
}

int unset_env(const char* key_string) {
    #ifdef _WIN32
        if (!SetEnvironmentVariable(key_string, NULL)) {
            return GetLastError();
        }
        return 0;
    #else
        return unsetenv(key_string);
    #endif
}
