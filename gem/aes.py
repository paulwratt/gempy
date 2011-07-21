import _gem

from error import GEMError
from constants import *

def alert(message,type=None,buttons=('Ok',),default=None):
    """Displays a generic GEM alert box with the specified
    message.  The type of box may also be specified as one
    of ('none', 'exclamation', 'question', 'stop', 'info',
    'disk', 'bomb').  The buttons parameter can contain a 
    tuple or list of button texts (up to 3, as limited by
    GEM."""
    
    alert_types = ['none', 'exclamation', 'question',
                   'stop', 'info', 'disk', 'bomb']
    try:
        internal_type = alert_type.index(type.lower())
    except ValueError:
        raise GEMError('Unknown alert box type')
    except AttributeError:
        if type is None:
            internal_type = 0
        else:
            internal_type = type
    
    if default is None:
        default = 0
    elif type(default) is str:
        try:
            default = buttons.index(default)
        except ValueError:
            raise GEMError('Could not locate default button')
    
    bstring = ''
    if len(buttons) > 3:
        buttons = buttons[0:3]
    for button in buttons:
        if len(button) > 10:
            button = button[0:10]
        bstring = bstring + button + '|'
    bstring = bstring[:-1]
    
    astring = "[{0}][{1}][{2}]".format(repr(internal_type),
                                       message, bstring)
    
    return _gem.form_alert(default, astring)
    
def window_update(action):
    """Issues a 'wind_update()' call to the AES with the specified
    argument.  The action argument must be END_UPDATE, BEG_UPDATE,
    END_MCTRL, or BEG_MCTRL."""
    _gem.wind_update(action)
    
class Window:
    """A class wrapping GEM windows and their functionality"""
    
    def __init__(self, type=NAME|FULLER|CLOSER|SIZER):
        """Creates (but does not show) a window"""
        self.id = _gem.wind_create(type,(0,0,10,10))
    
    def open(self,rect):
        """Opens a window using the the specified rectangle (x,y,w,h)"""
        _gem.wind_open(self.id, rect)
        
    def close(self):
        """Closes (but does not destroy) a window"""
        _gem.wind_close(self.id)
        
    def destroy(self):
        """Deletes an existing GEM window"""
        _gem.wind_delete(self.id)
        
    def set_name(self,name):
        """Sets the name of a window"""
        _gem.wind_set(self.id,WF_NAME,name)
        
    def begin_update(self):
        window_update(BEG_UPDATE)
    
    def end_update(self):
        window_update(END_UPDATE)

class Event:
    def __init__(self):
        pass
        
    def process(self):
        pass
        
class MouseButtonEvent(Event):
    """A base mouse button event class"""
    def __init__(self, clicks=1, mask=MB_LEFT, state=0):
        Event.__init__(self)
        self.clicks = clicks
        self.mask = mask
        self.requested_state = state
        
        self.returned_button = None
        self.returned_state = None
        self.returned_clicks = None
        self.position = None
        
class MouseMovementEvent(Event):
    def __init__(self):
        Event.__init__(self)
        raise RuntimeError("Not yet implemented")
        
class TimerEvent(Event):
    def __init__(self, length=1000):
        Event.__init__(self)
        self.length = length
        
class KeyboardEvent(Event):
    def __init__(self):
        Event.__init__(self)
        
        self.keycode = None

class MessageEvent(Event):
    def __init__(self):
        Event.__init__(self)

        self.message = None

class Application:

    def __init__(self):
        """Initializes the GEM application"""
        self.id = _gem.appl_init()
        if self.id == -1:
            raise GEMError("The application failed to initialize")
        
        self.windows = []
        self.resource = False
        
        self.message_event = None
        self.button_event = None
        self.keyboard_event = None
        self.mouse_event = None
        self.timer_event = None
        
        self.event_processing = False
        
    def destroy(self):
        """Destroys the application"""
        _gem.appl_exit(self.id)
        
    def load_resource(self,file):
        """Loads a resource file into the application."""
        try:
            _gem.rsrc_load(file)
            self.resource = True
        except:
            self.resource = False
            raise GEMError("Could not load the resource file {0}".format(file))
        
    def get_resource_address(self,type,index):
        """Retrieves the address of a resource element in a Python capsule.
        The returned object should never be directly modified."""
        if not self.resource:
            raise GEMError("A resource has not yet be loaded")
            
        return _gem.rsrc.gaddr(type,index)
        
    def event_loop(self):
        """Executes the GEM event loop, watching for events specified
        by the event attributes of the Application object."""
        
        self.event_processing = True
        while self.event_processing:
            
            events = 0
            kwdict = dict()
            if self.message_event is not None:
                events = events | MU_MESAG
                
            if self.button_event is not None:
                events = events | MU_BUTTON
                kwdict['mouse_buttons'] = (self.button_event.clicks, 
                                           self.button_event.mask, 
                                           self.button_event.state)
                
            if self.timer_event is not None:
                events = events | MU_TIMER
                kwdict['timer'] = self.timer_event.length
                
            if self.keyboard_event is not None:
                events = events | MU_KEYBD
                
            if self.mouse_event is not None:
                self.event_processing = False
                raise RuntimeError("Not yet implemented")
                events = events | MU_M1 | MU_M2 | MU_WHEEL | MU_MX
            
            if events == 0:
                self.event_processing = False
                raise GEMError("No event callbacks have been specified")
        
            ret = _gem.evnt_multi(events,**kwdict)
            
            if ret['events'] & MU_MESAG:
                self.message_event.message = ret['message']
                self.message_event.process()
                
            if ret['events'] & MU_BUTTON:
                self.button_event.position = ret['mouse_position']
                self.button_event.returned_button = ret['mouse_button'][0]
                self.button_event.returned_state = ret['mouse_button'][1]
                self.button_event.returned_clicks = ret['mouse_button'][2]
                self.button_event.process()
                
            if ret['events'] & MU_TIMER:
                self.timer_event.process()
                
            if ret['events'] & MU_KEYBD:
                self.keyboard_event.keycode = ret['key']
                self.keyboard_event.process()
                
            