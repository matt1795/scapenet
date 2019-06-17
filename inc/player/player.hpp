// Runescape Player Class
//
// Author: Matthew Knight
// File Name: player.hpp
// Date: 2018-12-14
//
// This class keeps the player state and controls actions taken by the user.

#pragma once

#include <opencv2/core.hpp>

class Player {
	cv::Point position;
	double direction;
	int health;
	int prayer;
	int energy;
	int specialAttack;
	int xp;
	Attack_t attackMode;
	// stats
	// equip
	// inventory
};
