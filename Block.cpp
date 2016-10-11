#include "Common.h"
#include "Tetris.h"

extern Game tetrisGame;

Block::Block(){
    posX = NUM_BLOCKS_X/2;
    posY = NUM_BLOCKS_Y-1;
}

Block::~Block(){
}

void Block::Draw() const {
    int left = posX * (BLOCK_SIZE + BLOCK_SPACING);
    //int left = posX * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
    int right = left + BLOCK_SIZE;
    int bottom = posY * (BLOCK_SIZE + BLOCK_SPACING);
    int top = bottom + BLOCK_SIZE;

    glBegin(GL_QUADS);
    glColor3d(1,1,1);
    glVertex3f(left, top, 0);
    glVertex3f(right, top, 0);
    glVertex3f(right, bottom, 0);
    glVertex3f(left, bottom, 0);
    glEnd();
}

bool Block::CanRotate(const int figureX, const int figureY) const {
    int offsetX = posX - figureX;
    int offsetY = posY - figureY;

    if(!offsetX && offsetY){
	return true;
    }

    int nextPosX = figureX - offsetY;
    int nextPosY = figureY + offsetX;

    if(tetrisGame.GetMap(nextPosX, nextPosY) != EMPTY){
	return false;
    }

    int tmpX[3], tmpY[3];

    tmpX[0] = figureX + offsetX - offsetY;
    tmpY[0] = figureY + offsetX + offsetY;

    if(abs(offsetX) > 1 || abs(offsetY) > 1) {
	tmpX[1] = (tmpX[0] + posX)/2;
	tmpX[2] = (tmpX[0] + figureX - offsetY)/2;
	tmpY[1] = (tmpY[0] + posY)/2;
	tmpY[2] = (tmpY[0] + figureY + offsetX)/2;

	if(tetrisGame.GetMap(tmpX[1], tmpY[1]) != EMPTY || tetrisGame.GetMap(tmpX[2], tmpY[2]) != EMPTY){
	    return false;
	}
    }else if(abs(offsetX) == 1 && abs(offsetY) == 1) {
	tmpX[1] = (tmpX[0] + posX)/2;
	tmpY[1] = (tmpY[0] + posY)/2;
	if(tetrisGame.GetMap(tmpX[1], tmpY[1]) != EMPTY){
	    return false;
	}
    }else if(tetrisGame.GetMap(tmpX[0], tmpY[0]) != EMPTY){
	return false;
    }
    return true;
}

bool Block::Rotate(const int figureX, const int figureY) {
    int offsetX = posX - figureX;
    int offsetY = posY - figureY;

    if(!CanRotate(figureX, figureY)){
	return false;
    }
    int nextPosX, nextPosY;
    nextPosX = figureX - offsetY;
    nextPosY = figureY + offsetX;
    SetPosX(nextPosX);
    SetPosY(nextPosY);
    return true;
}

bool Block::Translate(const int offsetX, const int offsetY){
    int nextPosX = posX + offsetX, nextPosY = posY + offsetY;

    if(tetrisGame.GetMap(nextPosX, nextPosY) != EMPTY){
	return false;
    }
    SetPosX(nextPosX);
    SetPosY(nextPosY);
    return true;
}

bool Block::CanTranslate(const int offsetX, const int offsetY) const {
    int nextPosX = posX + offsetX, nextPosY = posY + offsetY;

    if(tetrisGame.GetMap(nextPosX, nextPosY) != EMPTY){
	return false;
    }
    return true;
}
