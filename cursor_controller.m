// cursor_controller.m

#include "cursor_controller.h"
#include <Cocoa/Cocoa.h> // Include the Cocoa framework

void initCursorController(CursorController *controller) {
    // Define a frame for the custom cursor
    NSRect frame = NSMakeRect(0, 0, 20, 20);  // Adjust size as necessary
    controller->cursorWindow = [[NSWindow alloc] initWithContentRect:frame
        styleMask:NSWindowStyleMaskBorderless
        backing:NSBackingStoreBuffered defer:NO];

    // Make the window transparent and non-interactive
    [controller->cursorWindow setOpaque:NO];
    [controller->cursorWindow setBackgroundColor:[NSColor clearColor]];
    [controller->cursorWindow setIgnoresMouseEvents:YES];
    [controller->cursorWindow setLevel:NSFloatingWindowLevel];

    // Create a simple view to represent the cursor (you can use a custom cursor image here)
    NSView *cursorView = [[NSView alloc] initWithFrame:frame];
    [controller->cursorWindow setContentView:cursorView];
    [controller->cursorWindow makeKeyAndOrderFront:nil];
}

void moveCursor(CursorController *controller, float x, float y) {
    // Update the controller's position
    controller->currentX += x;
    controller->currentY += y;

    // Move the cursor window to the new position
    NSRect frame = [controller->cursorWindow frame];
    frame.origin.x = controller->currentX;
    frame.origin.y = controller->currentY;
    [controller->cursorWindow setFrameOrigin:frame.origin];
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