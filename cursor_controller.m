// cursor_controller.m

#include "cursor_controller.h"
#include <Cocoa/Cocoa.h>
#include <ApplicationServices/ApplicationServices.h>  // For system cursor manipulation

void initCursorController(CursorController *controller) {
    // Define a frame for the custom cursor (no need to display it)
    NSRect frame = NSMakeRect(0, 0, 20, 20);  // Adjust size as necessary

    // Instead of creating a visible window, we skip that step
    controller->cursorWindow = nil;  // No visual window needed
}

void moveCursor(CursorController *controller, float x, float y) {
    // Update the controller's position
    controller->currentX += x;
    controller->currentY += y;

    // Move the actual system cursor to the new position
    CGPoint newCursorPosition = CGPointMake(controller->currentX, controller->currentY);
    CGWarpMouseCursorPosition(newCursorPosition);

    // No need to move a visual window since we’re controlling the system cursor
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