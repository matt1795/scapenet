// Map Area class
//
// Author: Matthew Knight
// File name: map-area.hpp
// Date: 2018-12-14
//
// This class is for the map area that contains the map, health, compass, etc.

#pragma once

#include <ui/orb.hpp>
#include <ui/compass.hpp>
#include <ui/mini-map.hpp>
#include <ui/element.hpp>

#include <opencv2/core.hpp>

class MapArea {
	Compass compass;
	Orb health, prayer, energy, specialAttack;
	MiniMap map;

	const size_t width = 235;
	const size_t height = 168;

public:
	// ctor
	MapArea(const cv::Point& position)
		: compass()
		, health()
		, prayer()
		, energy()
		, specialAttack()
		, map()
	{}
};
