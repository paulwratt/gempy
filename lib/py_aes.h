#ifndef __PY_AES_HEADERS
#define __PY_AES_HEADERS

#include "ldg_Python.h"

static PyObject* __CDECL py_appl_init(PyObject *self, PyObject *args);

static PyObject* __CDECL py_appl_exit(PyObject *self, PyObject *args);

static PyObject* __CDECL py_appl_write(PyObject *self, PyObject *args)

static PyObject* __CDECL py_form_alert(PyObject *self, PyObject *args);


static void __CDECL py_rsrc_load(PyObject *self, PyObject *args);
static PyObject* __CDECL py_rsrc_gaddr(PyObject *self, PyObject *args);

static PyObject* __CDECL py_wind_create(PyObject *self, PyObject *args)
static PyObject* __CDECL py_wind_open(PyObject *self, PyObject *args);
static PyObject* __CDECL py_wind_get(PyObject *self, PyObject *args);
static PyObject* __CDECL py_wind_delete(PyObject *self, PyObject *args);
static PyObject* __CDECL py_wind_close(PyObject *self, PyObject *args);

#endif /* __PY_AES_HEADERS */
