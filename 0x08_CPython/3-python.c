#include <Python.h>
#include <object.h>
#include <listobject.h>
#include <bytesobject.h>
#include <floatobject.h>
#include <stdlib.h>

void print_python_bytes(PyObject *p);

/**
 * print_python_float - print basic info about Python Float object
 * @p: pointer to Python object
*/

void print_python_float(PyObject *p)
{
	PyFloatObject *f = (PyFloatObject *)p;
	double val = f->ob_fval;
	char str[40];

	printf("[.] float object info\n");
	if (!PyFloat_Check(f))
	{
		printf("  [ERROR] Invalid Float Object\n");
		fflush(stdout);
		return;
	}
	sprintf(str, "%.16g", val);
	if (strchr(str, '.') != NULL)
		printf("  value: %s\n", str);
	else
		printf("  value: %.1f\n", val);

}

/**
 * print_python_bytes - print basic info about python byte object
 * @p: pointer to PyObject ( a byte one hence )
*/

void print_python_bytes(PyObject *p)
{
	const char *str = NULL;
	Py_ssize_t size;

	printf("[.] bytes object info\n");

	if (!PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	size = ((PyVarObject *)p)->ob_size;
	str = ((PyBytesObject *)p)->ob_sval;


	printf("  size: %zd\n", size);
	printf("  trying string: %s\n", str);
	printf("  first %zd bytes:", size < 10 ? size + 1 : 10);

	for (int i = 0; i <= size && i < 10; i++)
	{
		printf(" %02hhx", str[i]);
	}
	printf("\n");
}

/**
 * print_python_list - prints basic info about given
 * Python lists
 * @p: PyObject object
*/

void print_python_list(PyObject *p)
{
	long int size;
	PyListObject *list = (PyListObject *)p;
	const char *type;

	printf("[*] Python list info\n");
	if (!PyList_Check(list))
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	size = ((PyVarObject *)p)->ob_size;

	printf("[*] Size of the Python List = %zd\n", size);
	printf("[*] Allocated = %zd\n", list->allocated);
	for (int i = 0; i < size; i++)
	{
		type = (list->ob_item[i])->ob_type->tp_name;
		printf("Element %d: %s\n", i, type);
		if (!strcmp(type, "bytes"))
			print_python_bytes(list->ob_item[i]);
		if (!strcmp(type, "float"))
			print_python_float(list->ob_item[i]);
	}
}


