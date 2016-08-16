# coding=utf-8
"""
This program uses the uinput python package to create a new user-space input device to emit key events.

 Properties:
 - requires uinput python package
 - requires root!

 This script is a modified version of https://github.com/tuomasjjrasanen/python-uinput
"""
import uinput
from time import sleep


if __name__ == "__main__":

    # define the keys of the virtual input device. In this example, we only create a device with
    # a single key that sends an "x" character
    events = (uinput.KEY_X,)

    # create virtual input device
    with uinput.Device(events) as device:

        # sleep 5 seconds
        sleep(5)

        # emit a single click (key press and key release event)
        device.emit_click(uinput.KEY_X)
