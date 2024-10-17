#ifndef MOUSE_DEVICE_DRIVER_H
#define MOUSE_DEVICE_DRIVER_H

#include <IOKit/hid/IOHIDManager.h>

void addDriverForDevice(IOHIDDeviceRef device);
void removeDriverForDevice(IOHIDDeviceRef device);

#endif