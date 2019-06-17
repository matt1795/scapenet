// Runescape Player Class
//
// Author: Matthew Knight
// File Name: player.cpp
// Date: 2019-01-04
//
// This class implements a runescape player in RAII fashion, the constructor and
// destructor handle logging in and out. The client pointer acts as the
// interface to the game, and is assumed to be valid at all times since it is
// the one that manages the lifetime of the player.

#include <player.hpp>

Player::Player(const login_info_t& loginInfo, Client* client)
	: username(loginInfo.username)
	, password(loginInfo.password)
	, client(client)
	, startTime(std::chrono::steady_clock::now())
{
	std::cout << "New player logging in" << std::endl
		<< "username: " << username << std::endl
		<< "password: " << password << std::endl;

	client->leftClick(450, 300);
	client->type(username);

	client->leftClick(450, 285);
	client->type(password);

	client->leftClick(300, 340);
}

void Player::iterate() {}

login_info_t Player::getLoginInfo() {
	return { username, password };
}

std::chrono::seconds Player::playTime() {
	return std::chrono::duration_cast<std::chrono::seconds>(
		std::chrono::steady_clock::now() - startTime
	);
}

Player::~Player() {
	client->leftClick(642, 486);
	client->leftClick(642, 438);
	std::this_thread::sleep_for(std::chrono::seconds(5));
}
