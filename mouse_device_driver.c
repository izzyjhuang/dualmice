// mouse_device_driver.c

#include "mouse_device_driver.h"
#include "cursor_controller.h"
#include <IOKit/hid/IOHIDUsageTables.h>  // Include this for HID usage constants
#include <CoreFoundation/CoreFoundation.h>  // Include this for CFDictionary and CFNumber handling

static void InputValueCallback(void *context, IOReturn result, void *sender, IOHIDValueRef value);

void addDriverForDevice(IOHIDDeviceRef device) {
    // Create the matching dictionary for X, Y, and mouse usages
    CFNumberRef usagePage = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &(int){kHIDPage_GenericDesktop});
    CFNumberRef usageX = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &(int){kHIDUsage_GD_X});
    CFNumberRef usageY = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &(int){kHIDUsage_GD_Y});
    CFNumberRef usageMouse = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &(int){kHIDUsage_GD_Mouse});
    
    // Create matching dictionaries for each usage (X, Y, Mouse)
    CFDictionaryRef matchingX = CFDictionaryCreate(kCFAllocatorDefault,
        (const void *[]){ CFSTR(kIOHIDElementUsagePageKey), CFSTR(kIOHIDElementUsageKey) },
        (const void *[]){ usagePage, usageX },
        2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    CFDictionaryRef matchingY = CFDictionaryCreate(kCFAllocatorDefault,
        (const void *[]){ CFSTR(kIOHIDElementUsagePageKey), CFSTR(kIOHIDElementUsageKey) },
        (const void *[]){ usagePage, usageY },
        2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    CFDictionaryRef matchingMouse = CFDictionaryCreate(kCFAllocatorDefault,
        (const void *[]){ CFSTR(kIOHIDElementUsagePageKey), CFSTR(kIOHIDElementUsageKey) },
        (const void *[]){ usagePage, usageMouse },
        2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    // Create an array of matching dictionaries (for X, Y, and Mouse)
    CFArrayRef criteria = CFArrayCreate(kCFAllocatorDefault, (const void *[]){ matchingX, matchingY, matchingMouse }, 3, &kCFTypeArrayCallBacks);

    // Set matching criteria and input callback
    IOHIDDeviceSetInputValueMatchingMultiple(device, criteria);
    IOHIDDeviceRegisterInputValueCallback(device, InputValueCallback, NULL);

    // Release the created objects after use
    CFRelease(usagePage);
    CFRelease(usageX);
    CFRelease(usageY);
    CFRelease(usageMouse);
    CFRelease(matchingX);
    CFRelease(matchingY);
    CFRelease(matchingMouse);
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