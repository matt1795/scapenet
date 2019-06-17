// Keyboard Interface Class
//
// Author: Matthew Knight
// File Name: keyboard.hpp
// Date: 2018-12-13
//
// This class is used as an interface for different keyboard emulation
// implementations.

#include <control/keyboard.hpp>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#include <iostream>
#include <string>
#include <unordered_map>

#define Shift_L 0xffe1

const std::unordered_map<char, KeySym> modkeys = {
	{ '@', Shift_L }
};

Keyboard::Keyboard() : display(XOpenDisplay(NULL)) {

	// TODO null catch
}

Keyboard::~Keyboard() {
	XCloseDisplay(display);
}

void Keyboard::type(const std::string& str) {
	for (int i = 0; i < str.size(); i++) {

		KeySym sym = static_cast<KeySym>(str[i]);
		KeyCode modcode = 0, code = XKeysymToKeycode(display, sym);

		auto it = modkeys.find(str[i]);
		if (it != modkeys.end()) {
			modcode = XKeysymToKeycode(display, it->second);
		}

		if (modcode != 0)
			XTestFakeKeyEvent(display, modcode, True, 0);

		XTestFakeKeyEvent(display, code, True, 0);
		XTestFakeKeyEvent(display, code, False, 0);

		if (modcode != 0)
			XTestFakeKeyEvent(display, modcode, False, 0);

		XSync(display, 0);
	}
};
