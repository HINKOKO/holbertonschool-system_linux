#include <Python.h>
#include <listobject.h>
#include <object.h>
#include <bytesobject.h>

void print_python_bytes(PyObject *p);


/**
 * print_python_list - prints basic info about given
 * Python lists
 * @p: PyObject object
*/

void print_python_list(PyObject *p)
{
	PyObject *x;
	long int size = PyList_Size(p);

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %zd\n", size);
	printf("[*] Allocated = %zd\n", ((PyListObject *)p)->allocated);
	for (int i = 0; i < size; i++)
	{
		x = PyList_GET_ITEM(p, i);
		printf("Element %d: %s\n", i, x->ob_type->tp_name);
		if (!strcmp(x->ob_type->tp_name, "bytes"))
			print_python_bytes(((PyListObject *)p)->ob_item[i]);
	}
}

/**
 * print_python_bytes - print basic info about python byte object
 * @p: pointer to PyObject ( a byte one hence )
*/

void print_python_bytes(PyObject *p)
{
	char *str = NULL;
	Py_ssize_t size;

	printf("[.] bytes object info\n");

	if (!PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	PyBytes_AsStringAndSize(p, &str, &size);
	printf("  size: %zd\n", size);
	printf("  trying string: %s\n", str);
	printf("  first %zd bytes:", size <= 10 ? size + 1 : 10);

	for (int i = 0; i <= size && i < 10; i++)
	{
		printf(" %02hhx", str[i]);
	}
	printf("\n");
}
