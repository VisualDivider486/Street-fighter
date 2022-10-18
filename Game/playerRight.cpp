#include "playerLeft.h"
#include "playerRight.h"
#include "graphics.h"
#include <iostream>
#include <vector>
#include "game.h"
PlayerRight::PlayerRight(const Game& mygame)
	:GameObject(mygame)
{
}

void PlayerRight::update() {
	if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {

		pos_x2 -= speed * graphics::getDeltaTime() / 20.0f;//aksonas x
	}
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		pos_x2 += speed * graphics::getDeltaTime() / 20.0f;//aksonas x
	}
	if (graphics::getKeyState(graphics::SCANCODE_UP) || loopJumpRight)
	{
		if (pos_y2 <= CANVAS_HEIGHT_RIGHT / 1.5f && goingUpRight == true) {
			if (pos_y2 == CANVAS_HEIGHT_RIGHT / 1.5f) {
				loopJumpRight = true;
			}
			pos_y2 -= speed * graphics::getDeltaTime() / 15.0f;
		}
		if (pos_y2 <= CANVAS_HEIGHT_RIGHT / 2.6f || goingUpRight == false) {
			goingUpRight = false;
			pos_y2 += speed * graphics::getDeltaTime() / 15.0f;
			if (pos_y2 >= CANVAS_HEIGHT_RIGHT / 1.5f) {
				goingUpRight = true;
				loopJumpRight = false;
			}
		}
	}
	
	if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {//GUARD
		damage2Left = false;
		//guard
	}
	if (!graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		if (graphics::getKeyState(graphics::SCANCODE_J) && !(graphics::getKeyState(graphics::SCANCODE_S))) {//ATTACK
			damage2Left = true;
			damageCaused2Left = 0.001f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_K) && !(graphics::getKeyState(graphics::SCANCODE_S))) {//ATTACK
			damage2Left = true;
			damageCaused2Left = 0.002f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_L) && !(graphics::getKeyState(graphics::SCANCODE_S))) {//ATTACK
			damage2Left = true;
			damageCaused2Left = 0.003f;
		}
	}

	if (pos_x2 <= CANVAS_WIDTH_RIGHT / 11.f) pos_x2 = CANVAS_WIDTH_RIGHT / 11.f;//left player settings to not exit the image
	if (pos_x2 >= CANVAS_WIDTH_RIGHT / 1.1f) pos_x2 = CANVAS_WIDTH_RIGHT / 1.1f;
	if (pos_y2 >= CANVAS_HEIGHT_RIGHT / 1.5f) pos_y2 = CANVAS_HEIGHT_RIGHT / 1.5f;
}

void PlayerRight::draw(){

	graphics::Brush br;
	
	if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		br.texture = std::string(ASSET_PATH) + "defensePosRight.png";
		br.outline_opacity = 0.0f;//adiafano

		graphics::drawRect(pos_x2, pos_y2, 450, 280, br);

		br.texture = "";
	}
	else if (graphics::getKeyState(graphics::SCANCODE_J)) {
		br.texture = std::string(ASSET_PATH) + "sideKickPosRight.png";
		br.outline_opacity = 0.0f;//adiafano
		graphics::drawRect(pos_x2, pos_y2, 450, 280, br);
		graphics::playSound(std::string(ASSET_PATH) + "kickEffect.mp3", 0.5f);
		br.texture = "";
	}
	else if (graphics::getKeyState(graphics::SCANCODE_K)) {
		br.texture = std::string(ASSET_PATH) + "punchPosRight.png";
		br.outline_opacity = 0.0f;//adiafano

		graphics::drawRect(pos_x2, pos_y2, 450, 280, br);
		graphics::playSound(std::string(ASSET_PATH) + "punchEffect.mp3", 0.5f);
		br.texture = "";
	}
	else if (graphics::getKeyState(graphics::SCANCODE_L)) {
		br.texture = std::string(ASSET_PATH) + "LegKickPosRight.png";
		br.outline_opacity = 0.0f;//adiafano
		graphics::drawRect(pos_x2, pos_y2, 450, 280, br);
		graphics::playSound(std::string(ASSET_PATH) + "kickEffect.mp3", 0.5f);
		br.texture = "";
	}
	else {
		br.texture = std::string(ASSET_PATH) + "normalPosRight.png";
		br.outline_opacity = 0.0f;//adiafano

		graphics::drawRect(pos_x2, pos_y2, 450, 280, br);

		br.texture = "";
	}

	if (game.getDebugMode()) {
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;

		br.gradient = false;

		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}
}

void PlayerRight::init()
{

}

Disk PlayerRight::getCollisionHull() const
{
	//kane to idio me x1 x2 y1 y2 h ftiakse nea playerRight!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Disk disk;
	disk.cx = pos_x2;
	disk.cy = pos_y2-20;
	disk.radius = 85.0f;
	return disk;
}