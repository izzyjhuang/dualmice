// cursor_controller.h

#ifndef CURSOR_CONTROLLER_H
#define CURSOR_CONTROLLER_H

typedef struct {
    // Add fields to manage cursor state (if necessary)
    float currentX;
    float currentY;
} CursorController;

void moveCursor(CursorController* controller, float x, float y);
void performClick(float x, float y);

#endif