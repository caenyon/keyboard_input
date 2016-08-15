# coding=utf-8
import signal
import sys
from Xlib.ext import xinput
from Xlib.display import Display
from Xlib import X

display = Display()

root = display.screen().root

root.change_attributes(event_mask=X.KeyPressMask | X.KeyReleaseMask)

signal.signal(signal.SIGALRM, lambda a,b:sys.exit(1))
signal.alarm(10)


display.sync()
root.grab_key(10, 0, True, X.GrabModeSync, X.GrabModeSync)

while 1:
    event = display.next_event()
    display.allow_events(X.AsyncKeyboard, X.CurrentTime)
    print(event.type)

