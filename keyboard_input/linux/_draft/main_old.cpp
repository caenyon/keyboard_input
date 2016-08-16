// Send a fake keystroke event to an X window.
// by Adam Pierce - http://www.doctort.org/adam/
// This is public domain software. It is free to use by anyone for any purpose.

#include <X11/Xlib.h>
#include <X11/extensions/XI.h> // only constants
#include <X11/extensions/XI2.h>  // only constants
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/XKB.h>  // only constants
#include <X11/keysym.h>
#include <chrono>
#include <thread>

// The key code to be sent.
// A full list of available codes can be found in /usr/include/X11/keysymdef.h
#define KEYCODE XK_Down

// Function to create a keyboard event
XKeyEvent createKeyEvent(Display *display, Window &win,
                         Window &winRoot, bool press,
                         int keycode)
{
    XKeyEvent event;

    event.display     = display;
    event.window      = win;
    event.root        = winRoot;
    event.subwindow   = None;
    event.time        = CurrentTime;
    event.x           = 1;
    event.y           = 1;
    event.x_root      = 1;
    event.y_root      = 1;
    event.same_screen = True;
    event.keycode     = XKeysymToKeycode(display, keycode);
    event.state       = 0;

    if(press)
        event.type = KeyPress;
    else
        event.type = KeyRelease;

    return event;
}

int main()
{

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
// Obtain the X11 display.
    Display *display = XOpenDisplay(0);
    if(display == NULL)
        return -1;
    printf("Num_Screens %i\n", ScreenCount(display));

// Get the root window for the current display.
    Window winRoot = XDefaultRootWindow(display);  // returns root window of default screen

// Find the window which has the current keyboard focus.
    Window winFocus;
    int    revert;
    XGetInputFocus(display, &winFocus, &revert);

    printf("Root %ld\n", (unsigned long) winRoot);

    printf("Focus %ld\n", (unsigned long) winFocus);
    printf("Keycode %d\n", KEYCODE);



// Send a fake key press event to the window.
    XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, KEYCODE);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

// Send a fake key release event to the window.
    event = createKeyEvent(display, winFocus, winRoot, false, KEYCODE);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

// Done.
    XCloseDisplay(display);
    return 0;
}