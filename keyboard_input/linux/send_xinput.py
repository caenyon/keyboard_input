# coding=utf-8

from Xlib.display import Display
from Xlib.protocol.event import KeyPress, KeyRelease
from Xlib import X


class XInputSendContext(object):

    def __init__(self):
        # open a connection to the x server
        self.display = Display()

        # get the root window of the default screen
        self.root = self.display.screen().root

    def send_key_event(self, key_code, key_down):
        # get the window that has the input focus
        focus_window = self.display.get_input_focus().focus

        # select the right event class depending on key_down
        event_class = KeyPress if key_down else KeyRelease

        # create event
        event = event_class(time=X.CurrentTime, root=self.root, window=focus_window, same_screen=0, child=0, root_x=0,
                            root_y=0, event_x=0, event_y=0, state=0, detail=key_code)

        # send event to the window that has the input focus
        focus_window.send_event(event)

    def close(self):
        # close the connection to the x server
        self.display.close()


if __name__ == '__main__':

    # create the context
    x = XInputSendContext()

    # press and release key 53 ('x' character)
    x.send_key_event(53, key_down=True)
    x.send_key_event(53, key_down=False)

    # close connection
    x.close()
