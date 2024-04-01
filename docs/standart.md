# Code Writing Standard (RCNF)
There is also a coding standard in the `RCNF` language. In this section, I will show you the standard version:

## Standard - v2024.4.1 (RCNF)
This standard is designed to be simple to use and does not require much space or effort to master. Here's an example of its usage in practice:

### Variable Creation
Creating variables is very simple and convenient. To create a variable, simply enter the keyword and the variable's value:
```rcnf
KEY=VALUE
```
Note: Avoid syntax like this:
```rcnf
ERR !!! KEY=VALUE VALUE
```

### Data Types
There are two data types: strings and regular text. Here's an explanation of each data type:

`untitled` - a data type for text or a single word. It can only contain one word:
```rcnf
word
```

`string` - a string data type that can contain more than one word. There are two types of strings: `raw` and `normal`:
```rcnf
"This is normal \nstring"
```
```rcnf
>>> This is normal 
>>> string
```

`raw string` - also a string data type, but in this case, escape characters are not interpreted. This is convenient for preserving text with such characters:
```rcnf
'This is raw \nstring'
```
```rcnf
>>> This is raw \nstring
```

### Error Handling
When errors occur, a variable named `ERR` will be created, containing information about the error.
