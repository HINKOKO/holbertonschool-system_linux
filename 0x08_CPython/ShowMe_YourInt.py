import ctypes
import sys



i = 1111111111222222222233333333334444444444555555555566666666667777777777888888888899999999990000000000

# convert python int to a C long int
py_int_object = ctypes.py_object(i)



# Acces the ob_digit array from C long int
ob_digit_address = ctypes.c_void_p.from_address(id(py_int_object) + ctypes.sizeof(ctypes.py_object(None)))

if sys.maxsize > 2**32:
    digit_pointer_type = ctypes.POINTER(ctypes.c_uint64)
else:
    digit_pointer_type = ctypes.POINTER(ctypes.c_uint32)

ob_digit_array = ctypes.cast(ob_digit_address, digit_pointer_type)
num_digits = abs(i.bit_length() // 30) + 1


# print the ob_digit array
digit_ob = []
for i in range(num_digits):
    digit_ob.append(ob_digit_array[i])

print(f"{digit_ob}")
