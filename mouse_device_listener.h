// mouse_device_listener.h

#ifndef MOUSE_DEVICE_LISTENER_H
#define MOUSE_DEVICE_LISTENER_H

#include <IOKit/hid/IOHIDManager.h>

typedef struct {
    IOHIDManagerRef manager;
} MouseDeviceListener;

void startListening(MouseDeviceListener *listener);
void addDriverForDevice(IOHIDDeviceRef device);
void removeDriverForDevice(IOHIDDeviceRef device);

#endif