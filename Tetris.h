#ifndef TETRIS_H
#define TETRIS_H

#include "Common.h"

class Block{
public:
//constructor and destructor
Block();
virtual ~Block();

//show the square
void Draw() const;

//judge whether the square can rotate to the specified position
//The parameter is the position of the square
bool CanRotate(const int figureX, const int figureY) const;

bool Rotate(const int figureX, const int figureY);

bool Translate(const int offsetX, const int offsetY);

bool CanTranslate(const int offsetX, const int offsetY) const;

Block &operator = (Block & other){
if(this != &other){
SetPosX(other.GetPosX());
SetPosY(other.GetPosY());
}
return *this;
}

int GetPosX() const {return posX;}
int GetPosY() const {return posY;}

void SetPosX(const int x) {posX = x;}
void SetPosY(const int y) {posY = y;}
private:
int posX, posY;
};

class Figure{
public:
Figure(int numFigure);
Figure();
virtual ~Figure();

void New(int numFigure);

void Draw() const;

bool Rotate();

bool Translate(const int offsetX, const int offsetY);

int GetPosX() const {return posX;}
int GetPosY() const {return posY;}

void SetPosX(const int x) {posX = x; }
void SetPosY(const int y) {posY = y; }

Block data[NUM_FIGURE_BLOCK];

private:
int posX, posY;
bool canRotate;
};

class Game{
public:
//constructor and destructor
Game();
virtual ~Game();

//show the interface
void Draw() const;

//update the status of the game interface
void Update(const Figure &figure);

//judge whether the row is full
bool RowIsFull(const int row) const;

//clear the row
void ClearRow(const int row);

//creat new game
void New();

//get whether the specified space is shown
int GetMap(const int x, const int y) const;

//get whether the game is running
bool GetStatus() const {return status;}

//reset the game status
void SetStatus(const bool newstatus) {status = newstatus; }
private:
int num_row, num_col;
int map[MAX_BLOCK_NUM][MAX_BLOCK_NUM];
bool status;
};
#endif
