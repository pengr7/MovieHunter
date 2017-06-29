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
	if (key == 'L' || key == 'l')  
		controller->RoateSetting(0, 0, -1);
	if (key == ';')
		controller->RoateSetting(0, 0, 1);
	if (key == 'R' || key == 'r')
		controller->RoateSetting(0, 2, 1);
	if (key == 'T' || key == 't')
		controller->RoateSetting(0, 2, -1);
	if (key == 'R' || key == 'r')
		controller->RoateSetting(0, 2, 1);
	if (key == 'T' || key == 't')
		controller->RoateSetting(0, 2, -1);
	if (key == 'F' || key == 'f')
		controller->RoateSetting(2, 2, 1);
	if (key == 'G' || key == 'g')
		controller->RoateSetting(2, 2, -1);
	if (key == 'B' || key == 'b')
		controller->RoateSetting(2, 0, -1);
	if (key == 'N' || key == 'n')
		controller->RoateSetting(2, 0, 1);
	if (key == 'U' || key == 'u')
		controller->RoateSetting(1, 2, 1);
	if (key == 'I' || key == 'i')
		controller->RoateSetting(1, 2, -1);
	if (key == 'D' || key == 'd')
		controller->RoateSetting(1, 0, -1);
	if (key == 'C' || key == 'c')
		controller->RoateSetting(1, 0, 1);

	if (key == 'X' || key == 'x')
		controller->RoateSetting(0, 3, 1);
	if (key == 'Y' || key == 'y')
		controller->RoateSetting(1, 3, 1);
	if (key == 'Z' || key == 'z')
		controller->RoateSetting(2, 3, 1);
	if (key == '4') {
		xadd -= 0.1;
		if (xadd < -0.7) xadd = -0.7;
	}
	if (key == '6') {
		xadd += 0.1;
		if (xadd > 0.7) xadd = 0.7;
	}
	if (key == '8') {
		yadd += 0.1;
		if (yadd > 0.7) yadd = 0.7;
	}
	if (key == '5') {
		yadd -= 0.1;
		if (yadd < -0.7) yadd = -0.7;
	}
}

//void DrawCube(void) {
//	int i, j;
//	glBegin(GL_QUADS);
//	glEnd();
//}
//
//void translation() {
//	glTranslatef(location, 0, 0);
//}
//
//void rotation() {
//	glRotatef(angle, 1, 1, 0);  // rotate around y=x axis in the XoY plane
//}
