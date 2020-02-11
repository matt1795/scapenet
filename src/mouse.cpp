// Mouse Interface Class
//
// Author: Matthew Knight
// File Name: mouse.hpp
// Date: 2018-12-13
//
// This class represents a real world mouse that is able to move the cursor and
// click.

#include <control/mouse.hpp>

#include <X11/extensions/XTest.h>

#include <chrono>
#include <stdexcept>
#include <thread>

Mouse::Mouse()
    : display(XOpenDisplay(NULL)) {
    if (display == NULL)
        throw std::runtime_error("Couldn't open XDisplay");
}

Mouse::~Mouse() {
    XFlush(display);
    XCloseDisplay(display);
}

// move cursor to position instantly
void Mouse::move(const cv::Point& position) {
    XTestFakeMotionEvent(display, 0, position.x, position.y, CurrentTime);
    XSync(display, 0);
}

void Mouse::leftClick(const cv::Point& position) { click(position, Button1); }

void Mouse::rightClick(const cv::Point& position) { click(position, Button3); }

void Mouse::click(const cv::Point& position, unsigned int button) {
    move(position);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    XTestFakeButtonEvent(display, button, True, CurrentTime);
    XTestFakeButtonEvent(display, button, False, CurrentTime);
    XSync(display, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
