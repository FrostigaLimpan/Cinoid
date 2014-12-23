#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
//#include "cinder/Camera.h"
#include "cinder/Text.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

#include "Parameters.h"
#include "BaseBlock.h"
#include "Ball.h"
#include "PlayerPaddle.h"
#include "GameState.h"
#include "Tile.h"
#include "Level.h"
#include "CollisionDetection.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace Cinoid;

class CinoidApp : public AppNative {
private:
	GameState state;
	unique_ptr<Ball> ball;
	unique_ptr<PlayerPaddle> player;
	std::vector<Tile> tiles;
	int lifes{ initialLifes };
	int currentScore{ 0 };
	unsigned int currentLevel = 0;
	std::string currentLevelName;
	gl::Texture startScreen;
	gl::Texture levelBackdrop;
	gl::Texture scoreBackdrop;
	gl::Texture endGameBackdrop;
	gl::TextureFontRef fpsFont;
	gl::TextureFontRef scoreFont;
	//CameraPersp	mCam;
	DebugFlags debugFlags;
	Vec2f levelTextBox;

	void drawStartScreen();
	void drawEndScreen();
	void drawScoreScreen();
	void drawPlayer();
	void drawTiles();
	void drawBall();
	void drawLevelBackground();
	bool loadLevel();
	void removeDestroyedTiles();
	void testForCollisions();
	void checkDebugFlags();
	void writeDebugFlags();

public:
	void setup();
	void prepareSettings(Settings *settings);
	void keyDown(KeyEvent evt);
	void keyUp(KeyEvent evt);
	void update();
	void draw();
	//void resize();

	bool movingLeft = false;
	bool movingRight = false;

};

void CinoidApp::prepareSettings(Settings *settings) {

	checkDebugFlags();

	settings->setWindowSize(windowWidth, windowHeight);
	settings->setFrameRate(60.0f);
	if (debugFlags.debugWindow)
		settings->enableConsoleWindow();
	settings->setResizable(false);
	settings->setTitle(windowTitle);
}

void CinoidApp::setup()
{
	startScreen = loadImage(loadAsset(startScreenImage));
	scoreBackdrop = loadImage(loadAsset(scoreBackdropImage));
	endGameBackdrop = loadImage(loadAsset(endGameBackdropImage));

	Font mFont = Font(loadAsset(fontFile), 16);
	scoreFont = gl::TextureFont::create(mFont);

	if (debugFlags.drawFPS)
		fpsFont = gl::TextureFont::create(mFont);

	ball = make_unique<Ball>(windowWidth / 2.0f, windowHeight / 2.0f, initialBallSpeed, windowHeight, windowWidth);
	player = make_unique<PlayerPaddle>(windowWidth / 2.0f - initialPlayerPaddleWidth / 2.f, windowHeight - 50.0f, initialPlayerPaddleWidth, initialPlayerPaddleHeight);
	state.currentState = State::STARTSCREEN;

	if (debugFlags.debugWindow)
		writeDebugFlags();
}

//void CinoidApp::resize()
//{
//}

void CinoidApp::keyDown(KeyEvent evt) {

	if (evt.getCode() == KeyEvent::KEY_RIGHT)
		movingRight = true;

	if (evt.getCode() == KeyEvent::KEY_LEFT)
		movingLeft = true;

}

