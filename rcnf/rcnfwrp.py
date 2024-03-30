from __future__ import annotations

import ctypes
from typing import Union, Optional, Any
from dataclasses import dataclass

MAX_MAP_SIZE: int = 124


@dataclass
class map_array(ctypes.Structure):
    _fields_ = [
        ("keys", ctypes.c_char_p * MAX_MAP_SIZE),
        ("values", ctypes.c_char_p * MAX_MAP_SIZE),
        ("count", ctypes.c_uint)]
    keys: list[bytes]
    values: list[bytes]
    count: int


lib_shared: ctypes.CDLL = ctypes.CDLL("./shared/simple.dll")

lib_shared.dll_get_env.argtypes = [ctypes.c_char_p]
lib_shared.dll_get_env.restype = ctypes.c_char_p

lib_shared.dll_unset_env.argtypes = [ctypes.c_char_p]
lib_shared.dll_unset_env.restype = ctypes.c_int

lib_shared.dll_set_env.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
lib_shared.dll_set_env.restype = ctypes.c_int

lib_shared.dll_extract_from.argtypes = [ctypes.c_char_p]
lib_shared.dll_extract_from.restype = map_array


def get_env(key_string: Union[str, bytes] = None, ret_bytes: bool = False) -> Union[bytes, str] | None:
    if key_string is None:
        return
    if isinstance(key_string, str):
        key_string: bytes = key_string.encode()
    return_to: bytes = lib_shared.dll_get_env(key_string)
    return return_to if ret_bytes else return_to.decode() if not return_to is None else None


def unset_env(key_string: Union[bytes, str] = None) -> int | None:
    if key_string is None:
        return
    if isinstance(key_string, str):
        key_string: bytes = key_string.encode()
    return lib_shared.dll_unset_env(key_string) == 0


def set_env(key_string: Union[bytes, str] = None, value_string: Union[bytes, str] = None) -> int | None:
    if key_string is None or value_string is None:
        return
    if isinstance(key_string, str):
        key_string: bytes = key_string.encode()
    if isinstance(value_string, str):
        value_string: bytes = value_string.encode()
    return lib_shared.dll_set_env(key_string, value_string) == 0


def extract_from(file_cstring: Union[bytes, str] = None) -> map_array | None:
    if file_cstring is None:
        return
    if isinstance(file_cstring, str):
        file_cstring: bytes = file_cstring.encode()
    return lib_shared.dll_extract_from(file_cstring)


def map_to(map_array_struct: map_array = None) -> dict | None:
    if map_array_struct is None:
        return
    to_dictionary: dict = {}
    for i in range(map_array_struct.count):
        key: str = map_array_struct.keys[i].decode('utf-8').replace('\n', '')
        value: str = map_array_struct.values[i].decode('utf-8')
        to_dictionary[key] = value
    return to_dictionary
