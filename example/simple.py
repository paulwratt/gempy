import gem

class AppMessageEvent(gem.MessageEvent):
    def __init__(self,app):
        gem.MessageEvent.__init__(self)
        
        self.app = app
        self.window = app.windows[0]
        
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

def start_app():

    app = gem.Application()

    w = app.new_window((60,60,500,300),'Awesome!')
    
    app.message_event = AppMessageEvent(app)
    
    app.event_loop()
    
    app.destroy()
    

if __name__ == "__main__":
    start_app()