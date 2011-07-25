from error import GEMError
from constants import *

import _gem

def get_screen_handle():
    """Returns a VDI handle for the current screen"""
    return _gem.v_open_screen()
    
def close(handle):
    """Closes the passed VDI handle"""
    _gem.v_clsvwk(handle)
    
    
# Drawing primitives
def bar(handle,pt1,pt2=None):
    """Draw a filled rectangle"""
    
    xpt1 = pt1
    if pt2 is None and len(pt1) == 4:
        xpt1 = (pt1[0],pt1[1])
        xpt2 = (pt1[0]+pt1[2],pt1[1]+pt1[3])
    elif len(pt2) == 2 and len(pt1) == 2:
        xpt2 = pt2
    else:
        raise ArgumentError('Points should be one (x,y,w,h) tuple or an (x,y) pair of tuples')

    _gem.v_bar(handle,xpt1,xpt2)
    
def ellipse(handle,center,radii):
    """Draw eclipse"""
    _gem.v_ellipse(handle,center,radii)
    
def vsf_color(handle,index):
    """Set the fill color index"""
    _gem.vsf_color(handle,index)
    
def vs_clip(handle, enable, pt1, pt2=None):
    """Set the clipping region"""
    xpt1 = pt1
    if pt2 is None and len(pt1) == 4:
        xpt1 = (pt1[0],pt1[1])
        xpt2 = (pt1[0]+pt1[2],pt1[1]+pt1[3])
    elif len(pt2) == 2 and len(pt1) == 2:
        xpt2 = pt2
    else:
        raise ArgumentError('Point should be one (x,y,w,h) tuple or an (x,y) pair of tuples')
    
    if enable:
        xenable = 1
    else:
        xenable = 0
        
    _gem.vs_clip(handle,xenable, xpt1, xpt2)
    