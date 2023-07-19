import ctypes

lib = ctypes.CDLL('./libPython.so')
lib.print_python_string.argtypes = [ctypes.py_object]
s = b"The spoon does not exist"
lib.print_python_string(s)
s = 15462
lib.print_python_string(s)
s = "The spoon does not exist"
lib.print_python_string(s)
