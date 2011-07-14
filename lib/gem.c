
/* Need to define an internal flag to avoid an extern */
#define LDG_INTERNAL
#include "ldg_Python.h"

#include <gem.h>
#include <ldg.h>

#include "py_aes.h"

/* --- A GEM exception --- */
static PyObject *GEMError;

/* --- Python-C API Calls --- */
static void *pycallbacks[PY_API_FCOUNT];

/* --- Python API Bookkeeping --- */
static PyMethodDef 
GemMethods[] = {
    /* AES Application Library */
    {"appl_init", py_appl_init, METH_VARARGS, "Initialize a GEM application"},
    {"appl_exit", py_appl_exit, METH_VARARGS, "Exit a GEM application"},
    {"appl_write", py_appl_write, METH_VARARGS, "Send a message to a GEM application"},
    
    /* AES Forms Library */
    {"form_alert", py_form_alert, METH_VARARGS, "Display a GEM alert dialog"},
    
    /* AES Resource Library */
    {"rsrc_load", py_rsrc_load, METH_VARARGS, "Load a resource into memory"},
    {"rsrc_gaddr", py_rsrc_gaddr, METH_VARARGS, "Return an encapsulated memory address of a resource component"},
    
    /* AES Window Library */
    {"wind_create", py_wind_create, METH_VARARGS, "Create a window"},
    {"wind_open", py_wind_open, METH_VARARGS, "Open a window"},
    {"wind_get", py_wind_get, METH_VARARGS, "Retrieve window information"},
    {"wind_delete", py_wind_delete, METH_VARARGS, "Delete a window (after closing...)"},
    {"wind_close", py_wind_close, METH_VARARGS, "Close a window"},
    
    {NULL,NULL,0,NULL}
};   
 
PyMODINIT_FUNC __CDECL initgem(void)
{
PyObject *m;

    //printf("Welcome to shared init.\nStandby...\n");
    //LPy_InitModule("gem",GemMethods,NULL,NULL);
    
    m = Py_InitModule("_gem",GemMethods);
    
    GEMError = PyErr_NewException("_gem.error",NULL,NULL);
    Py_INCREF(GEMError);
    PyModule_AddObject(m,"error",GEMError);
    
    return;
}
/* --- End Python API Bookkeeping --- */


/* --- LDG Bookkeeping --- */
void __CDECL assign_pycalls(void **calls)
{
int i;

    for(i=0;i<PY_API_FCOUNT;i++) 
        pycallbacks[i] = calls[i];
}

PROC LibFunc[] = {
        "assign_pycalls", "Assigns Python callbacks", assign_pycalls,
        "initgem", "Internal\n", initgem,
        
        /* AES Application Library */
        "py_appl_exit", "Internal\n", py_appl_exit,
        "py_appl_init", "Internal\n", py_appl_init,
        "py_appl_write", "Internal\n", py_appl_write,
        
        /* AES Forms Library */
        "py_form_alert", "Internal\n", py_form_alert,
        
        /* AES Resource Library */
        "py_rsrc_load", "Internal\n", py_rsrc_load,
        "py_rsrc_gaddr", "Internal\n", py_rsrc_gaddr,
        
        /* AES Window Library */
        "py_wind_create", "Internal\n", py_wind_create,
        "py_wind_open", "Internal\n", py_wind_open,
        "py_wind_get", "Internal\n", py_wind_get,
        "py_wind_delete", "Internal\n", py_wind_delete,
        "py_wind_close", "Internal\n", py_wind_close
};

LDGLIB LibLdg[] = {
        0x0001, 13, LibFunc, "GEM Extensions for Python", 0
};

int main( void) 
{
        if( ldg_init( LibLdg) == -1) {
                printf("*** %s ***\n",LibLdg[0].infos);
                printf("This program is a shared library.\n");
        }
        return 0;
}
/* --- End LDG Bookkeeping --- */

 