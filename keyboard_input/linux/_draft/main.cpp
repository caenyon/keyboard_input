//
// Created by canyon on 10.08.16.
//
#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>
#include <thread>

void grab_ungrab_device(Display *display){
    Window winRoot = XDefaultRootWindow(display);  // returns root window of default screen
    XDevice *device = XOpenDevice(display, 14);

    int event_count = 1;
    XEventClass events[1] = {1};
    XGrabDevice(display, device, winRoot, 1, event_count, events, 0, 0, CurrentTime);


    XUngrabDevice(display, device, CurrentTime);
}

int main()
{
    Display *display = XOpenDisplay(0);
    if(display == NULL)
        return -1;
    XAutoRepeatOff(display);

    //grab_ungrab_keyboard(display);

    Window win_root = XDefaultRootWindow(display);  // returns root window of default screen

    XGrabKey(display, 10, 0, win_root, True, GrabModeSync, GrabModeSync);
    XGrabKey(display, 11, 0, win_root, True, GrabModeSync, GrabModeSync);
    XGrabKey(display, 12, 0, win_root, True, GrabModeSync, GrabModeSync);

    //XGrabDeviceKey(display, device, 10, 0, NULL, winRoot, 1, 1, &classes[0], 0, 0);

    //XSync(display, False);

    while (true){
        XEvent event;
        XNextEvent(display, &event);

        printf("EVENT: %i, %i\n",event.type, event.xkey.keycode);

        if (event.xkey.keycode == 12){
            break;
        }
        if (event.xkey.keycode ==11){
            XAllowEvents(display, AsyncKeyboard, event.xkey.time);
        }else{
            XAllowEvents(display, ReplayKeyboard, event.xkey.time);
            XFlush(display);
        }
    }

    XAutoRepeatOn(display);
    XCloseDisplay(display);
    return 0;
}