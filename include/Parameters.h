#pragma once

// Game Parameters - Could be read from a file in the future

// Debug
struct DebugFlags {
	bool debug = false;
	bool debugWindow = false;
	bool isImmortal = false;
	bool drawFPS = true;
	bool logPlayerControl = false;
	bool logCollisions = false;
	bool logEntityUpdate = false;
	bool logGameStateChange = false;
	bool allowSkipLevel = true;
	bool allowAddLives = true;
	bool allowInstantKill = true;
};

// General
const unsigned int windowWidth{ 800 };
const unsigned int windowHeight{ 600 };
const std::string windowTitle{ "Cinoid 1.0" };
const float BaseColorRed = 255.f;
const float BaseColorGreen = 255.f;
const float BaseColorBlue = 255.f;
const float BackgroundColorRed = 0.f;
const float BackgroundColorGreen = 0.f;
const float BackgroundColorBlue = 0.f;
const int initialLifes{ 3 };
const std::string startScreenImage {"Title.png" };
const std::string scoreBackdropImage { "ScoreScreen.jpg" };
const std::string endGameBackdropImage { "Endgame.jpg" };

// Tiles
const int TilesXCount{ 11 };
const int TilesYCount{ 4 };
const float TileWidth{ 60.f };
const float TileHeight{ 20.f };
const float initialTileWidth{ 60.f };
const float initialTileHeight{ 20.f };
const int initialScore{ 1000 };
const float TileColorRed = 255.f;
const float TileColorGreen = 0.f;
const float TileColorBlue = 0.f;

// Ball
const float initialBallSpeed{ 5.f };
const float initialBallRadius{ 8.f };
const float BallColorRed = 255.f;
const float BallColorGreen = 0.f;
const float BallColorBlue = 0.f;

// PlayerPaddle
const float initialPlayerPaddleWidth{ 90.f };
const float initialPlayerPaddleHeight{ 20.f };
const float initialPlayerPaddleSpeed{ 8.f };
const float PlayerColorRed = 255.f;
const float PlayerColorGreen = 0.f;
const float PlayerColorBlue = 255.f;

// Levels
const std::string levelPath{ "Levels\\" };
const std::string levelBackdropImage{ "Level.jpg" };

// Assets
const std::string assetPath { "Assets\\" };
const std::string fontFile { "Dosis-Medium.ttf" };
const std::string scorebarfontFile { "Dosis-Medium.ttf" };

// Level list
//const std::vector<std::string> levelList{
//	std::string{ "Level 1" },
//	std::string{ "Level 2" },
//};

const std::vector<std::string> levelList{
	std::string{ "Level 1" },
	std::string{ "Level 2" },
	std::string{ "Level 3" },
	std::string{ "Level 4" },
	std::string{ "Level 5" },
	std::string{ "Level 6" },
	std::string{ "Level 7" },
	std::string{ "Level 8" },
	std::string{ "Level 9" },
	std::string{ "Level 10" },
	std::string{ "Level 11" },
	std::string{ "Level 12" },
	std::string{ "Level 13" },
	std::string{ "Level 14" }
};