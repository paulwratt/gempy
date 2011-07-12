
/* Need to define an internal flag to avoid an extern */
#define LDG_INTERNAL
#include "ldg_Python.h"

#include <gem.h>
#include <ldg.h>

#include "py_aes.h"

/* --- Python-C API Calls --- */
static void *pycallbacks[PY_API_FCOUNT];

/* --- Python API Bookkeeping --- */
static PyMethodDef 
GemMethods[] = {
    {"appl_init", py_appl_init, METH_VARARGS, "Initialize a GEM application"},
    {"appl_exit", py_appl_exit, METH_VARARGS, "Exit a GEM application"},
    {"form_alert", py_form_alert, METH_VARARGS, "Display a GEM alert dialog"},
    {NULL,NULL,0,NULL}
};   
 
PyMODINIT_FUNC __CDECL initgem(void)
{

    printf("Welcome to shared init.\nStandby...\n");
    //LPy_InitModule("gem",GemMethods,NULL,NULL);
    ldg_callback(pycallbacks[0],"gem",GemMethods,NULL,NULL);
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
        "py_form_alert", "Internal\n", py_form_alert,
        "py_appl_exit", "Internal\n", py_appl_exit,
        "py_appl_init", "Internal\n", py_appl_init
};

LDGLIB LibLdg[] = {
        0x0001, 5, LibFunc, "GEM Extensions for Python", 0
};

int main( void) 
{
        if( ldg_init( LibLdg) == -1) {
                printf("This program is a shared library.\n");
        }
        return 0;
}
/* --- End LDG Bookkeeping --- */

 