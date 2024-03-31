from __future__ import annotations

import ctypes
from os import path, PathLike
from typing import Union, Optional, Any, NoReturn, Mapping
from dataclasses import dataclass

MAX_MAP_SIZE: int = 124

@dataclass
class map_array(ctypes.Structure):
    """
    Represents a structure for mapping arrays.

    Attributes:
        keys (list[bytes]): List of keys.
        values (list[bytes]): List of values.
        count (int): Count of items.
    """
    _fields_ = [
        ("keys", ctypes.c_char_p * MAX_MAP_SIZE),
        ("values", ctypes.c_char_p * MAX_MAP_SIZE),
        ("count", ctypes.c_uint)]
    keys: list[bytes]
    values: list[bytes]
    count: int

lib_shared: ctypes.CDLL = ctypes.CDLL("./shared/dll/librcnf_shared.dll")

lib_shared.dll_get_env.argtypes = [ctypes.c_char_p]
lib_shared.dll_get_env.restype = ctypes.c_char_p

lib_shared.dll_unset_env.argtypes = [ctypes.c_char_p]
lib_shared.dll_unset_env.restype = ctypes.c_int

lib_shared.dll_set_env.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
lib_shared.dll_set_env.restype = ctypes.c_int

lib_shared.dll_extract_from.argtypes = [ctypes.c_char_p]
lib_shared.dll_extract_from.restype = map_array

lib_shared.dll_read_file.argtypes = [ctypes.c_char_p]
lib_shared.dll_read_file.restype = ctypes.c_char_p

lib_shared.dll_process_to_env.argtypes = [ctypes.c_char_p]
lib_shared.dll_process_to_env.restype = None

lib_shared.dll_extract_from_file.argtypes = [ctypes.c_char_p]
lib_shared.dll_extract_from_file.restype = map_array

def get_env(key_string: Union[str, bytes] = None, ret_bytes: bool = False) -> Union[bytes, str, None]:
    """
    Retrieves environment variable value.

    Args:
        key_string (Union[str, bytes]): Key of the environment variable.
        ret_bytes (bool): Flag to determine if the value should be returned as bytes.

    Returns:
        Union[bytes, str, None]: Environment variable value.
    """
    if key_string is None:
        return None
    if isinstance(key_string, str):
        key_string: bytes = key_string.encode()
    return_to: bytes = lib_shared.dll_get_env(key_string)
    return return_to if ret_bytes else return_to.decode() if not return_to is None else None

def unset_env(key_string: Union[bytes, str] = None) -> Union[bool, None]:
    """
    Unsets environment variable.

    Args:
        key_string (Union[bytes, str]): Key of the environment variable.

    Returns:
        Union[bool, None]: True if successful, else False.
    """
    if key_string is None:
        return None
    if isinstance(key_string, str):
        key_string: bytes = key_string.encode()
    return lib_shared.dll_unset_env(key_string) == 0

def set_env(key_string: Union[bytes, str] = None, value_string: Union[bytes, str] = None) -> Union[bool, None]:
    """
    Sets environment variable.

    Args:
        key_string (Union[bytes, str]): Key of the environment variable.
        value_string (Union[bytes, str]): Value of the environment variable.

    Returns:
        Union[bool, None]: True if successful, else False.
    """
    if key_string is None or value_string is None:
        return None
    if isinstance(key_string, str):
        key_string: bytes = key_string.encode()
    if isinstance(value_string, str):
        value_string: bytes = value_string.encode()
    return lib_shared.dll_set_env(key_string, value_string) == 0

def extract_from(file_cstring: Union[bytes, str] = None) -> Union[map_array, None]:
    """
    Extracts data from a file.

    Args:
        file_cstring (Union[bytes, str]): Path to the file.

    Returns:
        Union[map_array, None]: Extracted data.
    """
    if file_cstring is None:
        return None
    if isinstance(file_cstring, str):
        file_cstring: bytes = file_cstring.encode()
    return lib_shared.dll_extract_from(file_cstring)

def extract_from_file(file_path: Union[PathLike, str, bytes] = None) -> Union[map_array, None]:
    """
    Extracts data from a file.

    Args:
        file_path (Union[PathLike, str, bytes]): Path to the file.

    Returns:
        Union[map_array, None]: Extracted data.
    """
    if file_path is None:
        return None
    if isinstance(file_path, str):
        file_path: bytes = file_path.encode()
    return lib_shared.dll_extract_from_file(file_path)

def read_file(file_path: Union[PathLike, bytes, str] = None, ret_bytes: bool = False) -> Union[bytes, str, None]:
    """
    Reads content from a file.

    Args:
        file_path (Union[PathLike, bytes, str]): Path to the file.
        ret_bytes (bool): Flag to determine if the content should be returned as bytes.

    Returns:
        Union[bytes, str, None]: Content of the file.
    """
    if file_path is None:
        return None
    if isinstance(file_path, str):
        file_path: bytes = file_path.encode()
    to_return: bytes = lib_shared.dll_read_file(file_path) 
    return to_return if ret_bytes else to_return.decode() if not to_return is None else None

def map_to(map_array_struct: map_array = None) -> Union[Mapping[str, str], None]:
    """
    Maps array to dictionary.

    Args:
        map_array_struct (map_array): Structure containing keys and values.

    Returns:
        Union[Mapping[str, str], None]: Mapped dictionary.
    """
    if map_array_struct is None:
        return None
    to_dictionary: dict = {}
    for i in range(map_array_struct.count):
        key: str = map_array_struct.keys[i].decode('utf-8')
        if key[0] == "\n": 
            key: str = key[1:]
        value: str = map_array_struct.values[i].decode('utf-8')
        to_dictionary[key] = value
    return to_dictionary

def process_to_env(file_path: Union[PathLike, bytes, str] = None) -> NoReturn:
    """
    Processes data to environment.

    Args:
        file_path (Union[PathLike, bytes, str]): Path to the file.

    Returns:
        NoReturn: No return value.
    """
    if file_path is None:
        return None
    if isinstance(file_path, str):
        file_path: bytes = file_path.encode()
    lib_shared.dll_process_to_env(file_path)

print(map_to(extract_from_file("C:\\Users\\risknumak\\Desktop\\rcnfdll\\.env"))['HELLO'])
