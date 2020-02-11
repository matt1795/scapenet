// RuneScape Client
//
// Author: Matthew Knight
// File Name: client.hpp
// Date: 2018-12-28

#pragma once

#include <control/keyboard.hpp>
#include <control/mouse.hpp>
#include <player.hpp>

#include <opencv2/opencv.hpp>

#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>

struct login_info_t;
class Player;

class Client {
    cv::Rect borders;
    cv::Mat frame;
    Mouse mouse;
    Keyboard keyboard;
    std::mutex& mtx;
    std::queue<login_info_t> users;
    Player* activePlayer;

  public:
    Client(const cv::Rect& borders, const cv::Mat& frame, std::mutex& mtx);

    void iterate();

    void leftClick(int x, int y);

    void type(const std::string& text);

    static void Create(const cv::Rect& borders, const cv::Mat& frame,
                       std::mutex& mtx);
};
