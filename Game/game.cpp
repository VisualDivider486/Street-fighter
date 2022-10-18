#include "game.h"
#include "graphics.h"
#include "config.h"
#include <iostream>
#include "playerLeft.h"
#include "playerRight.h"
#include "windows.h"
bool Game::checkCollision()
{////////////////////////////////
	if (!playerLeft)
		return false;
	if(!playerRight)
		return false;
	Disk d1 = playerLeft->getCollisionHull();
	Disk d2 = playerRight->getCollisionHull();
	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if ((sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) && playerLeft->damage2Right) {
		playerLeft->damage2Right = false;
		//std::cout <<playerLeft->damageCaused2Right;//meiwntai zwh deksia
		playerLeft->reduceLife(playerLeft->damageCaused2Right);
		//playerRight->reduceLife(playerLeft->damageCaused2Right);
		return true;
	}
	else if ((sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) && playerRight->damage2Left) {
		playerRight->damage2Left = false;
		//std::cout << playerRight->damageCaused2Left;//meiwntai zwh deksia
		playerRight->reduceLife(playerRight->damageCaused2Left);
		return true;
	}
	else {
		return false;
	}
}
void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_1) || graphics::getKeyState(graphics::SCANCODE_2) || graphics::getKeyState(graphics::SCANCODE_3)) {
		status = STATUS_PLAYING;
		setMinutes(2);

		if (graphics::getKeyState(graphics::SCANCODE_1)) {
			background = "arena.png";
		}
		else if (graphics::getKeyState(graphics::SCANCODE_2)) {
			background = "marsBg.png";
		}
		else if (graphics::getKeyState(graphics::SCANCODE_3)) {
			background = "japan.png";
		}
	}
}
void Game::updateLevelScreen()
{
	if (playerLeft && playerLeft->getRemainingLife() == 0.f) {
		status = STATUS_LEFT;
		playerLeft->reduceLife(-1.f);

		delete playerRight;
		playerRight = nullptr;
		playerRight = new PlayerRight(*this);

		//playerRight->reduceLife(1.f);

		delete playerLeft;
		playerLeft = nullptr;
		playerLeft = new PlayerLeft(*this);
	}
	if (playerRight && playerRight->getRemainingLife() == 0.f) {
		status = STATUS_RIGHT;
		playerRight->reduceLife(1.f);

		delete playerLeft;
		playerLeft = nullptr;
		playerLeft= new PlayerLeft(*this);

		//playerLeft->reduceLife(-1.f);

		delete playerRight;
		playerRight = nullptr;
		playerRight = new PlayerRight(*this);
	}
	if (graphics::getGlobalTime() > 1000 && playerLeft_initialized == false) {
		playerLeft = new PlayerLeft(*this);
		playerLeft_initialized = true;
	}
	if (graphics::getGlobalTime() > 1000 && playerRight_initialized == false) {
		playerRight = new PlayerRight(*this);
		playerRight_initialized = true;
	}
	if (playerLeft)
		playerLeft[0].update();
	if (playerRight)
		playerRight[0].update();


	checkCollision();
	
}
void Game::drawStartScreeen()
{
	graphics::Brush br;
	char info[100];
	sprintf_s(info, "Enter :  1 for Colloseum arena");
	graphics::drawText(CANVAS_WIDTH_LEFT / 5, CANVAS_HEIGHT_LEFT / 4, 30, info, br);

	sprintf_s(info, "             2 for Mars arena ");
	graphics::drawText(CANVAS_WIDTH_LEFT / 4, CANVAS_HEIGHT_LEFT / 3, 30, info, br);

	sprintf_s(info, "    3 Japan arena ");
	graphics::drawText(CANVAS_WIDTH_LEFT / 3.4, CANVAS_HEIGHT_LEFT / 2.4f, 30, info, br);




}
void Game::drawLevelScreen()
{
		graphics::Brush br;
		br.texture = std::string(ASSET_PATH) + background;
		br.outline_opacity = 0.0f;
		graphics::drawRect(CANVAS_WIDTH_RIGHT / 2, CANVAS_HEIGHT_RIGHT / 2, CANVAS_WIDTH_RIGHT, CANVAS_HEIGHT_RIGHT, br);
		int globalTime = (int)graphics::getGlobalTime();
		std::cout << "minutes :" << minutes << std::endl;
		std::cout << "seconds: " << seconds << std::endl;
		changeMinutes();
		if (globalTime > (1000 * iteration)) {
			reduceSeconds();
			std::string info = startClock(minutes, seconds, true);
			graphics::drawText(CANVAS_WIDTH_LEFT / 2.18f, CANVAS_HEIGHT_LEFT / 12, 30, info, br);
		}
		else {
			std::string info = startClock(minutes, seconds, false);
			graphics::drawText(CANVAS_WIDTH_LEFT / 2.18f, CANVAS_HEIGHT_LEFT / 12, 30, info, br);
		}
		if (playerLeft)
			playerLeft->draw();
		if (playerRight)
			playerRight->draw();

		float player_lifeLeft = playerLeft ? playerLeft->getRemainingLife() : 0.f;
		float player_lifeRight = playerRight ? playerRight->getRemainingLife() : 0.f;

		br.outline_opacity = 0.0f;
		br.fill_color[0] = 1.f;
		br.fill_color[1] = 0.2f;
		br.fill_color[2] = 0.2f;
		br.texture = "";

		br.fill_secondary_color[0] = 0.2f;
		br.fill_secondary_color[1] = 0.2f;
		br.fill_secondary_color[2] = 1.0f;

		br.gradient = true;
		br.gradient_dir_u = 1.0f;
		br.gradient_dir_v = 0.0f;

		graphics::drawRect(CANVAS_WIDTH_LEFT - 220 - ((1.f - player_lifeLeft) * 380 / 2), 30, player_lifeLeft * 380, 20, br);
		graphics::drawRect(CANVAS_WIDTH_LEFT - 590 - player_lifeRight * 380 / 2, 30, player_lifeRight * 380, 20, br);
		if (playerLeft != nullptr) 
		br.outline_opacity = 1.0f;
		br.gradient = false;
		br.fill_opacity = 0.0f;

		graphics::drawRect(CANVAS_WIDTH_LEFT - 220, 30, 380, 20, br);
		graphics::drawRect(CANVAS_WIDTH_LEFT - 780, 30, 380, 20, br);
}
void Game::updateDraw()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
		restartTime();
	}
	else if (graphics::getKeyState(graphics::SCANCODE_0)) {
		exit(0);
	}
}
void Game::updateLeftWon()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
		restartTime();
	}
	else if (graphics::getKeyState(graphics::SCANCODE_0)) {
		exit(0);
	}
}
void Game::updateRightWon()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
		restartTime();
	}
	else if (graphics::getKeyState(graphics::SCANCODE_0)) {
		exit(0);
	}
}
void Game::drawDraw()
{
	graphics::Brush br;
	char info[40];
	sprintf_s(info, "   NOBODY WON YOU RUN OUT OF TIME");
	graphics::drawText(CANVAS_WIDTH_LEFT / 5, CANVAS_HEIGHT_LEFT / 2, 30, info, br);
	questionPlayOrStop();
}
void Game::drawLeftWon()
{
	graphics::Brush br;
	char info[40];
	sprintf_s(info, "    CONGRATULATIONS LEFT PLAYER WON!!");
	graphics::drawText(CANVAS_WIDTH_LEFT / 5, CANVAS_HEIGHT_LEFT / 2, 30, info, br);
	questionPlayOrStop();
}
void Game::drawRightWon()
{
	graphics::Brush br;
	char info[40];
	sprintf_s(info, "    CONGRATULATIONS RIGHT PLAYER WON!!");
	graphics::drawText(CANVAS_WIDTH_LEFT / 5, CANVAS_HEIGHT_LEFT / 2, 30, info, br);
	questionPlayOrStop();
}
void Game::questionPlayOrStop()
{
	graphics::Brush br;
	char info[40];
	sprintf_s(info, "press ENTER to continue or 0 to stop");
	graphics::drawText(CANVAS_WIDTH_LEFT / 5, CANVAS_HEIGHT_LEFT / 1.4f, 30, info, br);
}
void Game::update()
{
	if (status == STATUS_START) {
		updateStartScreen();
	}
	else if(status==STATUS_PLAYING){
		updateLevelScreen();
	}
	else {
		if (status == STATUS_LEFT) {
			updateLeftWon();
		}
		else if (status == STATUS_RIGHT) {
			updateRightWon();
		}
		else {
			updateDraw();
		}
	}
	
}

