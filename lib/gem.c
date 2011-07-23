
/* Need to define an internal flag to avoid an extern */
#define LDG_INTERNAL

#include "ldg_Python.h"

/* --- Python-C API Calls --- */
//static 

#include <gem.h>
#include <ldg.h>

#include "py_aes.h"
#include "py_vdi.h"

/* --- A GEM exception --- */
 

/* --- Python API Bookkeeping --- */
static PyMethodDef 
GemMethods[] = {
    /* AES Application Library */
    {"appl_init", py_appl_init, METH_VARARGS, "Initialize a GEM application"},
    {"appl_exit", py_appl_exit, METH_VARARGS, "Exit a GEM application"},
    {"appl_write", py_appl_write, METH_VARARGS, "Send a message to a GEM application"},
    {"appl_read", py_appl_read, METH_VARARGS, "Retrieve message data from a GEM application"},
    
    /* AES Forms Library */
    {"form_alert", py_form_alert, METH_VARARGS, "Display a GEM alert dialog"},
    {"form_dial", py_form_dial, METH_VARARGS, "Reserves and releases screen memory"},
    {"form_do", py_form_do, METH_VARARGS, "Processes a dialog"},
    {"form_center", py_form_center, METH_VARARGS, "Centers an object"},
    
    /* AES Graphics Library */
    {"graf_handle", py_graf_handle, METH_NOARGS, "Return a handle to the VDI"},
    {"graf_mouse", py_graf_mouse, METH_VARARGS, "Sets the mouse pointer"},
    
    /* AES Resource Library */
    {"rsrc_load", py_rsrc_load, METH_VARARGS, "Load a resource into memory"},
    {"rsrc_gaddr", py_rsrc_gaddr, METH_VARARGS, "Return an encapsulated memory address of a resource component"},
    
    /* AES Window Library */
    {"wind_create", py_wind_create, METH_VARARGS, "Create a window"},
    {"wind_open", py_wind_open, METH_VARARGS, "Open a window"},
    {"wind_get", py_wind_get, METH_VARARGS, "Retrieve window information"},
    {"wind_delete", py_wind_delete, METH_VARARGS, "Delete a window (after closing...)"},
    {"wind_close", py_wind_close, METH_VARARGS, "Close a window"},
    {"wind_set", py_wind_set, METH_VARARGS, "Set a window parameter"},
    {"wind_set_string", py_wind_set_string, METH_VARARGS, "Set a string window parameter"},
    {"wind_update", py_wind_update, METH_VARARGS, "Lock window redraw for updates"},
    
    {"evnt_multi", py_evnt_multi, METH_VARARGS | METH_KEYWORDS, "Process multiple GEM events."},

    /* VDI Functions */
    {"v_open_screen", py_v_open_screen, METH_NOARGS, "Open and retrieve a handle to a virtual screen workstation"},
    {"v_clsvwk", py_v_clsvwk, METH_VARARGS, "Close a virtual workstation"},
    {"v_bar", py_v_bar, METH_VARARGS, "Draw a filled rectangle"},
    {"v_ellipse", py_v_ellipse, METH_VARARGS, "Draw an ellipse"},
    {"vsf_color", py_vsf_color, METH_VARARGS, "Select the fill color index"},
    {"vs_clip", py_vs_clip, METH_VARARGS, "Set VDI clipping region"},
    
    {NULL,NULL,0,NULL}
};   
 
PyMODINIT_FUNC __CDECL init_gem(void)
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
        "init_gem", "Internal\n", init_gem,
        
        /* AES Application Library */
        "py_appl_exit", "Internal\n", py_appl_exit,
        "py_appl_init", "Internal\n", py_appl_init,
        "py_appl_write", "Internal\n", py_appl_write,
        "py_appl_read", "Internal\n", py_appl_read,
        
        /* AES Forms Library */
        "py_form_alert", "Internal\n", py_form_alert,
        "py_form_dial", "Internal\n", py_form_dial,
        "py_form_do", "Internal\n", py_form_do,
        "py_form_center", "Internal\n", py_form_center,
        
        /* AES Graphics Library */
        "py_graf_handle", "Internal\n", py_graf_handle,
        "py_graf_mouse", "Internal\n", py_graf_mouse,
        
        /* AES Resource Library */
        "py_rsrc_load", "Internal\n", py_rsrc_load,
        "py_rsrc_gaddr", "Internal\n", py_rsrc_gaddr,
        
        /* AES Window Library */
        "py_wind_create", "Internal\n", py_wind_create,
        "py_wind_open", "Internal\n", py_wind_open,
        "py_wind_get", "Internal\n", py_wind_get,
        "py_wind_delete", "Internal\n", py_wind_delete,
        "py_wind_close", "Internal\n", py_wind_close,
        "py_wind_update", "Internal\n", py_wind_update,
        "py_wind_set", "Internal\n", py_wind_set,
        "py_wind_set_string", "Internal\n", py_wind_set_string,
        
        /* AES Event Library */
        "py_evnt_multi", "Internal\n", py_evnt_multi,
        
        /* VDI Functions */
        "py_v_open_screen", "Internal\n", py_v_open_screen,
        "py_v_clsvwk", "Internal\n", py_v_clsvwk,
        "py_v_bar", "Internal\n", py_v_bar,
        "py_v_ellipse", "Internal\n", py_v_ellipse,
        "py_vsf_color", "Internal\n", py_vsf_color,
        "py_vs_clip", "Internal\n", py_vs_clip,
        
        NULL,NULL,NULL
};

LDGLIB LibLdg[] = {
        0x0001, 29, LibFunc, "GEM Extensions for Python", 0
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

 