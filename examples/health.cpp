// Determine current hitpoints
//
// Author: Matthew Knight
// File Name: health.cpp
// Date: 2018-12-14
//
// This program takes an image of the health number and determines the value.

#include <opencv2/opencv.hpp>

#include <iostream>

int main() {
	cv::Mat health = cv::imread("../images/map/health.png");

	//cv::Mat channel = health[0];
	//cv::imwrite("output.png", channel);

	std::cout << health << std::endl;
}
