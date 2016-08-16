//
// This script uses Xlibs XGrabKeyboard function to grab the keyboard. Implemented actions:
// - Key "2" events are consumed
// - Key "3" exits the programm
// - Other Key: Events are passed to other applications
//
// PROBLEM:
// XAllowEvents doesn't work when using GrabKeyboard
//
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>


int main() {
    // open connection to the x server
    Display *display = XOpenDisplay(0);
    if (display == NULL)
        return -1;

    // turn off auto repeat, just for testing
    XAutoRepeatOff(display);


    Window win_root = XDefaultRootWindow(display);  // returns root window of default screen

    XSelectInput(display, win_root, KeyPressMask | KeyReleaseMask);


    // grab keyboard
    XGrabKeyboard(display, win_root, 0, GrabModeAsync, GrabModeAsync, CurrentTime);
    XSync(display, false);

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
        } else {

            // pass other events to other applications
            XTestFakeKeyEvent(display, event.xkey.keycode, event.xkey.type == 2, 0);
        }
    }

    // re-enable auto repeat
    XAutoRepeatOn(display);

    // release keyboard grab
    XUngrabKeyboard(display, CurrentTime);
    XSync(display, false);

    // close the connection to the x server
    XCloseDisplay(display);
    return 0;
}
