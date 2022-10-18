#pragma once
#include "gameobject.h"
#include "config.h"
#include <iostream>
class PlayerLeft : public GameObject,public Collidable
{
	//jump for left player
	bool goingUpLeft = true;
	bool loopJumpLeft = false;
	float lifeLeft = 1.0f;

	//positions of players
	float speed = 7.0f;	//speed of players moving the fighters
	float pos_x1=CANVAS_WIDTH_LEFT/6.f, pos_y1=CANVAS_HEIGHT_LEFT/1.3f;		// first position of left player

public:
	bool damage2Right = false;
	float damageCaused2Right = 0.f;
public:
	PlayerLeft(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;

	float getPos_x1() { return pos_x1; }
	float getPos_y1() { return pos_y1; }
	float damageCaused2Left = 0.f;
	Disk  getCollisionHull() const  override;
	float getRemainingLife() { return lifeLeft; }
	void reduceLife(float amount) {
		lifeLeft = std::max<float>(0.0f, lifeLeft - amount);
	}
	//void deleteLeftPlayer();
};