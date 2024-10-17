// cursor_controller.h

#ifndef CURSOR_CONTROLLER_H
#define CURSOR_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Cocoa/Cocoa.h>

typedef struct {
    NSWindow *cursorWindow;
    float currentX;
    float currentY;
} CursorController;

void initCursorController(CursorController *controller);
void moveCursor(CursorController *controller, float x, float y);
void performClick(float x, float y);

#ifdef __cplusplus
}
#endif

#endif