import ctypes
from typing import List, Tuple

MAX_MAP_SIZE: int = 124

# Define map_entry structure to hold key-value pairs
class MapEntry(ctypes.Structure):
    _fields_ = [("key", ctypes.c_char_p), ("value", ctypes.c_char_p)]

# Define map_array structure
class MapArray(ctypes.Structure):
    _fields_ = [("entries", MapEntry * MAX_MAP_SIZE), ("count", ctypes.c_uint)]

# Load the DLL
dll = ctypes.CDLL("./shared/simple.dll")

# Define function prototypes
dll.dll_get_env.argtypes = [ctypes.c_char_p]
dll.dll_get_env.restype = ctypes.c_char_p

dll.dll_unset_env.argtypes = [ctypes.c_char_p]
dll.dll_unset_env.restype = ctypes.c_int

dll.dll_set_env.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
dll.dll_set_env.restype = ctypes.c_int

dll.dll_extract_from.argtypes = [ctypes.c_char_p]
dll.dll_extract_from.restype = MapArray

# Define wrapper functions
def get_env(key_string: bytes) -> bytes:
    return dll.dll_get_env(key_string)

def unset_env(key_string: bytes) -> int:
    return dll.dll_unset_env(key_string)

def set_env(key_string: bytes, value_string: bytes) -> int:
    return dll.dll_set_env(key_string, value_string)

def extract_from(file_cstring: bytes) -> MapArray:
    return dll.dll_extract_from(file_cstring)

# Example usage
set_env(b"HELLO", b"WORLD")
print(get_env(b"HELLO"))
result_map = extract_from(b"HELLO=WORLD\nDA=NET\n")
for i in range(result_map.count):
    entry = result_map.entries[i]
    print(f"Key: {entry.key.decode()}, Value: {entry.value.decode()}")
