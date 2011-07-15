#include "ldg_Python.h"
#include <gem.h>
#include <macros.h>

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

static PyObject* __CDECL py_form_dial(PyObject *self, PyObject *args)
{
int id;
int lx, ly, lw, lh;
int bx, by, bw, bh;
int ret;
    
    if(!PyArg_ParseTuple(args,"i(iiii)(iiii)",&id,&lx,&ly,&lw,&lh,&bx,&by,&bw,&bh))
        return NULL;
    
    ret = form_dial(id, lx, ly, lw, lh, bx, by, bw, bh);
    
    if(ret == 0) {
        PyErr_SetString(GEMError,"Form dial call failed");
        return NULL;
    }
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* __CDECL py_form_do(PyObject *self, PyObject *args)
{
PyObject *obj;
int x;
int ret;
    
    if(!PyArg_ParseTuple(args,"Oi",&obj,&x))
        return NULL;
        
    ret = form_do(PyCapsule_GetPointer(obj),x);
    return Py_BuildValue("i",ret);
}

static PyObject* __CDECL py_form_center(PyObject *self, PyObject *args)
{
PyObject *obj;
int x,y,w,h;
int ret;
    
    if(!PyArg_ParseTuple(args,"O(iiii)",&obj,&x,&y,&w,&h))
        return NULL;
        
    form_center(PyCapsule_GetPointer(obj),x,y,w,h);
    
    Py_INCREF(Py_None);
    return Py_None;
}

/* --- Graphics Library --- */
static PyObject* __CDECL py_graf_handle(PyObject *self)
{
int wchar,hchar,wcell,hcell;
int ret;
    
    ret = graf_handle(&wchar, &hchar, &wcell, &hcell);
    return Py_BuildValue("i(iiii)",ret,wchar,hchar,wcell,hcell);
}

static PyObject* __CDECL py_graf_mouse(PyObject self, PyObject *args)
{
int mouse;

    if(!PyArg_ParseTuple(args,"i",&mouse))
        return NULL;

    if(mouse == USER_DEF) {
        PyErr_SetString(GEMError,"User-defined mouse pointers not currently supported");
        return NULL;
    }
    
    if(graf_mouse(mouse) == 0) {
        PyErr_SetString(GEMError,"Mouse cursor setting failed");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

/* --- Resources Library --- */
static PyObject* __CDECL py_rsrc_load(PyObject *self, PyObject *args)
{
char *file;
int x;
    
    if(!PyArg_ParseTuple(args,"s",&file))
        return NULL;
        
    if(rsrc_load(file) == 0) {
        PyErr_SetString(GEMError,"Resource failed to load");
        return NULL;
    }
    
    Py_INCREF(Py_None);
    return Py_None;
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

/* --- Windows Library --- */
static PyObject* __CDECL py_wind_create(PyObject *self, PyObject *args)
{
int type, x, y, w, h;
int ret;
    
    if(!PyArg_ParseTuple(args,"i(iiii)",&type,&x,&y,&w,&h))
        return NULL;
    
    return Py_BuildValue("i",wind_create(type,x,y,w,h));
}

static PyObject* __CDECL py_wind_close(PyObject *self, PyObject *args)
{
int id;
    
    if(!PyArg_ParseTuple(args,"i",&id))
        return NULL;
    
    if(wind_close(id) == 0) {
        PyErr_SetString(GEMError,"Window failed to close");
        return NULL;
    }
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* __CDECL py_wind_delete(PyObject *self, PyObject *args)
{
int id;
    
    if(!PyArg_ParseTuple(args,"i",&id))
        return NULL;
    
    if(wind_delete(id) == 0) {
        PyErr_SetString(GEMError,"Window was not deleted");
        return NULL;
    }
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* __CDECL py_wind_open(PyObject *self, PyObject *args)
{
int id, x, y, w, h;
int ret;
    
    if(!PyArg_ParseTuple(args,"i(iiii)",&id,&x,&y,&w,&h))
        return NULL;
        
    ret = wind_open(type,x,y,w,h);
    if(ret == 0) {
        PyErr_SetString(GEMError,"Window could not be opened");
        return NULL;
    }
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* __CDECL py_wind_get(PyObject *self, PyObject *args)
{
int id, gp;
int w1, w2, w3, w4;
int ret;
    
    if(!PyArg_ParseTuple(args,"ii",&id,&gp))
        return NULL;
        
    ret = wind_get(id,gp,&w1,&w2,&w3,&w4);
    if(ret == 0) {
        PyErr_SetString(GEMError,"Window request failed");
        return NULL;
    }
    
    switch(gp) {
    
        case WF_WORKXYWH:
        case WF_WINXCFG:
        case WF_WINX:
        case WF_WIDGETS:
        case WF_UNICONIFY:
        case WF_TOP:
        case WF_PREVXYWH:
        case WF_OWNER:
        case WF_NTOOLBAR:
        case WF_NEXTXYWH:
        case WF_MINXYWH:
        case WF_FULLXYWH:
        case WF_FTOOLBAR:
        case WF_FIRSTXYWH:
        case WF_DDELAY:
        case WF_CURRXYWH:
            return Py_BuildValue("(iiii)", w1, w2, w3, w4);
            break;
        case WF_DCOLOR:
        case WF_ICONIFY:
        case WF_NEWDESK:
            return Py_BuildValue("(iii)", w1, w2, w3);
            break;
        case WF_MENU:
        case WF_TOOLBAR:
        case WF_M_WINDLIST:
            return Py_BuildValue("(ii)", w1, w2);
            break;
        case XA:
            return Py_BuildValue("ii", ret, w1);
            break;
        case WF_BEVENT:
        case WF_BOTTOM:
        case WF_HSLIDE:
        case WF_HSLSIZE:
        case WF_KIND:
        case WF_M_OWNER:
        case WF_SHADE:
        case WF_VSLIDE:
        case WF_VSLSIZE:
        default:
            return Py_BuildValue("i", w1);
            break;
    }
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* __CDECL py_wind_update(PyObject *self, PyObject *args)
{
int op;
int ret;
    
    if(!PyArg_ParseTuple(args,"i",&op))
        return NULL;
    if(wind_update(op) == 0) {
        PyErr_SetString(GEMError,"Window update failed");
        return NULL;
    }
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* __CDECL py_wind_set(PyObject *self, PyObject *args)
{
int id, sp;
int w1, w2, w3, w4;
int ret;
PyObject *tple;
    
    if(!PyArg_ParseTuple(args,"ii|O",&id,&sp,&tpl))
        return NULL;
    
    w1 = 0; w2 = 0; w3 = 0; w4 = 0;
    
    switch(gp) {
        case WF_BEVENT:
        case WF_BOTTOMALL:
        case WF_HSLIDE:
        case WF_HSLSIZE:
        case WF_M_BACKDROP:
        case WF_SHADE:
        case WF_STACK:
        case WF_TOPALL:
        case WF_VSLIDE:
        case WF_VSLSIZE:
        case WF_WHEEL:
            PyArg_ParseTuple(tpl,"i",&w1);
            break;
        case WF_COLOR:
        case WF_INFO:
        case WF_MENU:
        case WF_NAME:
        case WF_OPTS:
            PyArg_ParseTuple(tpl,"ii",&w1,&w2);
            break;
        case WF_DCOLOR:
        case WF_NEWDESK:
            PyArg_ParseTuple(tpl,"iii",&w1,&w2,&w3);
            break;
        case WF_CURRXYWH:
        case WF_DDELAY:
        case WF_FULLXYWH:
        case WF_ICONIFY:
        case WF_PREVXYWH:
        case WF_UNICONIFYXYWH:
        case WF_WIDGETS:
        case WF_WINXCFG:
            PyArg_ParseTuple(tpl,"iiii",&w1,&w2,&w3,&w4);
            break;
    }
    
    ret = wind_set(id,gp,w1,w2,w3,w4);
    if(ret == 0) {
        PyErr_SetString(GEMError,"Window set failed");
        return NULL;
    }
    
    Py_INCREF(Py_None);
    return Py_None;
}


/* --- Event Library --- */
static PyObject* __CDECL py_evnt_multi(PyObject self, PyObject *args, PyObject *kwargs)
{
/* Because this is possibly the ugliest call ever created in the C
 * language, we'll use the same variable names as the docs use.
 */
int ev_mflags, ev_mbclicks, ev_mbmask, ev_mbstate, ev_mm1flags, ev_mm1x, ev_mm1y, ev_mm1width, ev_mm1height, ev_mm2flags;
int ev_mm2x, ev_mm2y, ev_mm2width, ev_mm2height, ev_mmgpbuff, ev_mtlocount, ev_mthicount, ev_mmox, ev_mmoy;
int ev_mmbutton, ev_mmokstate, ev_mkreturn, ev_mbreturn;

PyObject *mbuttons;
PyObject *mmovement;
long int timer;

static char *kwlist[] = {"mouse_buttons","mouse_movement","timer",NULL};

    mbuttons = NULL;
    mmoverment = NULL;
    timer = 0l;

    if(!PyArg_ParseTupleAndKeywords(args, keywds, "i|OOl", kwlist,
                                     &ev_mflags, &mbuttons, &mmovement, &timer))
        return NULL;

    /* Timer handling */
    ev_mtlocount = loword(timer);
    ev_mthicount = hiword(timer);

    /* Mouse button handling */
    if(mouse_buttons != NULL) {
        PyArg_ParseTuple(mbuttons,"iii",&ev_mbclicks,&ev_mbmask,&ev_mbstate);
    }
    
    /* Mouse movement handling */
    if(mouse_movement != NULL) {
        PyArg_ParseTuple(mmovement,"(iiiii)(iiiii)",&ev_mm1flags,&ev_mm1x,&ev_mm1y,&ev_mm1width,ev_mm1height,
                                                        &ev_mm2flags,&ev_mm2x,&ev_mm2y,&ev_mm2width,ev_mm2height);
    }

    /* More is still needed */
    ret = evnt_multi(ev_mflags, 
                     ev_mbclicks, 
                     ev_mbmask, 
                     ev_mbstate, 
                     ev_mm1flags, 
                     ev_mm1x, 
                     ev_mm1y, 
                     ev_mm1width, 
                     ev_mm1height, 
                     ev_mm2flags, 
                     ev_mm2x, 
                     ev_mm2y, 
                     ev_mm2width, 
                     ev_mm2height, 
                     &ev_mmgpbuff, 
                     ev_mtlocount, 
                     ev_mthicount, 
                     &ev_mmox, 
                     &ev_mmoy, 
                     &ev_mmbutton, 
                     &ev_mmokstate, 
                     &ev_mkreturn, 
                     &ev_mbreturn);
    
    return Py_BuildValue("{s:i,s:i,s:(ii),s:(iii),s:i", "events", ret, "message", ev_mmgpbuff, 
        "mouse_position", ev_mmox, ev_mmoy, "mouse_button", ev_mmbutton, ev_mmokstate, ev_mbreturn
        "key", ev_mkreturn);
}

