
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <frameobject.h>
#include <structmember.h>

#include <list>
#include <string>
#include <iostream>
#include <thread>
using namespace std;

typedef struct _TEMP
{
    _TEMP(int i)
    {
        number = i;
    }
    int number;
} Temp;

typedef struct _unit
{
    int numa;
    int numb;
} Unit;

typedef struct _TEMP_OBJECT
{
    PyObject_HEAD
    int number;
    Unit unit;
} TempObject;

list<Temp*> tlist;

typedef struct _TEMP_LIST_OBJECT
{
    PyObject_HEAD
    list<Temp*>::iterator iter;
    int number;
} TempListObject;

PyObject* TempSelfiter(PyObject *obj)
{
    TempListObject *objt = (TempListObject*)obj;
    objt->iter = tlist.begin();
    if(objt->iter == tlist.end())
        return NULL;
    objt->number = (*(objt->iter))->number;
    Py_INCREF(obj);
    return obj;
}

PyObject* TempListNext(TempListObject *it)
{
    if(it->iter == tlist.end())
    {
        return NULL;
    }

    it->number = (*(it->iter))->number;
    ++ it->iter;
    Py_INCREF(it);
    return (PyObject*) it;
}

int TempListInit(TempListObject*self, PyObject *args, PyObject *kwds)
{
    self->iter = tlist.begin();
    self->number = -1;
    return 0;
}

PyMemberDef TempListMembers[] =
{
    {"number", T_INT, offsetof(TempListObject, number), 0, "temp list number"},
    {NULL}
};

void TempListDealloc(TempListObject *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}

PyObject* TempListNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    TempListObject *self;
    self = (TempListObject*) type->tp_alloc(type, 0);

    return (PyObject*)self;
}

PyTypeObject TempListType =
{
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "TempM2.TempList",
    .tp_basicsize = sizeof(TempListObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)&TempListDealloc,
    .tp_doc = "temp list object",
    .tp_iter = (getiterfunc)&TempSelfiter,
    .tp_iternext = (iternextfunc)&TempListNext,
    .tp_members = TempListMembers,
    .tp_init = (initproc)&TempListInit,
    .tp_new = (newfunc)&TempListNew,
};

void TempDealloc(TempObject *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}

PyObject* TempNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    TempObject *self;
    self = (TempObject*) type->tp_alloc(type, 0);
    if (self)
    {
        self->number = 1;
        self->unit.numa = 2;
        self->unit.numb = 3;
    }

    return (PyObject*)self;
}

int TempInit(TempObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"number", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist,
                                     &self->number))
        return -1;

    return 0;
}

PyMemberDef TempMembers[] =
{
    {"number", T_INT, offsetof(TempObject, number), 0, "temp number"},
    {"numa", T_INT, offsetof(TempObject, unit.numa), 0, "temp number"},
    {"numb", T_INT, offsetof(TempObject, unit.numb), 0, "temp number"},
    {NULL}
};

PyObject* TempName(TempObject *self, PyObject *Py_UNUSED(ignored))
{
    return PyUnicode_FromFormat("Temp name");
}

PyObject* TempStr(TempObject *self)
{
    return PyUnicode_FromFormat("%d", self->number);
}

PyObject* TempHelloFunc(PyObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    //PyObject_Print(args[0], stdout, 0);
    //PyObject_Print(args[1], stdout, 0);
    //PyObject_Print(args[2], stdout, 0);
    //printf("\n");
    PyObject *res = PyObject_Str(args[0]);
    if (res)
    {
        if (PyBytes_Check(res))
            printf("%s\n", PyBytes_AS_STRING(res));
        else if(PyUnicode_Check(res))
        {
            PyObject *t = PyUnicode_AsEncodedString(res, "utf-8", "backslashreplace");
            if(t)
                printf("%s\n", PyBytes_AS_STRING(t));
        }
    }
    printf("\n");
    return PyUnicode_FromFormat("Hello Func");
}

PyObject* TempHeyFunc(PyObject *self, PyObject *args, PyObject *kwds)
{
    const char *addr = NULL, *abi = NULL; 
    Py_ssize_t addr_size, abi_size;
    double value = 0.0;
    int types = 0;
    static char *kwlist[] = {"address", "abi", "value", "types", "li", NULL};
    PyObject *list;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|s#s#diO", kwlist,
                                     &addr, &addr_size, &abi, &abi_size, &value, &types, &list))
    {
        printf("be here 1\n");
        PyObject* err=PyErr_Occurred();
        if(err)
        {
            PyObject_Print(err, stdout, 0);
        }
        return NULL;
    }

    printf("list size: %u\n", PyList_Size(list));
    for(Py_ssize_t i = 0; i < PyList_Size(list); i ++)
    {
        char* buff = NULL;
        Py_ssize_t length = 0;
        printf("%X\n", ((PyListObject *)list)->ob_item[i]);
        if(PyBytes_AsStringAndSize(PyUnicode_AsASCIIString(PyList_GetItem(list, i)), &buff, &length) == -1)
        {
            printf("list %d--failed\n", i);
            continue;
        }
        printf("list %d--%s\n", i, buff);
    }

    printf("be here 2 %s %u\n", addr, addr_size);
    printf("be here 3 %s %u\n", abi, abi_size);
    printf("%s\n", addr);
    printf("%s, %s\n", addr, abi);
    printf("%s, %s, %lf\n", addr, abi, value);
    //printf("%s, %s, %lf, %d\n", addr, abi, value, types);

    return NULL;
}

