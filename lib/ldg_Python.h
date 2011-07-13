#ifndef __LDG_PYTHON_HEADERS
#define __LDG_PYTHON_HEADERS

#include <Python.h>
#include <ldg.h>

#define PY_API_FCOUNT   8

#ifndef LDG_INTERNAL
extern void *pycallbacks[PY_API_FCOUNT];
#endif

#ifdef Py_REF_DEBUG
#error Cannot build LDG Python exceptions with reference debugging
#endif

#define Py_InitModule(name,methods)     ldg_callback(pycallbacks[0],name,methods,NULL,NULL)
#define PyArg_ParseTuple(tpl,...)       ldg_callback(pycallbacks[1],tpl,##__VA_ARGS__)
#define Py_BuildValue(fmt,...)          ldg_callback(pycallbacks[2],fmt,##__VA_ARGS__)
#define PyErr_NewException(obj,pt1,pt2) ldg_callback(pycallbacks[3],obj,pt1,pt2)
#define PyErr_SetString(obj,s)          ldg_callback(pycallbacks[4],obj,s)
#define PyModule_AddObject(m,s,o)       ldg_callback(pycallbacks[5],m,s,o)
#define PyCapsule_New(pt,s,de)          ldg_callback(pycallbacks[6],pt,s,de)
#define PyCapsule_GetPointer(c,s)       ldg_callback(pycallbacks[7],c.s)
//#define Py_INCREF(obj)                  ldg_callback(pycallbacks[4],obj)

#endif /*__LDG_PYTHON_HEADERS */