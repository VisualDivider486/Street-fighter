#include "playerLeft.h"
#include "playerRight.h"
#include "graphics.h"
#include <iostream>
#include <vector>
#include "game.h"

//#include "game.h"
PlayerLeft::PlayerLeft(const Game& mygame) :GameObject(mygame)
{
}

void PlayerLeft::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_A)) //epeidh anoikoun sthn graphics ta SCANCODE
	{				
		pos_x1 -= speed * graphics::getDeltaTime() / 20.0f;//aksonas x
	}				
	if (graphics::getKeyState(graphics::SCANCODE_D)) 
	{
		pos_x1 += speed * graphics::getDeltaTime()/ 20.0f;//aksonas x
	}
	if (graphics::getKeyState(graphics::SCANCODE_W) || loopJumpLeft) 
	{
		if (pos_y1 <= CANVAS_HEIGHT_LEFT / 1.5f && goingUpLeft==true) {
			if (pos_y1 == CANVAS_HEIGHT_LEFT / 1.5f) {
				loopJumpLeft = true;
			}
			pos_y1 -= speed* graphics::getDeltaTime() / 15.0f; 
		}
		if (pos_y1 <= CANVAS_HEIGHT_LEFT / 2.6f || goingUpLeft==false) {
			goingUpLeft = false;
			pos_y1 += speed* graphics::getDeltaTime() / 15.0f;
			if (pos_y1 >= CANVAS_HEIGHT_LEFT / 1.5f) {
				goingUpLeft = true;
				loopJumpLeft = false;
			}
		}
	}
	if (graphics::getKeyState(graphics::SCANCODE_S)) {			//DEFENSE
		damage2Right = false;
	}
	if (!graphics::getKeyState(graphics::SCANCODE_S)) {          //CAN'T ATTACK WHILE DEFENDING
		if (graphics::getKeyState(graphics::SCANCODE_1) && !(graphics::getKeyState(graphics::SCANCODE_DOWN))) {			//ATTACK
			damage2Right = true;
			damageCaused2Right = 0.001f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_2) && !(graphics::getKeyState(graphics::SCANCODE_DOWN))) {			//ATTACK
			damage2Right = true;
			damageCaused2Right = 0.002f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_3) && !(graphics::getKeyState(graphics::SCANCODE_DOWN))) {			//ATTACK
			damage2Right = true;
			damageCaused2Right = 0.003f;
		}
	}
	
	if (pos_x1 <= CANVAS_WIDTH_LEFT/11.f) pos_x1 =CANVAS_WIDTH_LEFT /11.f;	//orizontio orio aristera
	if (pos_x1 >= CANVAS_WIDTH_LEFT /1.1f) pos_x1 = CANVAS_WIDTH_LEFT /1.1f;//orizontio orio deksia
	if (pos_y1 >= CANVAS_HEIGHT_LEFT /1.5f) pos_y1 = CANVAS_HEIGHT_LEFT /1.5f;//ka8eto orio katw

}

void PlayerLeft::draw()
{	
	graphics::Brush br1;
		
	if (graphics::getKeyState(graphics::SCANCODE_S)) {
		br1.texture = std::string(ASSET_PATH) + "defensePosLeft.png";
		br1.outline_opacity = 0.0f;//adiafano
		graphics::drawRect(pos_x1, pos_y1, 450, 280, br1);
		br1.texture = "";
	}
	else if (graphics::getKeyState(graphics::SCANCODE_1)) {
		br1.texture = std::string(ASSET_PATH) + "ArmKickPosLeft.png";
		br1.outline_opacity = 0.0f;//adiafano
		graphics::drawRect(pos_x1, pos_y1, 450, 280, br1);
		graphics::playSound(std::string(ASSET_PATH) + "boxer12Effect.mp3", 0.5f);
		br1.texture = "";
	}
	else if (graphics::getKeyState(graphics::SCANCODE_2)) {
		br1.texture = std::string(ASSET_PATH) + "lowKickPosLeft.png";
		br1.outline_opacity = 0.0f;//adiafano
		graphics::drawRect(pos_x1, pos_y1, 450, 280, br1);
		graphics::playSound(std::string(ASSET_PATH) + "boxer12Effect.mp3", 0.5f);
		br1.texture = "";
	}
	else if (graphics::getKeyState(graphics::SCANCODE_3)) {
		br1.texture = std::string(ASSET_PATH) + "punchPosLeft.png";
		br1.outline_opacity = 0.0f;//adiafano
		graphics::drawRect(pos_x1, pos_y1, 450, 280, br1);
		graphics::playSound(std::string(ASSET_PATH) + "punchEffect.mp3", 0.5f);
		br1.texture = "";
	}
	else {
		br1.texture = std::string(ASSET_PATH) + "normalPosLeft.png";
		br1.outline_opacity = 0.0f;//adiafano
		graphics::drawRect(pos_x1, pos_y1, 450, 280, br1);
		br1.texture = "";
	}



	if (game.getDebugMode()) {
		br1.outline_opacity = 1.0f;
		br1.texture = "";
		br1.fill_color[0] = 0.3f;
		br1.fill_color[1] = 1.0f;
		br1.fill_color[2] = 0.3f;
		br1.fill_opacity = 0.3f;

		br1.gradient = false;

		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br1);
		
	}
}

void PlayerLeft::init()
{
}

Disk PlayerLeft::getCollisionHull() const
{
	//kane to idio me x1 x2 y1 y2 h ftiakse nea playerRight!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Disk disk;
	disk.cx = pos_x1;
	disk.cy = pos_y1-20;
	disk.radius = 85.0f;
	return disk;
}