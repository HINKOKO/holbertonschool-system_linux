#include <Python.h>
#include <listobject.h>
#include <object.h>

/**
 * print_python_list - prints basic info about given
 * Python lists
 * @p: PyObject object
*/

void print_python_list(PyObject *p)
{
	printf("[*] Python list info\n");
	printf("[*] Size of the Python list = %i\n", Py_SIZE(p));
	printf("[*] Allocated = %i\n", (PyListObject *)p->allocated);
	for (int i = 0; i < PyList_Size(p); i++)
		printf("Element %d: %s", i, Py_TYPE(PyList_GET_ITEM(p, i)->ob_type));
}
