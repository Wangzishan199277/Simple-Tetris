#include <stdio.h>
#include <string.h>

#include "Common.h"
#include "Tetris.h"

extern Figure tetrisFigure;

Game::Game(){
    num_col = (WINDOW_WIDTH)/(BLOCK_SIZE + BLOCK_SPACING);
    num_row = (WINDOW_HEIGHT)/(BLOCK_SIZE + BLOCK_SPACING);

    status = true;
}

Game::~Game(){
}

void Game::Draw() const {
    int i, j;

    glBegin(GL_LINE_LOOP);
    glColor3f(0.5,0.2,0.1);
    glVertex3f(0,0,0);
    glVertex3f(WINDOW_WIDTH-BLOCK_SIZE/2, 0, 0);
    glVertex3f(WINDOW_WIDTH-BLOCK_SIZE/2, WINDOW_HEIGHT,0);
    glVertex3f(0, WINDOW_HEIGHT, 0);
    glEnd();

    if(status){
	Block block = Block();

	for(i = 0; i < num_row; i++){
	    for(j = 0; j < num_col; j++){
		if(map[i][j]){
		    block.SetPosX(j);
		    block.SetPosY(i);
		    block.Draw();
		}
	    }
	}
    }else{
	char string[] = "GAME OVER";
	int len;

	glRasterPos2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

	len = (int) strlen(string);
	for(i = 0; i < len; i++){
	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
    }
}

void Game::New(){
    int i, j;

    for(i = 0; i < num_row; i++){
	for(j = 0; j < num_col; j++){
	    map[i][j] = EMPTY;
	}
    }

    tetrisFigure.New(rand()%NUM_FIGURE);

    status = true;
}

void Game::Update(const Figure &figure){
    int i, num;

    for(i = 0; i < NUM_FIGURE_BLOCK; ++i){
	map[figure.data[i].GetPosY()][figure.data[i].GetPosX()] = USED;
    }

    num = figure.GetPosY();

    for(i = num + 2; i > num - 2; --i){
	if(RowIsFull(i)){
	    ClearRow(i);
	}
    }
}

void Game::ClearRow(const int row){
    int i, j;

    if(row < 0 || row >= num_row){
	return;
    }

    for(i = row; i < num_row - 2; ++i){
	for(j = 0; j < num_col; ++j){
	    map[i][j] = map[i+1][j];
	}
    }

    for(j = 0; j < num_col; ++j){
	map[num_row - 1][j] = 0;
    }
}

bool Game::RowIsFull(const int row) const {
    int i;

    if(row < 0 || row >= num_row){
	return false;
    }

    for(i = 0; i < num_col; ++i){
	if(map[row][i] == EMPTY){
	    return false;
	}
    }
    return true;
}

int Game::GetMap(const int x, const int y) const{
    if((x < 0) || (y < 0) || (x >= num_col) || (y >= num_row)){
	return -1;
    }else{
	return map[y][x];
    }
}
