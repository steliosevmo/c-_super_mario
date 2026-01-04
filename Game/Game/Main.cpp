#include "sgg/graphics.h"
#include <iostream>
#include <stdio.h>
#define SETCOLOR(c,r,g,b){c[0]=r,c[1]=g,c[2]=b;}
#include <string>
#include "GameState.h"


void init() {

	GameState::getInstance()->init();
	
}

void draw() {
	GameState::getInstance()->draw();
	
}

void update(float dt) {
	GameState::getInstance()->update(dt);
		
}
int main(int argc,char ** argv) {
	graphics::createWindow(500, 500,"Stage1");
	init();
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	
	graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();
	return 0;
}