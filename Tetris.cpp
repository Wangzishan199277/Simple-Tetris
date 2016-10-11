#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "Common.h"
#include "Tetris.h"

using namespace std;

Figure tetrisFigure(rand() % NUM_FIGURE);

Game tetrisGame;

void HandleKeyPress(unsigned char key, int x, int y);

void Display(void);

void Update(int value);

void HandleKeyPress(unsigned char key, int x, int y) {
    if(tetrisGame.GetStatus()){
	switch(key){
	    case 'a':
		tetrisFigure.Translate(-1, 0);
		glutPostRedisplay();
		break;
	    case 's':
		tetrisFigure.Translate(0,-1);
		glutPostRedisplay();
		break;
	    case 'd':
		tetrisFigure.Translate(1,0);
		glutPostRedisplay();
		break;
	    case 'w':
		tetrisFigure.Rotate();
		glutPostRedisplay();
		break;
	    default :
		break;
	}
    }else{
	switch(key){
	    case 'n':
		tetrisGame.New();
		glutPostRedisplay();
		break;
	    default:
		break;
	}
    }
}

void Display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    if(tetrisGame.GetStatus()){
	tetrisFigure.Draw();
    }

    tetrisGame.Draw();
    glutSwapBuffers();
}

void Update(int value){
    if(tetrisGame.GetStatus()){
	int moveSuccess = tetrisFigure.Translate(0,-1);

	if(!moveSuccess){
	    tetrisGame.Update(tetrisFigure);
	    tetrisFigure.New(rand() % NUM_FIGURE);
	}
    }

    glutPostRedisplay();

    glutTimerFunc(500, Update, 0);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH + 100, WINDOW_HEIGHT + 100);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("Tetris Game");

    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(-50, (GLdouble)WINDOW_WIDTH + 50, -50, (GLdouble)WINDOW_HEIGHT + 50);
    srand(time(NULL));

    glutDisplayFunc(Display);
    glutKeyboardFunc(HandleKeyPress);

    glutTimerFunc(500, Update, 0);


    glutMainLoop();
}
