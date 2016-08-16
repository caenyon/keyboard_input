//
// This script uses Xlibs XGrabKey function to grab three keys:
// - Key "1" events are passed to other applications
// - Key "2" events are consumed
// - Key "3" exits the programm
//
// PROBLEM:
// This program uses XAllowEvents with the ReplayKeyboard option to signal that specific events
// should be redirected to other windows. Unfortunately, the X server immediately redirects the
// KeyRelease event for a key to the other windows if XAllowEvents has been called with the
// ReplayKeyboard option on the corresponding KeyPress event.
//
// This means that the application doesn't get notified when the key is released!
//
#include <stdio.h>
#include <X11/Xlib.h>


int main() {
    // open connection to the x server
    Display *display = XOpenDisplay(0);
    if (display == NULL)
        return -1;

    // turn off auto repeat, just for testing
    XAutoRepeatOff(display);


    Window win_root = XDefaultRootWindow(display);  // returns root window of default screen

    XGrabKey(display, 10, 0, win_root, True, GrabModeSync, GrabModeSync);
    XGrabKey(display, 11, 0, win_root, True, GrabModeSync, GrabModeSync);
    XGrabKey(display, 12, 0, win_root, True, GrabModeSync, GrabModeSync);

    while (true) {
        XEvent event;
        XNextEvent(display, &event);

        printf("EVENT: %i, %i\n", event.type, event.xkey.keycode);

        if (event.xkey.keycode == 12) {

            // exit if key "3" is pressed
            break;
        }
        if (event.xkey.keycode == 11) {

            // capture and "swallow" key "2" events
            XAllowEvents(display, AsyncKeyboard, event.xkey.time);
        } else {

            // pass key "1" events to other applications
            XAllowEvents(display, ReplayKeyboard, event.xkey.time);
            XFlush(display);
        }
    }

    // re-enable auto repeat
    XAutoRepeatOn(display);

    // close the connection to the x server
    XCloseDisplay(display);
    return 0;
}