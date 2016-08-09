# coding=utf-8

from Xlib.display import Display
from Xlib import X
from Xlib.ext.xtest import fake_input


class XTestSendContext(object):

    def __init__(self):
        # open a connection to the x server
        self.display = Display()

        # get the root window of the default screen
        self.root = self.display.screen().root

    def send_key_event(self, key_code, key_down):
        # select the right event type depending on key_down
        event_type = X.KeyPress if key_down else X.KeyRelease

        # fake keyboard event
        fake_input(self.display, event_type, key_code)

        # sync connection to ensure that the input is actually sent to the x server
        self.display.sync()

    def close(self):
        # close the connection to the x server
        self.display.close()


if __name__ == '__main__':

    # create the context
    x = XTestSendContext()

    # press and release key 53 ('x' character)
    x.send_key_event(53, key_down=True)
    x.send_key_event(53, key_down=False)

    # close connection
    x.close()
