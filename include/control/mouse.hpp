// Mouse Interface Class
//
// Author: Matthew Knight
// File Name: mouse.hpp
// Date: 2018-12-13
//
// This class represents a real world mouse that is able to move the cursor and
// click. This is an abstract class so we have flexibility of more than one
// implementation

#pragma once

#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <opencv2/opencv.hpp>

class Mouse {
    Display* display;

    void click(const cv::Point& position, unsigned int button);

  public:
    Mouse();
    ~Mouse();

    // move cursor to position instantly
    void move(const cv::Point& position);

    void leftClick(const cv::Point& position);
    void rightClick(const cv::Point& position);
};
