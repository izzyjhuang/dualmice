CC = gcc
CFLAGS = -framework IOKit -framework CoreFoundation -framework Cocoa

dualmice: dualmice.o mouse_device_listener.o mouse_device_driver.o cursor_controller.o
	$(CC) -o dualmice dualmice.o mouse_device_listener.o mouse_device_driver.o cursor_controller.o $(CFLAGS)

dualmice.o: dualmice.c
	$(CC) -c dualmice.c $(CFLAGS)

mouse_device_listener.o: mouse_device_listener.c
	$(CC) -c mouse_device_listener.c $(CFLAGS)

mouse_device_driver.o: mouse_device_driver.c
	$(CC) -c mouse_device_driver.c $(CFLAGS)

cursor_controller.o: cursor_controller.c
	$(CC) -c cursor_controller.c $(CFLAGS)

clean:
	rm -f dualmice *.o