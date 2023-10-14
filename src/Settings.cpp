#include <cmath>

#include "Settings.h"

// player
const sf::Vector2f Settings::PLAYER_POS{12.5f, 9.5f};

// ray casting
const float Settings::SCREEN_DIST = (float)H_SCREEN_WIDTH / std::tan(H_FOV);

// colors
const sf::Color Settings::BG{30, 30, 30};

// paths
string Settings::ROOT_DIR = "D:\\Code\\C++\\DOOM v1\\";
string Settings::RES_DIR = ROOT_DIR + "res\\";
string Settings::FONTS_DIR = RES_DIR + "fonts\\";
string Settings::TEXTURES_DIR = RES_DIR + "textures\\";
string Settings::LEVELS_DIR = RES_DIR + "levels\\";