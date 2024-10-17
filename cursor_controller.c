// cursor_controller.c

#include "cursor_controller.h"
#include <CoreGraphics/CoreGraphics.h>

void moveCursor(CursorController* controller, float x, float y) {
    // Update the controller's position
    controller->currentX += x;
    controller->currentY += y;

    // Move the cursor to the new position
    CGPoint newPos = CGPointMake(controller->currentX, controller->currentY);
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