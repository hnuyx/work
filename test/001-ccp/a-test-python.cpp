
/**
 * a-test.cpp
 * test of C/C++ calls Python modules
 * Henry 2019-05-11
 * */

#define PY_SSIZE_T_CLEAN

// includes: <stdio.h> <string.h> <errno.h> <limits.h> <assert.h> <stdlib.h>
#include <Python.h>

/**
 * only PyObject*
 * PyObject, PyObject, PyObject_HEAD, PyObject_VAR_HEAD
 * Macros: Py_REFCNT, Py_TYPE, Py_SIZE, PyObject_HEAD_INIT, PyVarObject_HEAD_INIT
 *         Py_INCREF, Py_DECREF
 * */

void test_dict()
{
    PyObject *pDict = PyDict_new();
    assert(PyDict_Check(pDict));
}


int main()
{
    Py_Initialize();
    if (0 == Py_IsInitialized())
    {
        printf("failed calling Py_Initialize()\n");
        return -1;
    }

    printf("Hello Python\n");

    // macros
    printf("%s\n", Py_STRINGIFY(123));



    Py_Finalize();
    return 0;
}
