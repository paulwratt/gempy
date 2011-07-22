import gem

class AppMessageEvent(gem.MessageEvent):
    def __init__(self,app):
        gem.MessageEvent.__init__(self)
        
        self.app = app
        self.window = app.windows[0]
        
    def process(self):
        
        # First call the super's process()
        gem.MessageEvent.process(self)
        
        if self.message == WM_CLOSED:
            app.event_processing = False

def start_app():

    app = gem.Application()
    
    w = app.new_window((60,60,500,300))
    
    app.message_event = AppMessageEvent(app)
    
    app.event_loop()
    
    app.destroy()
    

if __name__ == "__main__":
    start_app()