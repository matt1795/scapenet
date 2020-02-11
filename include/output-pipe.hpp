// Output Pipe Class
//
// Author: Matthew Knight
// File Name: output-pipe.hpp
// Date: 2018-12-19
//
// This class provides an output stream interface for system pipes.

#pragma once

#include <streambuf>

#include <cstdio>

class OutputPipe {
    FILE* pipe;

  public:
    OutputPipe(std::string const& command)
        : pipe(popen(command.c_str(), "w")) {}

    ~OutputPipe() { pclose(pipe); }

    size_t write(void* ptr, size_t size, size_t count) {
        return fwrite(ptr, size, count, pipe);
    }
};
