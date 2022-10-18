#pragma once
#include "playerLeft.h"
#include "playerRight.h"
#include <string>
#include <iostream>
class Game 
{
	typedef enum {STATUS_START,STATUS_PLAYING,STATUS_DRAW,STATUS_LEFT,STATUS_RIGHT} status_t;
	PlayerLeft* playerLeft = nullptr;//se periptwsh pou den exei dhmiourgh8ei o player
	PlayerRight* playerRight = nullptr;
	bool playerLeft_initialized = false;
	bool playerRight_initialized = false;
	bool checkCollision();
	bool debug_mode = true;
	status_t status=STATUS_START;

	void updateStartScreen();
	void updateLevelScreen();
	void drawStartScreeen();
	void drawLevelScreen();

	void updateDraw();
	void updateLeftWon();
	void updateRightWon();
	void drawDraw();
	void drawLeftWon();
	void drawRightWon();

	void questionPlayOrStop();

public:
	void setDebugMode(bool debug) { debug_mode = debug; }
	bool getDebugMode() const { return debug_mode; }
	void update();
	void draw();
	int iteration = 1;
	int minutes;
	int seconds;
	std::string background;
	void setMinutes(int min) { minutes = min; }
	void setSeconds(int sec) { seconds = sec; }
	void reduceSeconds();
	void changeMinutes();
	void runOutOfTime();
	void restartTime();
	std::string startClock(int minutes,int seconds,bool var);
	char sike;
	void init();//mporei na mhn xreiastei
	//Game();
	~Game();//destructor
	 
};