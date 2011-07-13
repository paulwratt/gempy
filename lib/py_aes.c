#include "ldg_Python.h"
#include <gem.h>

extern PyObject *GEMError;

/* --- Application Library --- */
static PyObject* __CDECL py_appl_init(PyObject *self, PyObject *args)
{
int ret;

    ret = appl_init();
    return Py_BuildValue("i",ret);
}

static PyObject* __CDECL py_appl_exit(PyObject *self, PyObject *args)
{
int ret;

    ret = appl_exit();
    return Py_BuildValue("i",ret);
}

static PyObject* __CDECL py_appl_write(PyObject *self, PyObject *args)
{
int ret;
int app_id;
char *message;
int msg_length;
    
    if(!PyArg_ParseTuple(args,"iiy*",&app_id,&msg_length,&message))
        return NULL;
    
    ret = appl_write(app_id,msg_length,message);
    return Py_BuildValue("i",ret);
}

/* --- Forms Library --- */
static PyObject* __CDECL py_form_alert(PyObject *self, PyObject *args)
{
char *text;
int x;
    
    if(!PyArg_ParseTuple(args,"is",&x,&text))
        return NULL;
        
    x = form_alert(x,text);
    return Py_BuildValue("i",x);
}

/* --- Resources Library --- */
static void __CDECL py_rsrc_load(PyObject *self, PyObject *args)
{
char *file;
int x;
    
    if(!PyArg_ParseTuple(args,"s",&file))
        return NULL;
        
    if(rsrc_load(file) == 0) {
        PyErr_SetString(GEMError,"Resource failed to load");
        return NULL;
    }
    return Py_BuildValue("i",x);
}

static PyObject* __CDECL py_rsrc_gaddr(PyObject *self, PyObject *args)
{
char *file;
int type, index;
void *gaddr;
    
    if(!PyArg_ParseTuple(args,"ii",&type,&index))
        return NULL;
        
    if(rsrc_gaddr(type,index,&gaddr) == 0) {
        PyErr_SetString(GEMError,"Resource item was not found");
        return NULL;
    }
    
    return PyCapsule_New(gaddr,NULL,NULL);
}
