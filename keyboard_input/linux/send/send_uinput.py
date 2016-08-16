# coding=utf-8

# modified version of https://github.com/tuomasjjrasanen/python-uinput

# requires root!

import time

import uinput

if __name__ == "__main__":
    events = (uinput.KEY_X,)

    with uinput.Device(events) as device:
        time.sleep(5)
        device.emit_click(uinput.KEY_X)
