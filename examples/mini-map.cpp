// Mini Map Analysis
//
// Author: Matthew Knight
// File Name: mini-map.cpp
// Date: 2018-12-14
//
// This program analyzes the map and tells you what's on it.

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
	cv::Mat mask = cv::imread(argv[1], -1);
	std::vector<cv::Mat> channels(4);

	cv::split(mask, channels);
	cv::imwrite(argv[2], channels[3]);
}
