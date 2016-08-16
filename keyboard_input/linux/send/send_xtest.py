# coding=utf-8
"""
This module contains a simple program that uses the python-xlib package to send key events to the
 x-server using the fake_event method (equal to XTestFakeKeyEvent in Xlib).

 Properties:
 - requires running x server and python-xlib package
 - no root required
 - key events sent with this method do NOT have the send_event attribute set to True. This means
   that a program receiving an event generated with this method cannot detect that this event has
   been injected.
"""

from Xlib.display import Display
from Xlib import X
from Xlib.ext.xtest import fake_input
from time import sleep


class XTestSendContext(object):

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
        Sends a key event to the focused window using python-xlibs fake_input method.

        :param key_code: Integer code of the key event that should be sent
        :param key_down: True = key press event, False = key release event
        """
        # select the right event type depending on key_down
        event_type = X.KeyPress if key_down else X.KeyRelease

        # fake keyboard event
        fake_input(self.display, event_type, key_code)

        # sync connection to ensure that the input is actually sent to the x server
        self.display.sync()

    def close(self):
        """
        Closes the connection to the x server
        """
        self.display.close()


if __name__ == '__main__':
    # create the context
    x = XTestSendContext()

    # sleep for 5 seconds
    sleep(5)

    # press and release key 53 ('x' character)
    x.send_key_event(53, key_down=True)
    x.send_key_event(53, key_down=False)

    # close connection
    x.close()
