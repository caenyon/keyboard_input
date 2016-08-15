# coding=utf-8
import struct
import time
from Xlib.ext import xinput
from Xlib.display import Display
from Xlib import X

display = Display()

s = '=BBHLLLHBBB1xH'
vals = [131, 51, 8, 1, 0, 0, 5, 1, 1, False, 2]
struct.pack(s, *vals)


def grab_device(self, deviceid, time, grab_mode, paired_device_mode, owner_events, event_mask):
    return xinput.XIGrabDevice(
        display=self.display,
        opcode=self.display.get_extension_major(xinput.extname),
        deviceid=deviceid,
        grab_window=0,
        time=time,
        cursor=X.NONE,
        grab_mode=grab_mode,
        paired_device_mode=paired_device_mode,
        owner_events=owner_events,
        mask=event_mask,
        )


# xinput.grab_keycode(display, 5, X.CurrentTime, 15, X.GrabModeSync, 0, 0, 12, (0,0))
grab_device(display, 5, X.CurrentTime, xinput.GrabModeAsync, xinput.GrabModeAsync, 0, (5, xinput.KeyPressMask))

time.sleep(5)

xinput.ungrab_keycode(display, 5, 15, (0,0))

