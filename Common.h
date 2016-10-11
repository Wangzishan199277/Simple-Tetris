#ifndef COMMON_H
#define COMMON_H

#include <GL/glut.h>
//number of shape
#define NUM_FIGURE 7

//number of blocks needed for each shape
#define NUM_FIGURE_BLOCK 4

//the length of each block
#define BLOCK_SIZE 19

//the space between two blocks
#define BLOCK_SPACING 1

#define MAX_BLOCK_NUM 100

#define WINDOW_WIDTH 350
#define WINDOW_HEIGHT 500

#define NUM_BLOCKS_X WINDOW_WIDTH/(BLOCK_SIZE + BLOCK_SPACING)
#define NUM_BLOCKS_Y WINDOW_HEIGHT/(BLOCK_SIZE + BLOCK_SPACING)

#define USED 1
#define EMPTY 0

#define RUNNING 1
#define LOSE 0

const int image[NUM_FIGURE][NUM_FIGURE_BLOCK][2]={
    {
	{0,0},{0,1},{1,1},{1,0}
    },
    {
	{0,-1},{0,0},{0,1},{0,2}
    },
    {
	{0,1},{-1,1},{-1,0},{-1,-1}
    },
    {
	{0,1},{1,1},{1,0},{1,-1}
    },
    {
	{-1,1},{-1,0},{0,0},{0,-1}
    },
    {
	{0,1},{0,0},{-1,0},{-1,-1}
    },
    {
	{-1,0},{0,0},{1,0},{0,1}
    }
};

#endif
