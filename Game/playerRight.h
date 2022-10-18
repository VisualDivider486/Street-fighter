#pragma once
#include "gameobject.h"
#include "config.h"
#include <iostream>
class PlayerRight :public GameObject,public Collidable
{
	bool goingUpRight = true;
	bool loopJumpRight = false;
	float lifeRight = 1.f;

	float speed = 7.f;
	float pos_x2 = CANVAS_WIDTH_RIGHT / 1.2f, pos_y2 = CANVAS_HEIGHT_RIGHT / 1.3f; //location x,y 
public:
	bool damage2Left = false;
	float damageCaused2Left = 0.f;
public:
	 PlayerRight(const class Game& mygame);
	 float getPos_x2() { return pos_x2; }
	 float getPos_y2() { return pos_y2; }
	 void update() override;
	 void draw() override;
	 void init() override;

	 Disk  getCollisionHull() const  override;
	 float getRemainingLife() { return lifeRight; }
	 void reduceLife(float amount) {
		 lifeRight = std::max<float>(0.0f, lifeRight - amount);
	 }
};