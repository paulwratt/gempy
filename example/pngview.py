import gem
import gem.vdi

import sys

import png

# Taken from resource headers
MENU = 0
M_ABOUT = 7
M_QUIT = 16
ABOUT = 1
B_ABOUT_OK = 1

def redraw(window,data):

    window.begin_update()
    vh = window.graphics_handle()
    
    rgbdata = data[2]
    
    wrect = window.get_work_rect()
    
    for r in window.get_invalid_rectangles():
        todraw = window.intersect_work_area(r)
        if todraw is not None:
            gem.vdi.vs_clip(vh, True, todraw)
            image_y = 0
            for r in rgbdata:
                image_x = 0
                
                pvalue = 0
                pcount = 0
                for c in r:
                
                    pvalue = pvalue + c
                    pcount = pcount + 1
                    
                    if pcount == 3:
                
                        pvalue = pvalue / 3
                
                        if c > pvalue:
                            gem.vdi.vsf_color(vh,0)
                        else:
                            gem.vdi.vsf_color(vh,1)
                        x = wrect[0] + image_x
                        y = wrect[1] + image_y
                        gem.vdi.bar(vh,(x,y,1,1))
                        image_x = image_x + 1
                        #if image_x > data[0]:
                        #    raise RuntimeError("Point {0} exceeds limit {1}".format(image_x,data[0]))
                        pcount = 0
                        pvalue = 0
                        
                image_y = image_y + 1
            
            gem.vdi.vs_clip(vh, False, todraw)

    window.end_update()

class AppMessageEvent(gem.MessageEvent):
    def __init__(self,app):
        gem.MessageEvent.__init__(self)
        
        self.app = app
        self.window = app.windows[0]
    
    def handle_menu(self, item, title=None):
        if item == M_QUIT:
            self.app.send_message((gem.WM_CLOSED, 0, 0, self.window.id))
            
        elif item == M_ABOUT:
            dlg = self.app.get_resource_address(gem.R_TREE,ABOUT)
            self.app.draw_tree(dlg,2)
            self.app.form_do(dlg)
        
        if title is not None:
            self.app.set_menu_state(title)
    
    def process(self):
        
        # First call the super's process()
        gem.MessageEvent.process(self)
        
        if self.message == gem.WM_CLOSED:
            self.app.event_processing = False
        
        elif self.message == gem.WM_TOPPED:
            self.window.top()
            
        elif self.message == gem.WM_MOVED or self.message == gem.WM_SIZED:
            rect = (self.get_word(4),self.get_word(5),self.get_word(6),self.get_word(7))
            self.window.resize(rect)
            
        elif self.message == gem.WM_REDRAW:
            redraw(self.window,self.app.data)
        
        # Menu handling
        elif self.message == gem.MN_SELECTED:
            self.handle_menu(self.get_word(4),title=self.get_word(3))

def start_app(filename):

    reader = png.Reader(filename)
    data = reader.asRGB8()

    app = gem.Application()
    app.load_resource("simple.rsc")
    app.set_menu(MENU)

    app.data = data

    w = app.new_window((0,10,data[0],data[1]),filename,
                       type=gem.NAME|gem.MOVER|gem.CLOSER)
    
    app.message_event = AppMessageEvent(app)
    
    app.event_loop()
    
    app.destroy()
    

if __name__ == "__main__":
    print("Simple PNG Viewer for GEM")
    if len(sys.argv) < 2:
        print("Usage: {0} <png filename>".format(sys.argv[0]))
    else:
        print("Now processing {0}".format(sys.argv[1]))
        start_app(sys.argv[1])