#include <Python.h>

/**
 *
 *
 *
 */

void print_python_dict(PyObject *d)
{
	if (!PyDict_Check(d))
	{
		printf("yay not a dict\n");
		return;
	}
	Py_ssize_t size = PyDict_Size(d);
	printf("[*] dictionary size: %zd\n", size);
	

}
