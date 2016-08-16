//
// Created by canyon on 11.08.16.
//

#include <X11/Xlib.h>
#include <stdio.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <thread>


int get_master_keyboard_id(Display *display){
    int num_devices;
    XIDeviceInfo *devices = XIQueryDevice(display, XIAllMasterDevices, &num_devices);

    for (int i = 0; i < num_devices; ++i) {
        XIDeviceInfo *device = &devices[i];
        if (device->use == XIMasterKeyboard){
            return device->deviceid;
        }
    }
    return -1;
}

int main() {
    /* Connect to the X server */
    Display *display = XOpenDisplay(NULL);
    Window win_root = XDefaultRootWindow(display);

/* XInput Extension available? */
    int opcode, event, error;
    if (!XQueryExtension(display, "XInputExtension", &opcode, &event, &error)) {
        printf("X Input extension not available.\n");
        return -1;
    }

/* Which version of XI2? We support 2.0 */
    int major = 2, minor = 0;
    if (XIQueryVersion(display, &major, &minor) == BadRequest) {
        printf("XI2 not available. Server supports %d.%d\n", major, minor);
        return -1;
    }


    XIDetachSlaveInfo info;
    info.type = XIDetachSlave;
    info.deviceid = 10;

    XIAnyHierarchyChangeInfo any_info;
    any_info.type = XIDetachSlave;
    any_info.detach = info;
    XIChangeHierarchy(display, &any_info, 1);

    printf("Detached slave device 10\n");

    int master_id = get_master_keyboard_id(display);
    if (master_id == -1){
        printf("No master keyboard available.\n");
        return -1;
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));

    XIAttachSlaveInfo attach_info;
    attach_info.type = XIAttachSlave;
    attach_info.deviceid = 10;
    attach_info.new_master = master_id;
    XIAnyHierarchyChangeInfo any_attach_info;
    any_attach_info.type = XIAttachSlave;
    any_attach_info.attach = attach_info;
    XIChangeHierarchy(display, &any_attach_info, 1);

    printf("Attached slave device 10\n");

    XCloseDisplay(display);
}