#include "mouse_device_listener.h"
#include <CoreFoundation/CoreFoundation.h>
#include <stdio.h>
#include <stdlib.h>

static void DeviceMatchingCallback(void *inContext, IOReturn inResult, void *inSender, IOHIDDeviceRef inIOHIDDeviceRef);
static void DeviceRemovalCallback(void *inContext, IOReturn inResult, void *inSender, IOHIDDeviceRef inIOHIDDeviceRef);

void startListening(MouseDeviceListener *listener) {
    listener->manager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDManagerOptionNone);
    if (CFGetTypeID(listener->manager) != IOHIDManagerGetTypeID()) {
        exit(1);
    }

    CFDictionaryRef matchingDict = CFDictionaryCreate(kCFAllocatorDefault,
        (const void*[]){ CFSTR(kIOHIDDeviceUsagePageKey), CFSTR(kIOHIDDeviceUsageKey) },
        (const void*[]){ CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &(int){kHIDPage_GenericDesktop}),
                         CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &(int){kHIDUsage_GD_Mouse}) },
        2, NULL, NULL);

    IOHIDManagerSetDeviceMatching(listener->manager, matchingDict);
    IOHIDManagerRegisterDeviceMatchingCallback(listener->manager, DeviceMatchingCallback, listener);
    IOHIDManagerRegisterDeviceRemovalCallback(listener->manager, DeviceRemovalCallback, listener);
    IOHIDManagerOpen(listener->manager, kIOHIDOptionsTypeNone);
    IOHIDManagerScheduleWithRunLoop(listener->manager, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
}

static void DeviceMatchingCallback(void *inContext, IOReturn inResult, void *inSender, IOHIDDeviceRef inIOHIDDeviceRef) {
    MouseDeviceListener *listener = (MouseDeviceListener *)inContext;
    if (!listener->systemMouse) {
        listener->systemMouse = inIOHIDDeviceRef;
        IOHIDDeviceClose(inIOHIDDeviceRef, 0);
    } else {
        addDriverForDevice(inIOHIDDeviceRef);
    }
}

static void DeviceRemovalCallback(void *inContext, IOReturn inResult, void *inSender, IOHIDDeviceRef inIOHIDDeviceRef) {
    removeDriverForDevice(inIOHIDDeviceRef);
}