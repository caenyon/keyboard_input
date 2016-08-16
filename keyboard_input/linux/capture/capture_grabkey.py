# coding=utf-8
"""
This program uses python-xlibs grab_key method (equal Xlibs XGrabKey) to capture key events emitted by a single key.
"""

import signal
import sys
from Xlib.display import Display
from Xlib import X

# open connection to the x-server
display = Display()

# select root window
root = display.screen().root

# change root window attributes so that it gets notified when key press or key release events occur.
root.change_attributes(event_mask=X.KeyPressMask | X.KeyReleaseMask)

# terminate the program after 10 seconds to prevent freezing. This is useful if you want to modify
# this example without the risk of freezing your whole system permanently.
signal.signal(signal.SIGALRM, lambda a, b: sys.exit(1))
signal.alarm(10)

# grab the 'x' key (key code 53)
root.grab_key(53, 0, True, X.GrabModeSync, X.GrabModeSync)

while 1:

    # get the next event from the input queue. If the queue is empty, this call blocks until
    # there's an event
    event = display.next_event()

    # handle event
    print("pressed" if event.type == 2 else "released")

    # tell the x server that we 'consumed' the event. This call is required because we won't get
    # other events otherwise
    display.allow_events(X.AsyncKeyboard, X.CurrentTime)

