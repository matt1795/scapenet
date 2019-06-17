// Mini Map Class
//
// Author: Matthew Knight
// File Name: mini-map.hpp
// Date: 2018-12-20
//
// This class acts as a simple container for the map section of the ui. It has
// the constants of where it is located, and applies a mask to the map to remove
// the borders.

#pragma once

#include <opencv2/opencv.hpp>

class MiniMap {
	const cv::Rect rect = cv::Rect(570, 9, 145, 151);
	cv::Mat map;

public:
	MiniMap(cv::Mat const& frame) : map(frame, rect) {}

	cv::Mat getMat() {
		return map;
	}
};
