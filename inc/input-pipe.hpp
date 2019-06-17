// Input Pipe Class
//
// Author: Matthew Knight
// File Name: input-pipe.hpp
// Date: 2018-12-19
//
// This class provides an inpur stream interface for system pipes.

#pragma once

#include <streambuf>

#include <cstdio>

class InputPipe {
	FILE* pipe;

public:
	InputPipe(std::string const& command)
		: pipe(popen(command.c_str(), "r"))
	{
		if (pipe == NULL)
			throw "Error opening pipe";
	}

	~InputPipe() {
		pclose(pipe);
	}

	int read(void* ptr, size_t size, size_t count) {
		return fread(ptr, size, count, pipe);
	}
};
