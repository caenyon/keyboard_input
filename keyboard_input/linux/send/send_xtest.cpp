//
// This script uses the XTestFakeKeyEvent method from the XTest extension of the Xlib library
// to send key events to the running x-server.
//

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <chrono>
#include <thread>

int main(){

    // open connection to the x server
    Display *display = XOpenDisplay(0);
    if (display == NULL)
        return -1;

    // sleep for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // send a key press and key release event for key 53 ('x' character)
    XTestFakeKeyEvent(display, 53, True, 0);
    XTestFakeKeyEvent(display, 53, False, 0);

    // flush to ensure that the key events are sent to the server
    XFlush(display);

    // close connection
    XCloseDisplay(display);
};