PyMethodDef TempMethods[] =
{
    {"name",      (PyCFunction) TempName,      METH_NOARGS,                   "return the name" },
    {"helloFunc", (PyCFunction) TempHelloFunc, METH_FASTCALL | METH_KEYWORDS, "Hello func"      },
    {"heyFunc",   (PyCFunction) TempHeyFunc,   METH_VARARGS | METH_KEYWORDS,  "hey func"        },
    {NULL}
};

PyTypeObject TempType =
{
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "TempM.Temp",
    .tp_basicsize = sizeof(TempObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)&TempDealloc,
    .tp_str = (reprfunc)&TempStr,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "temp object",
    .tp_methods = TempMethods,
    .tp_members = TempMembers,
    .tp_init = (initproc)&TempInit,
    .tp_new = (newfunc)&TempNew,
};

PyModuleDef TempModule =
{
    PyModuleDef_HEAD_INIT,
    .m_name = "TempM",
    .m_doc = "Temp module",
    .m_size = -1,
};

PyMODINIT_FUNC PyInitTemp()
{
    PyObject *m;
    if (PyType_Ready(&TempType) < 0)
        return NULL;

    m = PyModule_Create(&TempModule);
    if (!m)
        return NULL;

    Py_INCREF(&TempType);
    PyModule_AddObject(m, "TempM", (PyObject *)&TempType);

    return m;
}

typedef struct _TEMP_OBJECT2
{
    PyObject_HEAD
    TempObject *tmp1;
    int number;
} TempObject2;

void TempDealloc2(TempObject2 *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}

PyObject* TempNew2(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    TempObject2 *self;
    self = (TempObject2*) type->tp_alloc(type, 0);
    if (self)
    {
        self->number = 2;
    }

    return (PyObject*)self;
}

int TempInit2(TempObject2 *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"tmp1", "number", NULL};
    PyObject *tmp1 = NULL, *t;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist,
                                     &tmp1,
                                     &self->number))
        return -1;

    if (tmp1)
    {
        t = (PyObject *)self->tmp1;
        Py_INCREF(tmp1);
        self->tmp1 = (TempObject *)tmp1;
        Py_XDECREF(t);
    }


    return 0;
}

PyMemberDef TempMembers2[] =
{
    {"number", T_INT, offsetof(TempObject2, number), 0, "temp2 number"},
    {"tmp1",   T_INT, offsetof(TempObject2, tmp1),   0, "temp2 tmp1"},
    {NULL}
};

PyObject* TempName2(TempObject2 *self, PyObject *Py_UNUSED(ignored))
{
    return PyUnicode_FromFormat("Temp name");
}

PyObject* getTmp1(TempObject2 *self, PyObject *Py_UNUSED(ignored))
{
    return PyInitTemp();
}

PyMethodDef TempMethods2[] =
{
    {"name",     (PyCFunction) TempName2, METH_NOARGS,"return the name"},
    {"get_tmp1", (PyCFunction) getTmp1,   METH_NOARGS,"get tmp1"},
    {NULL}
};

PyTypeObject TempType2 =
{
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "TempM2.Temp2",
    .tp_basicsize = sizeof(TempObject2),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)&TempDealloc2,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "temp object",
    .tp_methods = TempMethods2,
    .tp_members = TempMembers2,
    .tp_init = (initproc)&TempInit2,
    .tp_new = (newfunc)&TempNew2,
};

PyModuleDef TempModule2 = 
{
    PyModuleDef_HEAD_INIT,
    .m_name = "TempM2",
    .m_doc = "Temp module",
    .m_size = -1,
};

PyMODINIT_FUNC PyInitTemp2()
{
    PyObject *m;
    if (PyType_Ready(&TempType2) < 0)
        return NULL;
    if (PyType_Ready(&TempType) < 0)
        return NULL;
    if (PyType_Ready(&TempListType) < 0)
        return NULL;

    m = PyModule_Create(&TempModule2);
    if (!m)
        return NULL;


    Py_INCREF(&TempType2);
    Py_INCREF(&TempType);
    PyModule_AddObject(m, "tmp2", (PyObject *)&TempType2);
    PyModule_AddObject(m, "tmp1", (PyObject *)&TempType);
    PyModule_AddObject(m, "tmplist", (PyObject *)&TempListType);

    return m;
}

