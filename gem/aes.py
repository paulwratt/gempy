import _gem

from error import GEMError

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
    
class Window:
    def __init__(self, type):
    
        self.id = _gem.wind_create(type,(0,0,10,10))


class Application:

    def __init__(self):
        self.id = _gem.appl_init()
        if self.id == -1:
            raise GEMError("The application failed to initialize")
        
        self.windows = []
        
    def destroy(self):
        _gem.appl_exit(self.id)
        