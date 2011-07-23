#include "ldg_Python.h"
#include <gem.h>

PyObject* __CDECL py_v_open_screen(PyObject *self, PyObject *args)
{
int i;
short work_in[16];
short work_out[57];

short vdi_handle;
    
    for(i=1;i<16;i++)
        work_in[i] = (short)0;  /* General Defaults */
        
    work_in[0] = (short)1; /* Current Resolution */
    work_in[10] = (short)2; /* Necessary for screen drawing */
    
    v_opnvwk(work_in, &vdi_handle, work_out);
    
    /* For now, ignore the work_out array */
    
    return Py_BuildValue("i",(int)vdi_handle);
}

PyObject* __CDECL py_v_clsvwk(PyObject *self, PyObject *args)
{
int handle;

    if(!PyArg_ParseTuple(args,"i",&handle))
        return NULL;
        
    v_clsvwk(handle);
    
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* __CDECL py_v_bar(PyObject *self, PyObject *args)
{
int handle;
int x1, y1, x2, y2;
short pxarray[4];

    if(!PyArg_ParseTuple(args,"i(ii)(ii)",&handle, &x1, &y1, &x2, &y2))
        return NULL;
        
    pxarray[0] = x1;
    pxarray[1] = y1;
    pxarray[2] = x2;
    pxarray[3] = y2;
    
    v_bar(handle,pxarray);
    
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* __CDECL py_v_ellipse(PyObject *self, PyObject *args)
{
int handle;
int x1, y1, xr, yr;

    if(!PyArg_ParseTuple(args,"i(ii)(ii)",&handle, &x1, &y1, &xr, &yr))
        return NULL;
    
    v_ellipse(handle,x1,y1,xr,yr);
    
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* __CDECL py_vsf_color(PyObject *self, PyObject *args)
{
int handle;
int index;

    if(!PyArg_ParseTuple(args,"ii",&handle, &index))
        return NULL;
    
    index = vsf_color(handle,index);
    
    return Py_BuildValue("i",index);
}

PyObject* __CDECL py_vs_clip(PyObject *self, PyObject *args)
{
int handle;
int x1, y1, x2, y2;
int enable;
short pxarray[4];

    if(!PyArg_ParseTuple(args,"ii(ii)(ii)",&handle, &enable, &x1, &y1, &x2, &y2))
        return NULL;
        
    pxarray[0] = (short)x1;
    pxarray[1] = (short)y1;
    pxarray[2] = (short)x2;
    pxarray[3] = (short)y2;
    
    vs_clip(handle,enable,pxarray);
    
    Py_INCREF(Py_None);
    return Py_None;
}