void CinoidApp::keyUp(KeyEvent evt) {

	if (evt.getCode() == KeyEvent::KEY_SPACE)
		switch (state.currentState) {
		case State::STARTSCREEN:
			lifes = initialLifes;
			currentLevel = 0;
			loadLevel();
			ball->resetBall(windowWidth / 2.0f, windowHeight / 2.0f, initialBallSpeed);
			state.currentState = State::PAUSED;
			break;
		case State::SCORESCREEN:
			if (!loadLevel()) {
				state.currentState = State::ENDGAME;
			}
			else {
				ball->resetBall(windowWidth / 2.0f, windowHeight / 2.0f, initialBallSpeed);
				player->resetPaddle(windowWidth / 2, windowHeight - 50);
				state.currentState = State::PAUSED;
			}
			break;
		case State::ENDGAME:
			state.currentState = State::STARTSCREEN;
			break;
		case State::PAUSED:
			state.currentState = State::RUNNING;
			break;
	}

	if (evt.getCode() == KeyEvent::KEY_p && state.currentState == State::PAUSED)
		state.currentState = State::RUNNING;
	else if (evt.getCode() == KeyEvent::KEY_p && state.currentState == State::RUNNING)
		state.currentState = State::PAUSED;

	if (evt.getCode() == KeyEvent::KEY_s && state.currentState == State::RUNNING && debugFlags.allowSkipLevel) {
		if (debugFlags.debugWindow)
			console() << "[DEBUG] Skipping lvl." << std::endl;
		state.currentState = State::SCORESCREEN;
	}

	if (evt.getCode() == KeyEvent::KEY_l && state.currentState == State::RUNNING && debugFlags.allowAddLives) {
		if (debugFlags.debugWindow)
			console() << "[DEBUG] Adding lifes." << std::endl;
		lifes = 999;
	}

	if (evt.getCode() == KeyEvent::KEY_k && state.currentState == State::RUNNING && debugFlags.allowInstantKill) {
		if (debugFlags.debugWindow)
			console() << "[DEBUG] Instant kill." << std::endl;
		lifes = 0;
	}


	if (evt.getCode() == KeyEvent::KEY_RIGHT)
		movingRight = false;

	if (evt.getCode() == KeyEvent::KEY_LEFT)
		movingLeft = false;

}

void CinoidApp::update()
{

	if (state.currentState == State::RUNNING || state.currentState == State::PAUSED) {
		if (lifes <= 0)
			state.currentState = State::ENDGAME;
	}

	if (state.currentState == State::RUNNING) {

		if (tiles.empty())
			state.currentState = State::SCORESCREEN;

		ball->update();

		if (movingLeft) {
			player->moveLeft();
			if (debugFlags.logPlayerControl)
				console() << "[DEBUG] Moving left" << endl;
		}

		if (movingRight) {
			player->moveRight();
			if (debugFlags.logPlayerControl)
				console() << "[DEBUG] Moving right" << endl;
		}

		if (debugFlags.logEntityUpdate)
			console() << "Update entities" << endl;

		testForCollisions();
		removeDestroyedTiles();

	}
}

void CinoidApp::draw()
{
	gl::clear(Color(BackgroundColorRed, BackgroundColorGreen, BackgroundColorBlue));

	if (state.currentState == State::STARTSCREEN)
		drawStartScreen();
	else if (state.currentState == State::SCORESCREEN)
		drawScoreScreen();
	else if (state.currentState == State::ENDGAME)
		drawEndScreen();
	else if (state.currentState == State::RUNNING || state.currentState == State::PAUSED) {
		drawLevelBackground();
		drawBall();
		drawPlayer();
		drawTiles();
		scoreFont->drawString("Level: " + currentLevelName, { app::getWindowWidth() / 2.f - levelTextBox.length() /2.f, app::getWindowHeight() - 10.0f });
		scoreFont->drawString("Lives: " + std::to_string(lifes), { 10.0f, app::getWindowHeight() - 10.0f });
		scoreFont->drawString("Score: " + std::to_string(currentScore), { app::getWindowWidth() - 150.f, app::getWindowHeight() - 10.0f });
		if (state.currentState == State::PAUSED)
			scoreFont->drawString("Game Paused", Vec2f(app::getWindowWidth() / 2.f - 50.f, app::getWindowHeight() / 2.f));
	}

	if (debugFlags.drawFPS && (state.currentState == State::RUNNING || state.currentState == State::PAUSED)) {
		gl::color(Color::white());
		fpsFont->drawString(std::to_string(floor(getAverageFps())) + " FPS", Vec2f(10, 10 + fpsFont->getDescent()));
	}
}

