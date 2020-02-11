// Runescape Player Class
//
// Author: Matthew Knight
// File Name: player.hpp
// Date: 2019-01-04
//
// This class implements a runescape player in RAII fashion, the constructor and
// destructor handle logging in and out. The client pointer acts as the
// interface to the game, and is assumed to be valid at all times since it is
// the one that manages the lifetime of the player.

#pragma once

#include <client.hpp>

#include <chrono>
#include <string>

struct login_info_t {
    std::string username;
    std::string password;
};

class Client;

class Player {
    std::string username;
    std::string password;
    std::chrono::steady_clock::time_point startTime;
    Client* client;

  public:
    Player(const login_info_t& loginInfo, Client* client);

    ~Player();

    void iterate();

    login_info_t getLoginInfo();

    std::chrono::seconds playTime();
};
