#ifndef __PY_VDI_HEADERS
#define __PY_VDI_HEADERS

#include "ldg_Python.h"

PyObject* __CDECL py_v_open_screen(PyObject *self, PyObject *args);
PyObject* __CDECL py_v_clsvwk(PyObject *self, PyObject *args);
PyObject* __CDECL py_v_bar(PyObject *self, PyObject *args);
PyObject* __CDECL py_v_ellipse(PyObject *self, PyObject *args);
PyObject* __CDECL py_vsf_color(PyObject *self, PyObject *args);
PyObject* __CDECL py_vs_clip(PyObject *self, PyObject *args);

#endif /* __PY_VDI_HEADERS */
