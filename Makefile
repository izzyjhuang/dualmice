CC = gcc
CFLAGS = -framework IOKit -framework CoreFoundation -framework Cocoa

macpaste: macpaste.o mouse_device_listener.o mouse_device_driver.o cursor_controller.o
	$(CC) -o macpaste macpaste.o mouse_device_listener.o mouse_device_driver.o cursor_controller.o $(CFLAGS)

macpaste.o: macpaste.c
	$(CC) -c macpaste.c $(CFLAGS)

mouse_device_listener.o: mouse_device_listener.c
	$(CC) -c mouse_device_listener.c $(CFLAGS)

mouse_device_driver.o: mouse_device_driver.c
	$(CC) -c mouse_device_driver.c $(CFLAGS)

cursor_controller.o: cursor_controller.c
	$(CC) -c cursor_controller.c $(CFLAGS)

clean:
	rm -f macpaste *.o