//
// Created by canyon on 10.08.16.
//


#include <X11/Xlib.h>
#include <stdio.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/XInput2.h>

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


    XIEventMask eventmask;
    unsigned char mask[1] = {0}; /* the actual mask */

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = sizeof(mask); /* always in bytes */
    eventmask.mask = mask;
/* now set the mask */
    XISetMask(mask, XI_KeyRelease);
    XISetMask(mask, XI_KeyPress);

/* select on the window */
    XISelectEvents(display, win_root, &eventmask, 1);

    while (True) {

        XEvent ev;
        XNextEvent(display, &ev);
        if (ev.xcookie.type == GenericEvent &&
            ev.xcookie.extension == opcode &&
            XGetEventData(display, &ev.xcookie)) {
            XIDeviceEvent *evt = (XIDeviceEvent *) ev.xcookie.data;

            printf("Event: %i, %i - %i\n", evt->evtype, evt->detail, evt->deviceid);
            if (evt->deviceid == 10){
                XTestFakeKeyEvent(display, (unsigned int) evt->detail, evt->evtype == 2, 0);
            }
            if (evt->detail == 12) {
                XFreeEventData(display, &ev.xcookie);
                break;
            }
        }
        XFreeEventData(display, &ev.xcookie);


    }

    XCloseDisplay(display);
}