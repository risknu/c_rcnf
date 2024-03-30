# Fast library for working with environment variables
This library provides functionality for working with environment variables, including fast addition and removal, as well as a convenient error handling system (or rather, its absence). The library is written in pure C using only built-in libraries. It is also equipped with a flexible lexer and supports both Windows and Unix systems, including MacOS and FreeBSD.

There is also a Python wrapper written using the built-in `ctypes` library for Python version 3.11 and above.

## Features
Everything is written in C11, and the library does not depend on external modules, using only built-in modules.

## Usage Examples
Since the library is designed to work with both C and Python, the usage examples are almost identical because it's just an adaptation from C to Python.

### Working with environment variables
**Python**
```python
from rcnf import get_env, unset_env, set_env
print(get_env("VAR_NAME")) # get
print(unset_env("VAR_NAME")) # remove
print(set_env("VAR_NAME", "VAR_VALUE")) # add
```

**C**
```c
#include <rcnf.h>
#include <stdio.h>
int main() {
    printf("%s\n", get_env("VAR_NAME")); // get (returns char*)
    printf("%s\n", unset_env("VAR_NAME")); // remove (returns int)
    printf("%s\n", set_env("VAR_NAME", "VAR_VALUE")); // add (returns int)
    return 0;
}
```

### Reading from a file
**Python**
```python
from rcnf import extract_from, extract_from_file, read_file
print(extract_from("NAME=ABC\n")) # extract from string 
print(extract_from_file("<file_path>")) # extract from file
print(read_file("<file_path>")) # read file
```

**C**
```c
#include <rcnf.h>
#include <stdio.h>
int main() {
    map_array get_from_string = extract_from("NAME=ABC\n"); // extract from string
    map_array get_from_file = extract_from_file("<file_path>"); // extract from file
    char* file_string = read_file("<file_path>"); // read file

    return 0;
}
```

`map_array` is a simple structure that contains lists `keys`, `values`, and their length (`count`), which can be compared to `dict` in Python.

To get a `dict` from an object of the `map_array` class in Python, you can use the class method `to_dict()` or the function `map_to(<...>)`.

## License
The project is distributed under the Apache License 2.0.