void Game::draw()
{
	if (status == STATUS_START) {
		drawStartScreeen();
	}
	else if(status==STATUS_PLAYING){
		drawLevelScreen();
	}
	else {
		if (status == STATUS_LEFT) {
			drawLeftWon();
		}
		else if (status == STATUS_RIGHT) {
			drawRightWon();
		}
		else {
			drawDraw();
		}
	}
}

void Game::reduceSeconds()
{
	seconds--;
}

void Game::changeMinutes()
{
	if (seconds ==-1) {
		seconds = 59;
		if (--minutes == -1) {
			runOutOfTime();
			status = STATUS_DRAW;
		}
	}
}


void Game::runOutOfTime()
{
	playerLeft->reduceLife(-1.f);
	delete playerRight;
	playerRight = nullptr;
	playerRight = new PlayerRight(*this);

	playerRight->reduceLife(1.f);
	delete playerLeft;
	playerLeft = nullptr;
	playerLeft = new PlayerLeft(*this);

	restartTime();
}
void Game::restartTime()
{
	setMinutes(2);
	setSeconds(0);
}
std::string Game::startClock(int minutes, int seconds,bool var)
{
		if (var) {
			iteration++;
		}
		if (seconds < 10) {
			std::string min = std::to_string(minutes);
			std::string sec = std::to_string(seconds);
			std::string time = min + ":0" + sec;
			std::cout << time << std::endl;
			return time;
		}
		else {
			std::string min = std::to_string(minutes);
			std::string sec = std::to_string(seconds);
			std::string time = min + ":" + sec;
			std::cout << time << std::endl;
			return time;
		}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "roboticFont.ttf");
	graphics::playSound(std::string(ASSET_PATH) + "bgMusic.mp3", 0.5f,true);
}

//Game::Game()
//{
//}

Game::~Game()
{
	if (playerLeft)
	{
		delete playerLeft;
	}
	if (playerRight) 
	{
		delete playerRight;
	}
}
