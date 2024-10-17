// mouse_device_driver.h

#ifndef MOUSE_DEVICE_DRIVER_H
#define MOUSE_DEVICE_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <IOKit/hid/IOHIDManager.h>
#include "cursor_controller.h"

typedef struct {
    IOHIDDeviceRef device;
    CursorController cursorController;
} MouseDeviceDriver;

void addDriverForDevice(IOHIDDeviceRef device);
void removeDriverForDevice(IOHIDDeviceRef device);

#ifdef __cplusplus
}
#endif

#endif