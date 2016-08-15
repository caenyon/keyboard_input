# coding=utf-8

from Xlib.display import Display
from Xlib.ext import xinput, xtest

KEYBOARD_MASTER = 3
EXIT_KEY = 127  # Pause-Key


class DeviceListener(object):
    def __init__(self):
        self.display = Display()

        self.win_root = self.display.screen().root

        extension_info = self.display.query_extension('XInputExtension')
        self.xinput_major = extension_info.major_opcode

        self.device = None

        v = xinput.query_version(self.display)
        print("Version: {}, {}".format(v.major_version, v.minor_version))

        self.select_device()

    def select_device(self, device=None):
        self.device = device
        mask = xinput.KeyPressMask + xinput.KeyReleaseMask
        if device is None:
            xinput.select_events(self.win_root, ((xinput.AllDevices, mask),))
        else:
            xinput.select_events(self.win_root, ((device, mask), (xinput.AllDevices, 0)))
            self.display.xinput_detach_slave(device)

    def event_loop(self):
        while True:
            event = self.display.next_event()
            if event.type == self.display.extension_event.GenericEvent \
                    and event.extension == self.xinput_major:
                if not self.handle_event(event):
                    break

    def get_device_id(self):
        event = self.display.next_event()
        if event.type == self.display.extension_event.GenericEvent \
                and event.extension == self.xinput_major:
            return event.data.deviceid

    def handle_event(self, event):
        print("Event: {}, {}, {}".format(event.evtype, event.data.detail, event.data.deviceid))
        return not event.data.detail == EXIT_KEY

    def send_event(self, key_code, key_down):
        xtest.fake_input(self.display,
                         event_type=2 if key_down else 3,
                         detail=key_code)

    def close(self):
        self.display.xinput_attach_slave(self.device, KEYBOARD_MASTER)
        self.display.close()


if __name__ == '__main__':
    dl = DeviceListener()
    print("Press any key to select a device...")
    d_id = dl.get_device_id()
    print("Selected device: {}".format(d_id))
    dl.select_device(d_id)
    dl.event_loop()
    dl.close()
