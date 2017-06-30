#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <math.h>
#include <time.h>
#include<iostream>
#include "RubikController.h"
using namespace std;

void processNormalKeys(unsigned char key, int x, int y);
rubik* myRubik;
RubikController* controller;
GLfloat RubikPosition[3] = { 0,0,0 };
GLfloat RubikColor[6][3] = { {1, 1, 1},
							 {1, 0, 0},
							 {0, 1, 0},
							 {1, 0.5f, 0},
							 {0, 0, 1},
							 {1, 1, 0} };
GLfloat RubikLength = 0.2f;
GLfloat speed = 0.3;
GLfloat xadd = 0.4;
GLfloat yadd = 0.4;
GLfloat zadd = 0;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.2, 0.2, -0.2, 0.2, 0.5, 100);  // 透视投影

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(sin(clock() / 1000.0) * 2, 2, cos(clock() / 1000.0) * 2,
	//	0.0, 0.0, 0.0,
	//	0.0, 1.0, 0.0);

	gluLookAt(2*sin(xadd)*cos(yadd), 2*sin(yadd), 2*cos(xadd)*cos(yadd),
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	glPushMatrix();

	controller->RubikMainCycle();
	glPopMatrix();
	glutSwapBuffers();
	glClear(GL_DEPTH_BUFFER_BIT);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	
	//初始化魔方
	myRubik = new rubik(RubikPosition, RubikColor, RubikLength);
	controller = new RubikController();
	controller->setRubik(myRubik);
	controller->setSpeed(speed);

	glutCreateWindow("Rubik");
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutMainLoop();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	// Front Back Up Down Left Right
	if (key == 'F')
		controller->RoateSetting(2, 2, 1);
	if (key == 'f')
		controller->RoateSetting(2, 2, -1);
	if (key == 'B')
		controller->RoateSetting(2, 0, -1);
	if (key == 'b')
		controller->RoateSetting(2, 0, 1);
	if (key == 'U')
		controller->RoateSetting(1, 2, 1);
	if (key == 'u')
		controller->RoateSetting(1, 2, -1);
	if (key == 'D')
		controller->RoateSetting(1, 0, -1);
	if (key == 'd')
		controller->RoateSetting(1, 0, 1);
	if (key == 'L')
		controller->RoateSetting(0, 0, -1);
	if (key == 'l')
		controller->RoateSetting(0, 0, 1);
	if (key == 'R')
		controller->RoateSetting(0, 2, 1);
	if (key == 'r')
		controller->RoateSetting(0, 2, -1);

	// Middle Equator Standing
	if (key == 'M') {
		controller->RoateSetting(0, 1, -1);
	}
	if (key == 'm') {
		controller->RoateSetting(0, 1, 1);
	}
	if (key == 'E') {
		controller->RoateSetting(1, 1, -1);
	}
	if (key == 'e') {
		controller->RoateSetting(1, 1, 1);
	}
	if (key == 'S') {
		controller->RoateSetting(2, 1, 1);
	}
	if (key == 's') {
		controller->RoateSetting(2, 1, -1);
	}

	// X Y Z
	if (key == 'X')
		controller->RoateSetting(0, 3, 1);
	if (key == 'x')
		controller->RoateSetting(0, 3, -1);
	if (key == 'Y')
		controller->RoateSetting(1, 3, 1);
	if (key == 'y')
		controller->RoateSetting(1, 3, -1);
	if (key == 'Z')
		controller->RoateSetting(2, 3, 1);
	if (key == 'z')
		controller->RoateSetting(2, 3, -1);

	// Fine tuning and reset
	if (key == '0') {
		xadd = 0.4;
		yadd = 0.4;
		zadd = 0;
	}
	if (key == '4') {
		xadd -= 0.1;
		if (xadd < -0.7)
			xadd = -0.7;
	}
	if (key == '6') {
		xadd += 0.1;
		if (xadd > 0.7)
			xadd = 0.7;
	}
	if (key == '8') {
		yadd -= 0.1;
		if (yadd < -0.7)
			yadd = -0.7;
	}
	if (key == '5') {
		yadd += 0.1;
		if (yadd > 0.7)
			yadd = 0.7;
	}
}
