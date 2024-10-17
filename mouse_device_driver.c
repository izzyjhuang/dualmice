#include "mouse_device_driver.h"
#include "cursor_controller.h"
#include <IOKit/hid/IOHIDUsageTables.h>  // Include this for HID usage constants

static void InputValueCallback(void *context, IOReturn result, void *sender, IOHIDValueRef value);

void addDriverForDevice(IOHIDDeviceRef device) {
    // Use CFNumberCreate to create Core Foundation numbers for HID usages
    CFNumberRef usageX = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &(int){kHIDUsage_GD_X});
    CFNumberRef usageY = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &(int){kHIDUsage_GD_Y});
    CFNumberRef usageMouse = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &(int){kHIDUsage_GD_Mouse});

    // Create array of criteria using the usage numbers
    CFArrayRef criteria = CFArrayCreate(NULL, (const void*[]){ usageX, usageY, usageMouse }, 3, NULL);

    IOHIDDeviceSetInputValueMatchingMultiple(device, criteria);
    IOHIDDeviceRegisterInputValueCallback(device, InputValueCallback, NULL);

    // Release the Core Foundation objects after use
    CFRelease(usageX);
    CFRelease(usageY);
    CFRelease(usageMouse);
    CFRelease(criteria);
}

void removeDriverForDevice(IOHIDDeviceRef device) {
    // Logic to remove the driver (if needed)
}

static void InputValueCallback(void *context, IOReturn result, void *sender, IOHIDValueRef value) {
    IOHIDElementRef element = IOHIDValueGetElement(value);
    uint32_t usage = IOHIDElementGetUsage(element);

    // Check for X and Y movement, and handle accordingly
    if (usage == kHIDUsage_GD_X || usage == kHIDUsage_GD_Y) {
        float x = (usage == kHIDUsage_GD_X) ? IOHIDValueGetScaledValue(value, kIOHIDValueScaleTypeCalibrated) : 0;
        float y = (usage == kHIDUsage_GD_Y) ? IOHIDValueGetScaledValue(value, kIOHIDValueScaleTypeCalibrated) : 0;
        moveCursor(x, y);  // Move the cursor based on input
    }
}