#include "Tetris.h"
#include "Common.h"
#include <stdio.h>
#include <time.h>

extern Game tetrisGame;

Figure::Figure(){
    int numFigure = rand() % NUM_FIGURE;

    New(numFigure);
}

Figure::Figure(int numFigure){
    New(numFigure);
}

Figure::~Figure(){
}

void Figure::Draw() const {
int i;
for(i = 0; i < NUM_FIGURE_BLOCK; i++){
data[i].Draw();
}
}

void Figure::New(int numFigure){
    int i;
    if(numFigure >= 0 && numFigure < NUM_FIGURE){
	canRotate = (numFigure != 0);

	posX = NUM_BLOCKS_X/2;
	posY = NUM_BLOCKS_Y - 2;

	if(tetrisGame.GetMap(posX, posY+1) == 1 && tetrisGame.GetStatus()){
	    tetrisGame.SetStatus(false);
	    return;
	}

	for(i = 0; i < NUM_FIGURE_BLOCK; i++){
	    data[i].SetPosX(posX + image[numFigure][i][0]);
	    data[i].SetPosY(posY + image[numFigure][i][1]);
	}
    }
}

bool Figure::Rotate(){
int i;
if(!canRotate){
return false;
}

for(i = 0; i < 4; i++){
if(!data[i].CanRotate(posX, posY)){
return false;
}
}

for(i = 0; i < 4; i++){
data[i].Rotate(posX, posY);
}
return true;
}

bool Figure::Translate(const int offsetX, const int offsetY){
int i;

for(i = 0; i < 4; ++i){
if(!data[i].CanTranslate(offsetX, offsetY)){
return false;
}
}

for(i = 0; i < 4; i++){
data[i].Translate(offsetX, offsetY);
}

SetPosX(posX+offsetX);
SetPosY(posY+offsetY);
return true;
}
