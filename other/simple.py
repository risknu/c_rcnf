import ctypes

lib = ctypes.CDLL("./simple.dll")

lib.ping.restype = None
lib.ping.argtypes = None

lib.ping()