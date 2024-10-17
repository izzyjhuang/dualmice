#include "cursor_controller.h"
#include <CoreGraphics/CoreGraphics.h>

void moveCursor(float x, float y) {
    CGPoint currentPos;
    CGEventRef event = CGEventCreate(NULL);
    currentPos = CGEventGetLocation(event);
    CFRelease(event);

    CGPoint newPos = CGPointMake(currentPos.x + x, currentPos.y - y);
    CGWarpMouseCursorPosition(newPos);
}

void performClick(float x, float y) {
    CGPoint clickPoint = CGPointMake(x, y);

    CGEventRef click1_down = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, clickPoint, kCGMouseButtonLeft);
    CGEventRef click1_up = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, clickPoint, kCGMouseButtonLeft);

    CGEventPost(kCGSessionEventTap, click1_down);
    CGEventPost(kCGSessionEventTap, click1_up);

    CFRelease(click1_down);
    CFRelease(click1_up);
}