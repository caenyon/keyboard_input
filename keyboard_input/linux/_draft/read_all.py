# coding=utf-8
import signal
from Xlib.display import Display
from Xlib import X

display = Display()

root = display.screen().root

counter = 0

def swallow_keystroke(event):
    print("s")
    display.allow_events(X.AsyncKeyboard, event.time)


def passthru_keystroke(event):
    print("p")

    display.allow_events(X.ReplayKeyboard, event.time)
    display.flush()

root.grab_key(15, 0, True, X.GrabModeSync, X.GrabModeSync)
root.grab_key(10, 0, True, X.GrabModeSync, X.GrabModeSync)

signal.alarm(10)

while True:
    print("event...")
    event = display.next_event()
    print(event.type, event.detail, event.time)
    if event.type == X.KeyPress and event.detail == 10:
        print("pressed")
        if not counter % 2:
            swallow_keystroke(event)
        else:
            passthru_keystroke(event)
    elif event.type == X.KeyRelease and event.detail == 10:
        print("released")
        if not counter % 2:
            swallow_keystroke(event)
        else:
            passthru_keystroke(event)
        counter += 1

    if event.type == X.KeyPress and event.detail == 15:
        swallow_keystroke(event)

    if event.type == X.KeyRelease and event.detail == 15:
        print("exit")
        break
root.ungrab_key(10, 0)
root.ungrab_key(15, 0)
display.close()
