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
	static constexpr int TILE_SIZE = 50;
	static constexpr int LEVEL_WIDTH = 38;
	static constexpr int LEVEL_HEIGHT = 22;

	// player
	static const sf::Vector2f PLAYER_POS;
	static constexpr float PLAYER_SPEED = 5.f;

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
	static constexpr int MAX_DEPTH = 20;
	static const float SCREEN_DIST;

	// mouse
	static constexpr float MOUSE_SENSETIVITY = 0.2f;
	static constexpr int MAX_REL = 50;

	// fps
	static constexpr int FPS = 60;

	// colors
	static const sf::Color BG;

	// paths
	static string ROOT_DIR;
	static string RES_DIR;
	static string FONTS_DIR;
	static string TEXTURES_DIR;
	static string LEVELS_DIR;

	// other
	static constexpr int TEXTURES_COUNT = 5;
	static constexpr uint TEXTURE_SIZE = 1024;
};