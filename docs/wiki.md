# Environment Variables Management Library

This library provides simple access to manage environment variables, offering basic functionality and ensuring five times faster operation compared to the standard python-dotenv.

## Requirements
To use this library, you need Python version 3.11 or higher and internet access to download the library. To install, execute the following commands:

### Python
```bash
$ pip install rcnf 
```
```bash
$ pip3 install rcnf # for Unix-like systems
```

Then simply import the module into your Python project:
```python
import rcnf
```

### C
To download the C library, you'll need to download it from GitHub and then include it in the project where you intend to use it. When compiling, add the following arguments:
```bash
$ gcc -o main main.c -L<path-to-lib-folder> -lrcnf_lib
```
Then simply include it using the directive:
```c
#include "rcnf.h"
```

# Functionality and Functions Overview
There are several functions available for use, all of which work correctly and efficiently. Here's the documentation for each method.

## `read_file` C/Python
A simple function that returns `char*` (`str|None`) of the file's text, which you can specify in the function argument `const char* file_path` (`str`).

```h
char* read_file(const char* file_path);
```
```python 
def read_file(file_path: str = None) -> str: ...
```

## `extract_from_file` C/Python
This function reads a file and passes it to the `extract_from` function, which returns a dictionary (`char* keys[...]`, `char* values[...]`, `unsigned int count`).

```h
typedef struct {
    char* keys[MAX_MAP_SIZE];
    char* values[MAX_MAP_SIZE];
    unsigned int count;
} map_array;

map_array extract_from_file(char* file_path);
```
```python
@dataclass
class map_array(ctypes.Structure):
    _fields_ = [
        ("keys", ctypes.c_char_p * MAX_MAP_SIZE),
        ("values", ctypes.c_char_p * MAX_MAP_SIZE),
        ("count", ctypes.c_uint)]
    keys: list[bytes]
    values: list[bytes]
    count: int

def extract_from_file(file_path: str = None) -> map_array: ...
```

## `get_env` C/Python
This function allows you to access environment variables, specifically retrieving one with the provided name.

```h
char* get_env(const char* key_string);
```
```python
def get_env(key_string: str = None) -> str | None: ...
```

## `unset_env` C/Python
This function enables removing an environment variable from the list of environment variables.

```h
int unset_env(const char* key_string);
```
```python
def unset_env(key_string: str = None) -> bool: ...
```

## `set_env` C/Python
This function allows you to add an environment variable to the list.

```h
int set_env(const char* key_string, const char* value_string);
```
```python
def set_env(key_string: str = None, value_string: str = None) -> bool: ...
```

## `extract_from` C/Python
This function allows you to obtain a `map_array` without reading a file, simply through a string.

```h
typedef struct {
    char* keys[MAX_MAP_SIZE];
    char* values[MAX_MAP_SIZE];
    unsigned int count;
} map_array;

map_array extract_from(char* file_cstring);
```
```python
@dataclass
class map_array(ctypes.Structure):
    _fields_ = [
        ("keys", ctypes.c_char_p * MAX_MAP_SIZE),
        ("values", ctypes.c_char_p * MAX_MAP_SIZE),
        ("count", ctypes.c_uint)]
    keys: list[bytes]
    values: list[bytes]
    count: int

def extract_from(file_cstring: str = None) -> map_array: ...
```

## `process_to_env` C/Python
This function reads a file and writes the data into the environment variables list.

```h
void process_to_env(char* file_path);
```
```python
def process_to_env(file_path: str = None) -> None: ...
```

## `map_to` Python
This function only exists in Python, and it converts `map_array` to a `dict`, allowing you to work with it like a regular dictionary.