void fetch_error()
{
    PyObject *type = NULL, *value = NULL, *traceback = NULL;
     
    PyErr_Fetch(&type, &value, &traceback);
     
    if (type)
    {
        std::cout << PyExceptionClass_Name(type) << ": ";
    }
     
    if (value)
    {
        PyObject *line = PyObject_Str(value);
        if (line && (PyUnicode_Check(line)))
            std::cout << PyUnicode_1BYTE_DATA(line);
    }
     
    std::cout << std::endl;
     
    if (traceback)
    {
        for (PyTracebackObject *tb = (PyTracebackObject *)traceback;
             NULL != tb;
             tb = tb->tb_next)
        {
            PyObject *line = PyUnicode_FromFormat("  File \"%U\", line %d, in %U\n",
                                                  tb->tb_frame->f_code->co_filename,
                                                  tb->tb_lineno,
                                                  tb->tb_frame->f_code->co_name);
            std::cout<< PyUnicode_1BYTE_DATA(line)<<std::endl;
        }
    }
}

unsigned long tid = 0;

void interrupt()
{
    sleep(5);
    printf("--%lu\n", tid);
    //PyGILState_STATE state = PyGILState_Ensure();
    //PyThreadState_SetAsyncExc(tid, PyExc_KeyboardInterrupt);
    //PyErr_SetObject(PyExc_KeyboardInterrupt, NULL);
    //PyErr_SetObject(PyExc_RuntimeError, NULL);
    //PyErr_SetObject(PyExc_SystemExit, NULL);
    //PyErr_SetObject(PyExc_BlockingIOError, NULL);
    //PyErr_SetObject(PyExc_InterruptedError, NULL);
    //PyErr_SetObject(PyExc_IOError, NULL);
    //PyGILState_Release(state);
    PyErr_SetInterrupt();
}

void running()
{
    tid = PyThread_get_thread_ident();
    printf("--%lu\n", tid);
    PyObject *pMHey = PyImport_ImportModule("Hey");
    PyObject *pFHey = PyObject_GetAttrString(pMHey, "HeyWorld");
    PyObject *pRet = PyObject_CallObject(pFHey, NULL);
}

int main()
{
    for(int i = 0; i < 10; i ++)
    {
        Temp *t = new Temp(i);
        tlist.push_back(t);
    }

    tid = PyThread_get_thread_ident();
    //PyImport_AppendInittab("TempM", &PyInitTemp);
    PyImport_AppendInittab("TempM2", &PyInitTemp2);
    Py_Initialize();

    thread *t = new thread(interrupt);

    thread *ts[10];
    for(int i = 0; i < 1; i ++)
    {
        ts[i] = new thread(running);
        //running();
    }

    t->join();

    for(int i = 0; i < 1; i ++)
    {
        ts[i]->join();
    }

#if 0
    //PyErr_Print();
    PyObject *pMHey = PyImport_ImportModule("Hey");
    PyObject *pFHey = PyObject_GetAttrString(pMHey, "HeyWorld");
    PyObject *pRet = PyObject_CallObject(pFHey, NULL);
    //PyErr_Print();

    PyObject *pMSD = PyImport_ImportModule("SD");
    PyObject *pFS  = PyObject_GetAttrString(pMSD, "v_init");
    PyObject *pFD  = PyObject_GetAttrString(pMSD, "v_use");
    PyObject *tstr = PyObject_CallObject(pFS, NULL);
    char *buffer;
    Py_ssize_t  length;
    PyBytes_AsStringAndSize(tstr, &buffer, &length);

    //char *s = (char*)malloc(length+1);
    //memcpy(s, buffer, length);
    //pRet = PyObject_CallObject(pFD, Py_BuildValue("(y#)", s, length));

    string s;
    s.assign(buffer, length);
    pRet = PyObject_CallObject(pFD, Py_BuildValue("(y#)", s.c_str(), s.length()));

    fetch_error();

#if 0
    PyObject *pMCommon = PyImport_ImportModule("Common");
    PyObject *PCCommon = PyObject_GetAttrString(pMCommon, "CommonData");
    PyObject *pFFunc = PyObject_GetAttrString(pMHey, "Func");
    pRet = PyObject_CallObject(pFFunc, Py_BuildValue("(O)", PCCommon));

    PyObject *PCDict = PyObject_GetAttrString(pMCommon, "Dict");
    PyDict_SetItem(PCDict, PyUnicode_FromFormat("tmp1"), Py_BuildValue("ii", 2019, 10));
    pFFunc = PyObject_GetAttrString(pMHey, "TestDict");
    pRet = PyObject_CallObject(pFFunc, Py_BuildValue("(O)", PCDict));
#endif

#endif
    Py_Finalize();
    return 0;
}
