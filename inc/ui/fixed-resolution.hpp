// Fixed Resolution UI Class
//
// Author: Matthew Knight
// File Name: fixed-resolution.hpp
// Date: 2018-12-14
//
// This class implements the UI class for the fixed resolution setting.

#pragma once

#include <ui/ui.hpp>

class FixedResolution : public UI {
	MapArea map;
	Menu menu;

	public:
		FixedResultion() : map(516, 0)

		int getHealth();
};
