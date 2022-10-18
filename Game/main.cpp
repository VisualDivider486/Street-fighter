#include "graphics.h"
#include "game.h"
#include "config.h"
#include <iostream>
#include <string>
//#include "playerLeft.h";

void update(float ms)
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->update();
}

// The window content drawing function.
void draw()
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->draw();
}

int main()
{
    Game mygame;
    //

    graphics::createWindow(WINDOW_WIDTH_RIGHT, WINDOW_HEIGHT_RIGHT, "Game");

    graphics::setUserData(&mygame);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH_RIGHT, CANVAS_HEIGHT_RIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    mygame.init();
    
    mygame.setDebugMode(false);
    graphics::startMessageLoop();
    return 0;
}