#include <cmath>

#include "Settings.h"

// level
int Settings::TILE_SIZE = 20;

// player
const sf::Vector2f Settings::PLAYER_POS{12.5f, 9.5f};

float Settings::PLAYER_SPEED = 5.f;

// ray casting
const float Settings::SCREEN_DIST = (float)H_SCREEN_WIDTH / std::tan(H_FOV);

// mouse
const float Settings::MOUSE_SENSETIVITY = 0.2f;
const int Settings::MAX_REL = 50;

// colors
const sf::Color Settings::BG{30, 30, 30};

// paths
const string Settings::ROOT_DIR = "D:\\Code\\C++\\DOOM v1\\";
const string Settings::RES_DIR = ROOT_DIR + "res\\";
const string Settings::FONTS_DIR = RES_DIR + "fonts\\";
const string Settings::TEXTURES_DIR = RES_DIR + "textures\\";
const string Settings::LEVELS_DIR = RES_DIR + "levels\\";

// other
const uint Settings::TEXTURE_SIZE = 2048;