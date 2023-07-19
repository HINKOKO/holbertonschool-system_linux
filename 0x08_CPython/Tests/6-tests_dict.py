import ctypes

lib = ctypes.CDLL('./libPython.so')
lib.print_python_dict.argtypes = [ctypes.py_object]
d = {
    'name': 'John',
    'age': 56,
    'city': 'Iakoutsk',
    'profession': 'ice cream seller',
    'height': 185,
    'favorite_color' : 'black',
    'hobbies': "surfing in Iakoutsk"
}
lib.print_python_dict(d)
