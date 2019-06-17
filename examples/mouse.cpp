// Creating X11 Mouse Events
//
// Author: Matthew Knight
// File Name: mouse.cpp
// Date: 2018-12-23

#include <X11/extensions/XTest.h>

#include <chrono>
#include <iostream>
#include <thread>

#include <cstring>

int main() {
	Display* display = XOpenDisplay(NULL);

	if (display == NULL) {
		std::cerr << "Couldn't open the display" << std::endl;
		exit(1);
	}

	XEvent event;
	XQueryPointer(display, RootWindow(display, 0),
		&event.xbutton.root,
		&event.xbutton.window,
		&event.xbutton.x_root,
		&event.xbutton.y_root,
		&event.xbutton.x,
		&event.xbutton.y,
		&event.xbutton.state
	);

	XTestFakeMotionEvent(
		display,
		0,
		event.xbutton.x + 100,
		event.xbutton.y + 50,
		CurrentTime
	);

	XSync(display, 0);
	std::this_thread::sleep_for(std::chrono::seconds(3));

	XTestFakeMotionEvent(display, 0, 250, 250, CurrentTime);
	std::this_thread::sleep_for(std::chrono::seconds(3));

	XTestFakeButtonEvent(display, 3, True, CurrentTime);
	XTestFakeButtonEvent(display, 3, False, CurrentTime);

	XFlush(display);
	XCloseDisplay(display);
}
