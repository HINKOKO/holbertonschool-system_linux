#include <Python.h>
#include <stdbool.h>

#define PYABS(x) ((x) < 0 ? (-x) : (x))

/**
 * print_python_int - display a PyInt Object
 * @p: generic pointer to PyObject
 */

void print_python_int(PyObject *p)
{
	Py_ssize_t py_size, i, absolut;
	unsigned long cout = 0;
	digit *py_digits;

	if (!PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}

	py_size = ((PyVarObject *)p)->ob_size, absolut = PYABS(py_size);
	py_digits = ((PyLongObject *)p)->ob_digit;

	if (py_size > 3 || (py_size == 3 && py_digits[2] > 15))
	{
		printf("C unsigned long int overflow\n");
		return;
	}
	for (i = 0; i < absolut; i++)
		cout += py_digits[i] * (1L << (PyLong_SHIFT * i));
	if (py_size < 0)
		printf("-");
	printf("%lu\n", cout);
}
