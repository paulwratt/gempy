/* Dynamic Libraries for FreeMiNT (LDG) */

#include <Python.h>
#include "importdl.h"
#include <ldg.h>

#define PY_API_FCOUNT   3

const struct filedescr _PyImport_DynLoadFiletab[] = {
    {".ldg", "rb", C_EXTENSION},
    {"module.ldg", "rb", C_EXTENSION},
    {0, 0, 0}
};

//PyObject *Py_InitModule(char *name, PyMethodDef *methods);

dl_funcptr _PyImport_GetDynLoadFunc(const char *fqname, const char *shortname,
                                    const char *pathname, FILE *fp)
{
    dl_funcptr p;
    LDG *library;
    short aes_gl;
    char errBuf[256];
    
    char funcname[258];
    
    /* For assigning callbacks to the module */
    void (*assign_pycalls)(void *);
    void *callbacks[PY_API_FCOUNT];

    PyOS_snprintf(funcname, sizeof(funcname), "init%.200s", shortname);

    p = NULL;

    library = ldg_open(pathname, &aes_gl);

    /* Proceed on success */
    if(library != NULL) {
        
        /* Initialize the callbacks */
        assign_pycalls = ldg_find("assign_pycalls",library);
        if(assign_pycalls == NULL) { 
            PyOS_snprintf(errBuf, sizeof(errBuf),
                          "Could not find function assign_pycalls");
            PyErr_SetString(PyExc_ImportError, errBuf);
        } else {
            
            callbacks[0] = &Py_InitModule4;
            callbacks[1] = &PyArg_ParseTuple;
            callbacks[2] = &Py_BuildValue;
            callbacks[3] = &PyErr_NewException;
            callbacks[4] = &PyErr_SetString;
            callbacks[5] = &PyModule_AddObject;
            callbacks[6] = &PyCapsule_New;
            callbacks[7] = &PyCapsule_GetPointer;
            
            assign_pycalls(callbacks);
        
            p = (dl_funcptr)ldg_find(funcname,library);
            if(p == NULL) { 
                PyOS_snprintf(errBuf, sizeof(errBuf),
                              "Could not find function %s",funcname);
               PyErr_SetString(PyExc_ImportError, errBuf);
            }
        }   
         
    } else {
        PyOS_snprintf(errBuf, sizeof(errBuf),
                      "LDG load failed with error code %d",
                      ldg_error());
        PyErr_SetString(PyExc_ImportError, errBuf);
    }

    return p;
}