void CinoidApp::drawPlayer() {
	gl::color(player->getColor());
	gl::drawSolidRect(player->getShape(), false);
	gl::color(BaseColorRed, BaseColorGreen, BaseColorBlue);

}

void CinoidApp::drawTiles() {
	for (auto& tile : tiles) {
		gl::color(tile.getColor());
		gl::drawSolidRect(tile.getShape(), false);
	}

	gl::color(BaseColorRed, BaseColorGreen, BaseColorBlue);
}

void CinoidApp::drawBall() {
	auto shape = ball->getShape();
	gl::color(ball->getColor());
	gl::drawSolidCircle(shape.first, shape.second);
	gl::color(BaseColorRed, BaseColorGreen, BaseColorBlue);
}

void CinoidApp::drawLevelBackground() {
	gl::draw(levelBackdrop, getWindowBounds());
}

void CinoidApp::drawStartScreen() {
	gl::draw(startScreen, getWindowBounds());
}

void CinoidApp::drawEndScreen() {
	gl::draw(endGameBackdrop, getWindowBounds());
	//gl::drawStringCentered("Game Over", app::getWindowCenter());
}

void CinoidApp::drawScoreScreen() {
	gl::draw(scoreBackdrop, getWindowBounds());
	gl::drawStringCentered("Your score: " + std::to_string(currentScore), app::getWindowCenter());
}

bool CinoidApp::loadLevel() {
	if (currentLevel >= levelList.size()) {
		return false;
	}

	Level lvl{};
	lvl.loadLevel(std::string(levelList[currentLevel]));
	tiles = lvl.getTiles();
	currentLevelName = lvl.getName();
	levelBackdrop = loadImage(loadAsset(lvl.getBackdropImage()));

	levelTextBox = scoreFont->measureString("Level: " + currentLevelName);

	++currentLevel;
	return true;
}

void CinoidApp::removeDestroyedTiles() {
	tiles.erase(
		std::remove_if(std::begin(tiles), std::end(tiles),
		[](const Tile& tile) { return tile.isDestroyed; }),
		std::end(tiles)
		);
};

void CinoidApp::testForCollisions() {

	if (!debugFlags.isImmortal) {
		if (testForBottomCollision(*ball)) {
			--lifes;
			ball->resetBall(windowWidth / 2.0f, windowHeight / 2.0f, initialBallSpeed);
			player->resetPaddle(windowWidth / 2, windowHeight - 50);

			state.currentState = State::PAUSED;
			return;
		}
	}

	testForPlayerCollision((*player), (*ball));

	for (auto& tile : tiles) {
		testForTileCollision(tile, (*ball));
		if (tile.isDestroyed)
			currentScore += tile.score;
	}

};

void CinoidApp::checkDebugFlags() {
	if (!debugFlags.debug) {
		debugFlags.allowAddLives = false;
		debugFlags.allowSkipLevel = false;
		debugFlags.debugWindow = false;
		debugFlags.drawFPS = false;
		debugFlags.isImmortal = false;
		debugFlags.logCollisions = false;
		debugFlags.logEntityUpdate = false;
		debugFlags.logGameStateChange = false;
		debugFlags.logPlayerControl = false;
		debugFlags.allowInstantKill = false;
	}
}

void CinoidApp::writeDebugFlags() {
	if (debugFlags.debugWindow)
		console() << "[DEBUG] Debug mode enabled" << std::endl;
	if (debugFlags.debugWindow)
		console() << "[DEBUG] Immortal mode: " << std::to_string(debugFlags.isImmortal) << std::endl;
	if (debugFlags.debugWindow)
		console() << "[DEBUG] Allow add life mode: " << std::to_string(debugFlags.allowAddLives) << std::endl;
	if (debugFlags.debugWindow)
		console() << "[DEBUG] Allow skip level mode: " << std::to_string(debugFlags.allowSkipLevel) << std::endl;
	if (debugFlags.debugWindow)
		console() << "[DEBUG] Allow instant kill mode: " << std::to_string(debugFlags.allowInstantKill) << std::endl;
}

CINDER_APP_NATIVE(CinoidApp, RendererGl)
