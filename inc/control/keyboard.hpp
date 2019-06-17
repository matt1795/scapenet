// Keyboard Interface Class
//
// Author: Matthew Knight
// File Name: keyboard.hpp
// Date: 2018-12-13
//
// This class is used as an interface for different keyboard emulation
// implementations.

#pragma once

#include <X11/extensions/XTest.h>

#include <string>

class Keyboard {
	Display *display;

public:
	Keyboard();
	~Keyboard();

	// type in a full string
	void type(const std::string& str);

};
