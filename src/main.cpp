#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <math.h>
#include <time.h>
#include<iostream>
#include "RubikController.h"
using namespace std;


rubik* myRubik;
RubikController* controller;
GLfloat RubikPosition[3] = { 0,0,0 };
GLfloat RubikDirection[3] = { 1, 0, 0 };
GLfloat RubikColor[6][3] = { {0, 0, 0},
							 {1, 0, 0},
							 {0, 1, 0},
							 {1, 0.5f, 0},
							 {0, 0, 1},
							 {1, 1, 0} };
GLfloat RubikLength = 0.2f;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 3, 10);  // 透视投影

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 3, 5,
		0.0, 0.0, 0.0,
		0.0, 0, 0.0);

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
	myRubik = new rubik(RubikPosition, RubikDirection, RubikColor, RubikLength);
	controller = new RubikController();
	controller->setRubik(myRubik);

	glutCreateWindow("Rubik");
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutMainLoop();
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