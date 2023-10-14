#pragma once

#include <string>
#include "SFML/Graphics.hpp"

using std::string;
using uint = unsigned int;

struct Settings
{
	// monitor
	static constexpr uint MONITOR_WIDTH = 1920;
	static constexpr uint MONITOR_HEIGHT = 1080;
	static constexpr uint H_MONITOR_WIDTH = MONITOR_WIDTH / 2;
	static constexpr uint H_MONITOR_HEIGHT = MONITOR_HEIGHT / 2;

	//screen
	static constexpr bool FULLSCREEN = true;
	static constexpr uint SCREEN_WIDTH = FULLSCREEN ? MONITOR_WIDTH : 1200;
	static constexpr uint SCREEN_HEIGHT = FULLSCREEN ? MONITOR_HEIGHT : 900;
	static constexpr uint H_SCREEN_WIDTH = SCREEN_WIDTH / 2;
	static constexpr uint H_SCREEN_HEIGHT = SCREEN_HEIGHT / 2;

	// level
	static int TILE_SIZE;

	// player
	static const sf::Vector2f PLAYER_POS;
	static float PLAYER_SPEED;

	// numbers
	static constexpr float PI = 3.141592653589793f;
	static constexpr float DOUBLE_PI = PI * 2.f;

	// ray casting
	static constexpr float FOV = PI / 3.f;
	static constexpr float H_FOV = FOV / 2.f;
	static constexpr int NUM_RAYS = SCREEN_WIDTH / 2;
	static constexpr int H_NUM_RAYS = NUM_RAYS / 2;
	static constexpr float DELTA_ANGLE = FOV / (float)NUM_RAYS;
	static constexpr int SCALE = SCREEN_WIDTH / NUM_RAYS;
	static const float SCREEN_DIST;

	// mouse
	static const float MOUSE_SENSETIVITY;
	static const int MAX_REL;

	// colors
	static const sf::Color BG;

	// paths
	static const string ROOT_DIR;
	static const string RES_DIR;
	static const string FONTS_DIR;
	static const string TEXTURES_DIR;
	static const string LEVELS_DIR;

	// other
	static constexpr uint TEXTURES_COUNT = 5;
	static const uint TEXTURE_SIZE;
};