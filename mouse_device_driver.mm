// mouse_device_driver.mm

#include "mouse_device_driver.h"
#include "cursor_controller.h"
#include <IOKit/hid/IOHIDUsageTables.h>
#include <CoreFoundation/CoreFoundation.h>

// Store drivers for each connected device
static MouseDeviceDriver* deviceDrivers[10];  // Assuming max 10 devices for simplicity
static int deviceCount = 0;

static void InputValueCallback(void *context, IOReturn result, void *sender, IOHIDValueRef value);

void addDriverForDevice(IOHIDDeviceRef device) {
    if (deviceCount >= 10) return;  // Limit to 10 devices for now

    // Create a new driver for this device
    MouseDeviceDriver* driver = (MouseDeviceDriver*)malloc(sizeof(MouseDeviceDriver));
    driver->device = device;

    // Initialize each cursor independently and position them separately
    initCursorController(&driver->cursorController);
    driver->cursorController.currentX = 100 + (deviceCount * 50);  // Offset initial position to avoid overlap
    driver->cursorController.currentY = 100 + (deviceCount * 50);

    // Ensure the cursor window is shown for this device
    [driver->cursorController.cursorWindow makeKeyAndOrderFront:nil];

    // Store the driver in the array
    deviceDrivers[deviceCount++] = driver;

    // Set up matching criteria for the device
    int genericDesktopPage = kHIDPage_GenericDesktop;
    int usageXValue = kHIDUsage_GD_X;
    int usageYValue = kHIDUsage_GD_Y;

    CFNumberRef usagePage = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &genericDesktopPage);
    CFNumberRef usageX = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &usageXValue);
    CFNumberRef usageY = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &usageYValue);

    CFDictionaryRef matchingX = CFDictionaryCreate(kCFAllocatorDefault,
        (const void *[]){ CFSTR(kIOHIDElementUsagePageKey), CFSTR(kIOHIDElementUsageKey) },
        (const void *[]){ usagePage, usageX },
        2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    CFDictionaryRef matchingY = CFDictionaryCreate(kCFAllocatorDefault,
        (const void *[]){ CFSTR(kIOHIDElementUsagePageKey), CFSTR(kIOHIDElementUsageKey) },
        (const void *[]){ usagePage, usageY },
        2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    CFArrayRef criteria = CFArrayCreate(kCFAllocatorDefault, (const void *[]){ matchingX, matchingY }, 2, &kCFTypeArrayCallBacks);

    // Set matching criteria and input callback
    IOHIDDeviceSetInputValueMatchingMultiple(device, criteria);
    IOHIDDeviceRegisterInputValueCallback(device, InputValueCallback, driver);  // Pass the driver as context

    // Release the created objects after use
    CFRelease(usagePage);
    CFRelease(usageX);
    CFRelease(usageY);
    CFRelease(matchingX);
    CFRelease(matchingY);
    CFRelease(criteria);
}

void removeDriverForDevice(IOHIDDeviceRef device) {
    // Find and remove the driver for the given device
    for (int i = 0; i < deviceCount; i++) {
        if (deviceDrivers[i]->device == device) {
            free(deviceDrivers[i]);
            // Shift remaining drivers down
            for (int j = i; j < deviceCount - 1; j++) {
                deviceDrivers[j] = deviceDrivers[j + 1];
            }
            deviceCount--;
            break;
        }
    }
}

static void InputValueCallback(void *context, IOReturn result, void *sender, IOHIDValueRef value) {
    MouseDeviceDriver* driver = (MouseDeviceDriver*)context;  // Get the driver for the current device
    IOHIDElementRef element = IOHIDValueGetElement(value);
    uint32_t usage = IOHIDElementGetUsage(element);

    // Handle X and Y movement for this device's cursor
    if (usage == kHIDUsage_GD_X || usage == kHIDUsage_GD_Y) {
        float x = (usage == kHIDUsage_GD_X) ? IOHIDValueGetScaledValue(value, kIOHIDValueScaleTypeCalibrated) : 0;
        float y = (usage == kHIDUsage_GD_Y) ? IOHIDValueGetScaledValue(value, kIOHIDValueScaleTypeCalibrated) : 0;
        moveCursor(&driver->cursorController, x, y);  // Move this device's cursor
    }
}