# **CPython :snake:**

## **CPython -- What the hell is that**

**CPython** is a Python interpreter written in... C <br>
It's one of the Python implementations, along with "PyPy", "Jython", "IronPython"... and others, but CPython remains the most popular and well maintained. However it would be false to say that all Python programming language lies into CPython -> its **reference implementation.**
Indeed, there's some implementations details that you won't find in CPython.
We could rather say that Python is defined **partly** by the **_Python Language Reference_** and partly by its main implementation, **_CPython_**. <br>

In this project folder, we use the Python/C API that CPython provides, which allows to extend Python with C code, and embed Python inside C !

The execution of a Python program roughly consists of:

- Initialization
  CPython initializes data structures required to run Python, prepares things such as built-in types, built-in modules, sets-up import ect...

- Compilation
  CPython is an **interpreter**, not a compiler in a sense that it doesn't produce machine code. However, CPython translates source code into some intermediate stage representation before executing it. => It parses the source code an build an **AST** (**A**bstract **S**yntax **T**ree), and generates bytecodes from AST.
  **Bytecode** is a series of instructions, each instruction cosists of two bytes: one for an opcode and one for an argument.

  ```
  def inc(x):
  return x + 3
  ```

  Its bytecode looks like:

  ```
  ~/cpython/schuku$ python3 -m dis basic.py
  3           0 LOAD_CONST               0 (<code object inc at 0x7f7cc4197520, file "basic.py", line 3>)
              2 LOAD_CONST               1 ('inc')
              4 MAKE_FUNCTION            0
              6 STORE_NAME               0 (inc)
              8 LOAD_CONST               2 (None)
             10 RETURN_VALUE

  Disassembly of <code object inc at 0x7f7cc4197520, file "basic.py", line 3>:
  4 0 LOAD_FAST 0 (x)
  2 LOAD_CONST 1 (3)
  4 BINARY_ADD
  6 RETURN_VALUE
  ```

At the heart of CPython lies a virtual machine that executes Bytecodes in a giant loop that runs while there are instructions to run.

- Interpretation
  Executes the bytecode of the `code object`

## **Task 4 - Strings**

We used the function

```

wchar_t *PyUnicode_AsWideCharString(PyObject *unicode, Py_ssize_t \*size)

```

The `wchar_t` type is a **_wide character type_** in C programming. It's used to represent a wide character that can hold a wider range of characters than a regular 'char' type. <br>
=> The purpose of `**wchar_t**` is to provide support for multibyte character set.

wchar_t Wide chars are needed for stuff like this:

```

숟가락은 존재하지 않는다

ложка не существует

```

The PyUnicode_AsWideCharString convert the **Unicode object** to a wide character string. Output string always end with a null character.
--> returns a buffer --allocated by PyMem_Alloc() -- it is your responsability to free it with PyMem_Free() on success.

```

```

## **Exercise 5 - CPython Integers**

Python Integers can be as large as we want, and their sizes are only limited by the amount of available memory. They are also known as **_bignums._**
Many programming languages comes with this feature of "bignums" (JavaScript, Ruby, Go, C# ...) The general architecture to represent bignums differs slighty depending on languages but the general picture remains the same.

### **Bignum representation in Python**

Imagine you have to represent a big huge astonishing number, such as 1526486215764325896. <br>
The most obvious way is to store it as [1, 5, 2, 6, 4, 8, 6, 2, 1, 5, 7, 6, 4, 3, 2, 5, 8, 9, 6], guess what this is kind of essentially how it works. <br>
The very big difference is that instead of using **base 10** -- really inefficient because image using only 10 possibles values out of one byte of representation for example (which makes 10 out of 256, what a waste !) -- They solved this problem by using much larger base, our dear CPython uses...
**2^15** or **2^30** depending on the machine. With larger bases, less digits are used, and the less digits we use, the faster arithmetic stuff are performed.

==> `longintrepr.h` declares everything related to the Python integers representation.

Well guys, so we know that in CPython implementation, Python integers are stored in a variable length array of digits. <br>
These digits are store in **little-endian** order, least significant at index 0, then 1, an so on... <br>
