#ifndef __LDG_PYTHON_HEADERS
#define __LDG_PYTHON_HEADERS

#include <Python.h>
#include <ldg.h>

#define PY_API_FCOUNT   12

#ifndef LDG_INTERNAL
extern void *pycallbacks[PY_API_FCOUNT];
extern PyObject *GEMError;
#else
void *pycallbacks[PY_API_FCOUNT];
PyObject *GEMError;
#endif

#define Py_InitModule(name,methods)     ldg_callback(pycallbacks[0],name,methods,NULL,NULL)
#define PyArg_ParseTuple(tpl,...)       ldg_callback(pycallbacks[1],tpl,##__VA_ARGS__)
#define Py_BuildValue(fmt,...)          ((PyObject *)ldg_callback(pycallbacks[2],fmt,##__VA_ARGS__))
#define PyErr_NewException(obj,pt1,pt2) ldg_callback(pycallbacks[3],obj,pt1,pt2)
#define PyErr_SetString(obj,s)          ldg_callback(pycallbacks[4],obj,s)
#define PyModule_AddObject(m,s,o)       ldg_callback(pycallbacks[5],m,s,o)
#define PyCapsule_New(pt,s,de)          ((PyObject *)ldg_callback(pycallbacks[6],pt,s,de))
#define PyCapsule_GetPointer(c,s)       ((void *)ldg_callback(pycallbacks[7],c,s))
#define Py_IncRef(obj)                  ldg_callback(pycallbacks[8],obj)
#define Py_DecRef(obj)                  ldg_callback(pycallbacks[9],obj)
#define Py_None                         ((PyObject *)pycallbacks[10])
#define PyArg_ParseTupleAndKeywords(tpl,...)     ldg_callback(pycallbacks[11],tpl,##__VA_ARGS__)

#define Py_INCREF(obj)                  ldg_callback(pycallbacks[8],obj)
#define Py_DECREF(obj)                  ldg_callback(pycallbacks[9],obj)

#endif /*__LDG_PYTHON_HEADERS */