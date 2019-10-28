
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <frameobject.h>
#include <structmember.h>

#include <string.h>
#include <wchar.h>

#include <list>
#include <string>
#include <iostream>
using namespace std;

int main()
{
    Py_Initialize();

    //const wchar_t *str = L"好、支持、顶";
    const char *str = "好、支持、顶";

    //PyObject *line = PyUnicode_FromFormat("%ls", str);
    //printf("%s\n", PyUnicode_1BYTE_DATA(line));

    //PyObject *pystr = PyUnicode_Encode(str, wcslen(str), "utf-8", "backslashreplace");

    PyObject *pystr = PyUnicode_DecodeUTF8(str, strlen(str), "backslashreplace");

    Py_Finalize();
    return 0;
}
