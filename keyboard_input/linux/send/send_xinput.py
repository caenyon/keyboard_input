# coding=utf-8
"""
This module contains a simple program that uses the python-xlib package to send key events to the
 x-server using the send_event method (equal to XSendEvent in Xlib).

 Properties:
 - requires running x server and python-xlib package
 - no root required

 ATTENTION:
 Key events sent with this method will have the send_event attribute set to True. Some
 applications might ignore input sent with this method because of that flag.

 An alternative is to use the fake_input (Xlib: XTestFakeKeyEvent) from XTest extension package.
 See send_xtest.py for an example using fake_input.
"""

from Xlib.display import Display
from Xlib.protocol.event import KeyPress, KeyRelease
from Xlib import X
from time import sleep


class XInputSendContext(object):

    """
    This class manages a connection to the X-Server and allows to send key events.
    """

    def __init__(self):
        # open a connection to the x server
        self.display = Display()

        # get the root window of the default screen
        self.root = self.display.screen().root

    def send_key_event(self, key_code, key_down):
        """
        Sends a key event to the focused window using python-xlibs send_input method.

        :param key_code: Integer code of the key event that should be sent
        :param key_down: True = key press event, False = key release event
        """
        # get the window that has the input focus
        focus_window = self.display.get_input_focus().focus

        # select the right event class depending on key_down
        event_class = KeyPress if key_down else KeyRelease

        # create event
        event = event_class(time=X.CurrentTime, root=self.root, window=focus_window,
                            same_screen=0, child=0, root_x=0, root_y=0, event_x=0, event_y=0,
                            state=0, detail=key_code)

        # send event to the window that has the input focus
        focus_window.send_event(event)

    def close(self):
        """
        Closes the connection to the x server
        """
        self.display.close()


if __name__ == '__main__':

    # create the context
    x = XInputSendContext()

    # sleep for 5 seconds
    sleep(5)

    # press and release key 53 ('x' character)
    x.send_key_event(53, key_down=True)
    x.send_key_event(53, key_down=False)

    # close connection
    x.close()
