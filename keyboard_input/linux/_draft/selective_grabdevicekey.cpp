//
// Created by canyon on 10.08.16.
//


#include <X11/extensions/XInput.h>

int main(){

    XGrabDeviceKey(display, device, 10, 0, NULL, winRoot, 1, 1, &classes[0], 0, 0);

};