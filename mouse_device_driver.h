// mouse_device_driver.h

#ifndef MOUSE_DEVICE_DRIVER_H
#define MOUSE_DEVICE_DRIVER_H

#include <IOKit/hid/IOHIDManager.h>
#include "cursor_controller.h"  // Include this to define CursorController

typedef struct {
    IOHIDDeviceRef device;
    CursorController cursorController;  // Each device has its own cursor controller
} MouseDeviceDriver;

void addDriverForDevice(IOHIDDeviceRef device);
void removeDriverForDevice(IOHIDDeviceRef device);

#endif