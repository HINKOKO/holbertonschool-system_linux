#include <Python.h>

char *decimal_to_string(digit *ptr_out, ssize_t size, int neg);
int long_to_str(PyObject *lg, char **str);

/**
 * print_python_int - display a PyInt Object
 * @p: generic pointer to PyObject
 *
 * _PyLong_DECIMAL_SHIFT => used to convert between Python's
 * internal binary repr
 * && the decimal repr used in the 'decimal' module
 */

void print_python_int(PyObject *p)
{
	char *str = NULL;

	if (long_to_str(p, &str) == -1)
	{
		printf("PROBLEM DUDE\n");
		return;
	}
	printf("%s\n", str);
	free(str);
}

/**
 * long_to_str - extract the digit from PyLong object
 * to decimals digits, then to be feeded to next function
 * @lg: generic pointer to PyObject
 * @str: double pointer to str
 * Return: -1 if failure, or 0 after successfull completion
 */

int long_to_str(PyObject *lg, char **str)
{
	PyLongObject *py;
	ssize_t size, size_py, i, j;
	digit *ptr_out, *ptr_in;
	int neg, d_num;

	py = (PyLongObject *)lg;
	size_py = Py_SIZE(lg) < 0 ? -Py_SIZE(lg) : Py_SIZE(lg);
	neg = size_py < 0;

	/**
	 * To determine the number of decimal digits required
	 * to represent the Python long integer value as string in the console
	 * extremely crucial since J.Barbier wants us to overflow the capacity of
	 * our beloved C programming language, evil guy
	 * 2**30 is equal to = 1,073,741,824 ~ 1 billion (10^9)
	 * Thats why _PyLong_DECIMAL_SHIFT 9, by shifting
	 * 9 position assuring accurate to decimal ?
	 * d_num = (33*_PyLong_DECIMAL_SHIFT) /
	 * (10*PyLong_SHIFT - 33 *_PyLong_DECIMAL_SHIFT)
	 * GUESS WHAT THIS FANCY BADABOUM MAKES 99
	*/
	d_num = 33 * _PyLong_DECIMAL_SHIFT / (10 * PyLong_SHIFT - 33 * _PyLong_DECIMAL_SHIFT);
	size = 1 + size_py + size_py / d_num;
	ptr_out = calloc(sizeof(digit), size);
	if (!ptr_out)
		return (-1);
	ptr_in = py->ob_digit;
	size = 0;
	for (i = size; --i >= 0;)
	{
		digit hi = ptr_in[i];

		for (j = 0; j < size; j++)
		{
			twodigits z = (twodigits)ptr_out[j] << PyLong_SHIFT | hi;

			hi = (digit)(z / _PyLong_DECIMAL_BASE);
			ptr_out[j] = (digit)(z - (twodigits)hi * _PyLong_DECIMAL_BASE);
		}
		while (hi)
		{
			ptr_out[size++] = hi % _PyLong_DECIMAL_BASE;
			hi /= _PyLong_DECIMAL_BASE;
		}
	}
	if (size == 0)
		ptr_out[size++] = 0;
	*str = decimal_to_string(ptr_out, size, neg);
	return (0);
}

/**
 * decimal_to_string - now takes the digit decimal
 * and throw it to a *str
 * @ptr_out: pointer out
 * @size: size
 * @neg: negative or not negative
 * Return: the str'ized num
*/

char *decimal_to_string(digit *ptr_out, ssize_t size, int neg)
{
	;

	digit rem, pow;
	char *str, *p;
	ssize_t strlen, i, j;

	strlen = neg + 1 + (size - 1) * _PyLong_DECIMAL_SHIFT;
	pow = 10;
	rem = ptr_out[size - 1];
	while (rem >= pow)
	{
		pow *= 10;
		strlen++;
	}
	str = calloc(1, strlen + 1);
	if (!str)
		return (NULL);
	p = str + strlen;
	for (i = 0; i < size - 1; i++)
	{
		rem = ptr_out[i];
		for (j = 0; j < _PyLong_DECIMAL_SHIFT; j++)
		{
			*--p = '0' + rem % 10;
			rem /= 10;
		}
	}
	rem = ptr_out[i];
	do {
		*--p = '0' + rem % 10;
		rem /= 10;
	} while (rem != 0);

	if (neg)
		*--p = '-';
	return (str);
}
