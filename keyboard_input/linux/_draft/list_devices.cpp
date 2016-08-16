#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>

int error_handler(Display *d, XErrorEvent *e)
{
    throw e;
}

void list_devices(Display *display) {
    XSetErrorHandler(error_handler);
    int *num_devices = new int{};
    XDeviceInfo *device_info = XListInputDevices(display, num_devices);
    printf("Num_Devices: %i\n",*num_devices);
    for (int i = 0; i < *num_devices; ++i) {

        printf("Device: %s\n", device_info[i].name);
        printf("\tID: %lu\n", device_info[i].id);
        printf("\tType: %lu\n", device_info[i].type);
        printf("\tUse: %i\n", device_info[i].use);
        printf("\tNum_Classes: %i\n", device_info[i].num_classes);
        for (int j = 0; j < device_info[i].num_classes; ++j) {
            printf("\t\tClass ID: %lu, Length: %i\n", device_info[i].inputclassinfo[j].c_class,
                   device_info[i].inputclassinfo[j].length);
        }

        try {
            XDevice *device = XOpenDevice(display, device_info[i].id);
            XCloseDevice(display, device);
            printf("\tDevice is acessible\n");

        }catch (XErrorEvent *w){
            printf("\tCould not open Device!\n");
        }
    }
    XFreeDeviceList(device_info);
}

int main()
{
    Display *display = XOpenDisplay(0);
    if(display == NULL)
        return -1;

    list_devices(display);

    XCloseDisplay(display);
    return 0;
}