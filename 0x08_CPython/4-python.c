#include <Python.h>
#include <unicodeobject.h>
#include <stdio.h>

/**
 * print_python_string - prints Python strings
 * @p: pointer to Python object
 */

void print_python_string(PyObject *p)
{
	long int size;
	wchar_t *buf = NULL;
	PyASCIIObject *str = (PyASCIIObject *)p;

	printf("[.] string object info\n");

	if (!PyUnicode_Check(p))
	{
		printf("  [ERROR] Invalid String Object\n");
		fflush(stdout);
		return;
	}
	size = PyUnicode_GET_LENGTH(p);
	printf("  type: %s%s\n", str->state.compact ? "compact " : "",
		   str->state.ascii ? "ascii" : "unicode object");
	printf("  length: %zd\n", size);

	buf = PyUnicode_AsWideCharString(p, &size);
	if (buf)
	{
		printf("  value: %ls\n", buf);
		PyMem_Free(buf);
	}
}
