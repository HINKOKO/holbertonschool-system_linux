#include <Python.h>
#include <longintrepr.h>

#include <stdio.h>
#include <stdbool.h>

#define PY_ABS(x) ((x) < 0 ? (-x) : (x))

/**
 * print_python_int - prints Python integers
 * @p: pointer to PyObject prétendument entier
 * 64 bits platform => each digit is a 30 bit integers
 * 0 to 2^30 - 1
 * -------------------------------------
 * 32 bits platform => 15 bit integers
 * 0 to 2^15 - 1
 * ------------------------------------
 * max unsigned long C = 18446744073709551615
 * used python interpreter to check what limit we shouldn't reach
 * see computations below
 *
 * digits are stored in little endian order in ob_digit[]
 * suppose we have integer Python object with ob_digit = [1, 5, 7]
 * and ob_size = -3
 * we do the following:
 * base = 2**30 (or 1 << PyLong_SHIFT)
 * -(1 * base**0 + 5 * base**1 + 7 * base**2)
 * >>> -(1 * base**0 + 5 * base**1 + 7 * base**2)
 * -8070450537616637953
 * python3 -q to compute max ob_size for storing unsigned long int C
 * >>> x = 18446744073709551615
 * >>> base = 1 << 30
 * >>> x % base
 * 1073741823
 * >>> (x // base ) % base
 * 1073741823
 * >>> (x // base // base) % base
 * 15
 * >>> (x // base // base // base) % base
 * 0
 * >>>
 */

void print_python_int(PyObject *p)
{
	Py_ssize_t py_size, i;
	unsigned long int C_int = 0, pow_base;
	unsigned long int py_base;
	bool minus;

	if (!PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}

	py_size = PY_ABS(((PyVarObject *)p)->ob_size);
	minus = ((PyVarObject *)p)->ob_size < 0;
	py_base = 1 << PyLong_SHIFT;

	if (py_size < 3 ||
		(py_size == 3 && ((PyLongObject *)p)->ob_digit[2] < 16))
	{
		pow_base = 1;
		for (i = 0; i < py_size; i++)
		{
			C_int += pow_base * ((PyLongObject *)p)->ob_digit[i];
			pow_base *= py_base;
		}
		if (minus)
			putchar('-');
		printf("%lu\n", C_int);
	}
	else
		printf("C unsigned long int overflow\n");
}
