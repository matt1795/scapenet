// Agent Program
//
// Author: Matthew Knight
// File Name: agent.cpp
// Date: 2018-12-16
//
// This program embodies a single running agent, meaning that it operates one
// runescaupe client. It initially forks the necessary supporting processes, and
// then runs the main agent program itself.

#include <input-pipe.hpp>
#include <output-pipe.hpp>
#include <client.hpp>

#include <opencv2/opencv.hpp>

#include <condition_variable>
#include <iostream>
#include <string>
#include <thread>

#include <unistd.h>

const int width = 765;
const int height = 503;

const char* inputCommand = "ffmpeg -loglevel panic -video_size 765x503 -r 15\
	-f x11grab -draw_mouse 0 -i :0.0+817,18 -f rawvideo -pix_fmt bgr24 -an pipe:";

const char* outputCommand = "ffmpeg -loglevel panic -f rawvideo -pix_fmt bgr24\
	-s 765x503 -r 15 -i pipe:0 -f alsa -i pulse -f flv -ac 2 -ar 44100\
	-vcodec libx264 -g 30 -keyint_min 15 -b:v 1000k -minrate 1000k -maxrate 1000k\
	-pix_fmt yuv420p -s 1920x1080 -preset ultrafast -tune film\
	-acodec libmp3lame -threads 2 -strict normal -bufsize 1000k\
	\"rtmp://live.twitch.tv/app/live_180859114_OuXRYwGC6btzEdlBsLQdv9mT5UaF8F\"";

// multithreaded signaling
std::mutex fbMtx, frameMtx;
std::condition_variable cond;

int main() {
	switch(fork()) {
		case -1:
			std::cerr << "forking error" << std::endl;
			exit(1);
		case 0:
			std::cout << "forking" << std::endl;
			system("/home/mknight/Documents/ScapeNet/runescape.sh > /dev/null");
			exit(0);
	}

	InputPipe input(inputCommand);

	std::array<uint8_t, 3*width*height> rawbuffer, framebuffer;
	cv::Mat frame(height, width, CV_8UC3, framebuffer.data());

	// spin up a thread to continually grab incoming frames
	std::thread th([&]() {
		for (int frameNum = 0; true; frameNum++) {
			fbMtx.lock();
			input.read(rawbuffer.data(), 3, width*height);
			fbMtx.unlock();
			cond.notify_one();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	});

	cv::Rect borders(817, 18, width, height);
	Client::Create(borders, frame, frameMtx);

	for (int frameNum = 0; true; frameNum++) {
		std::unique_lock<std::mutex> lock(fbMtx);
		cond.wait(lock);
		frameMtx.lock();
		std::memcpy(framebuffer.data(), rawbuffer.data(), 3*height*width);
		frameMtx.unlock();
		lock.unlock();

	}
}
/*
	OutputPipe output(outputCommand);
	std::memcpy(outputFb.data(), inputFb.data(), 3*height*width);
	output.write(outputFb.data(), 3, width*height);
	*/
