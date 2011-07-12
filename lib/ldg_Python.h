#ifndef __LDG_PYTHON_HEADERS
#define __LDG_PYTHON_HEADERS

#include <Python.h>

#define PY_API_FCOUNT   3

#ifndef LDG_INTERNAL
extern void *pycallbacks[PY_API_FCOUNT];
#endif

#define Py_InitModule(name,methods)     ldg_callback(pycallbacks[0],name,methods,NULL,NULL)
#define PyArg_ParseTuple(tpl,...)       ldg_callback(pycallbacks[1],tpl,##__VA_ARGS__)
#define Py_BuildValue(fmt,...)          ldg_callback(pycallbacks[2],fmt,##__VA_ARGS__)

#endif /*__LDG_PYTHON_HEADERS */