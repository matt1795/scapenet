// HUD Class
//
// Author: Matthew Knight
// File Name: hud.hpp
// Date: 2018-12-14
//
// This class implements an abstraction of the user interface in runescape.

#pragma once

enum class Tab {
    Attack,
    Skills,
    Inventory,
    Equip,
    Buffs,
    Spells,
    Logout,
    Settings
};

class Hud {
    Tab active;

  public:
    void setTab(Tab tab);

    // TODO: figure out how we want to interact with the different
};
