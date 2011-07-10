#include <Python.h>
#include <gem.h>
#include <ldg.h>

#define PY_API_FCOUNT   3
static void *pycallbacks[PY_API_FCOUNT];

#define Py_InitModule(name,methods)     ldg_callback(pycallbacks[0],name,methods,NULL,NULL)
#define PyArg_ParseTuple(tpl,...)       ldg_callback(pycallbacks[1],tpl,##__VA_ARGS__)
#define Py_BuildValue(fmt,...)          ldg_callback(pycallbacks[2],fmt,##__VA_ARGS__)

//PyObject* (*LPy_InitModule)(char *, PyMethodDef *, char *, PyObject *) = NULL;


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

static PyObject* __CDECL py_form_alert(PyObject *self, PyObject *args)
{
char *text;
int x;
    
    if(!PyArg_ParseTuple(args,"is",&x,&text))
        return NULL;
        
    x = form_alert(x,text);
    return Py_BuildValue("i",x);
}

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

int main( void) {
        if( ldg_init( LibLdg) == -1) {
                printf("This program is a shared library.\n");
        }
        return 0;
}


 