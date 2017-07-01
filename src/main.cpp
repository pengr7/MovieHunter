#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\AntTweakBar\AntTweakBar.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "RubikController.h"
using namespace std;

void processNormalKeys(unsigned char key, int x, int y);
void subProcess(unsigned char key);

rubik* myRubik;
RubikController* controller;
GLfloat RubikPosition[3] = { 0,0,0 };
GLfloat RubikColor[6][3] = { { 1, 1, 1 },
{ 1, 0, 0 },
{ 0, 1, 0 },
{ 1, 0.5f, 0 },
{ 0, 0, 1 },
{ 1, 1, 0 } };
GLfloat RubikLength = 0.2f;
GLfloat speed = 0.3;
GLfloat xadd = 0.4;
GLfloat yadd = 0.4;
GLfloat zadd = 0;
string restore;

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

	gluLookAt(2 * sin(xadd)*cos(yadd), 2 * sin(yadd), 2 * cos(xadd)*cos(yadd),
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	glPushMatrix();

	controller->RubikMainCycle();
	glPopMatrix();

	TwDraw();

	glutSwapBuffers();
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Reshape(int width, int height) {
	TwWindowSize(width, height);
}

// function callback for UI 
void TW_CALL Rotate_X(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(0, 3, 1);
	restore += tolower('x');
}
void TW_CALL Rotate_Y(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(1, 3, 1);
	restore += tolower('y');
}
void TW_CALL Rotate_Z(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(2, 3, 1);
	restore += tolower('z');
}
void TW_CALL Rotate_X_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(0, 3, -1);
	restore += toupper('x');
}
void TW_CALL Rotate_Y_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(1, 3, -1);
	restore += toupper('y');
}
void TW_CALL Rotate_Z_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(2, 3, -1);
	restore += toupper('z');
}
/*
void TW_CALL Look_Default(void*) {
xadd = 0.4;
yadd = 0.4;
zadd = 0;
}
void TW_CALL Look_Left(void*) {
xadd -= 0.1;
if (xadd < -0.7)
xadd = -0.7;
}
void TW_CALL Look_Right(void*) {
xadd += 0.1;
if (xadd > 0.7)
xadd = 0.7;
}
void TW_CALL Look_Up(void*) {
yadd -= 0.1;
if (yadd < -0.7)
yadd = -0.7;
}
void TW_CALL Look_Down(void*) {
yadd += 0.1;
if (yadd > 0.7)
yadd = 0.7;
}

*/


void TW_CALL Action_Front(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(2, 2, 1);
	restore += tolower('f');
}
void TW_CALL Action_Back(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(2, 0, -1);
	restore += tolower('b');
}
void TW_CALL Action_Left(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(0, 0, -1);
	restore += tolower('L');
}
void TW_CALL Action_Right(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(0, 2, 1);
	restore += tolower('r');
}
void TW_CALL Action_Up(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(1, 2, 1);
	restore += tolower('u');
}
void TW_CALL Action_Down(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(1, 0, -1);
	restore += tolower('d');
}

void TW_CALL Action_Front_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(2, 2, -1);
	restore += toupper('f');
}
void TW_CALL Action_Back_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(2, 0, 1);
	restore += toupper('b');
}
void TW_CALL Action_Left_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(0, 0, 1);
	restore += toupper('L');
}
void TW_CALL Action_Right_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(0, 2, -1);
	restore += toupper('r');
}
void TW_CALL Action_Up_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(1, 2, -1);
	restore += toupper('u');
}
void TW_CALL Action_Down_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(1, 0, 1);
	restore += toupper('d');
}


void TW_CALL Action_M(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(0, 1, -1);
	restore += tolower('m');
}
void TW_CALL Action_E(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(1, 1, -1);
	restore += tolower('e');
}
void TW_CALL Action_S(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(2, 1, 1);
	restore += tolower('s');
}
void TW_CALL Action_M_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(0, 1, 1);
	restore += toupper('m');
}
void TW_CALL Action_E_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(1, 1, 1);
	restore += toupper('e');
}
void TW_CALL Action_S_inverse(void*) {
	if (controller->getRotatingState())
		return;
	controller->RoateSetting(2, 1, -1);
	restore += toupper('s');
}
void TW_CALL Undo(void*) {
	if (!restore.empty() && !controller->getRotatingState()) {
		subProcess(restore.back());
		restore.pop_back();
	}
}
void TW_CALL Restore(void*) {
	controller->doReset();
	restore.clear();
}


int main(int argc, char **argv)
{
	TwBar *bar; // Pointer to the tweak bar
	TwBar *mybar; // Pointer to the tweak bar


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Rubik");
	glutCreateMenu(NULL);

	glutDisplayFunc(renderScene);
	glutReshapeFunc(Reshape);
	glutIdleFunc(renderScene);

	TwTerminate();

	// UI use
	TwInit(TW_OPENGL, NULL);
	glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
	// - Directly redirect GLUT mouse motion events to AntTweakBar
	glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	// - Directly redirect GLUT mouse "passive" motion events to AntTweakBar (same as MouseMotion)
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	// - Directly redirect GLUT key events to AntTweakBar
	//glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
	// - Directly redirect GLUT special key events to AntTweakBar
	glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);
	// - Send 'glutGetModifers' function pointer to AntTweakBar;
	//   required because the GLUT key event functions do not report key modifiers states.
	//TwGLUTModifiersFunc(glutGetModifiers);


	bar = TwNewBar("TweakBar");
	TwDefine(" GLOBAL help='Rotate the rubik' "); // Message added to the help bar.
	TwDefine(" TweakBar size='200 170' color='96 216 224' "); // change default tweak bar size and color
	TwDefine(" TweakBar position='10 10' ");
	TwAddButton(bar, "Rotate_X", Rotate_X, NULL, " label='Rotate X ' ");
	TwAddButton(bar, "Rotate_X_inverse", Rotate_X_inverse, NULL, " label='Rotate X inverse' ");
	TwAddButton(bar, "Rotate_Y", Rotate_Y, NULL, " label='Rotate Y ' ");
	TwAddButton(bar, "Rotate_Y_inverse", Rotate_Y_inverse, NULL, " label='Rotate Y inverse' ");
	TwAddButton(bar, "Rotate_Z", Rotate_Z, NULL, " label='Rotate Z ' ");
	TwAddButton(bar, "Rotate_Z_inverse", Rotate_Z_inverse, NULL, " label='Rotate Z inverse' ");
	TwAddButton(bar, "Undo", Undo, NULL, " label='Undo' ");
	TwAddButton(bar, "Restore", Restore, NULL, " label='Restore' ");
	//TwAddButton(bar, "Rotate_X", Rotate_X, NULL, " label='Rotate around X direction' ");
	/*
	bar = TwNewBar("Look_normal");
	TwDefine(" GLOBAL help='A different perspective' "); // Message added to the help bar.
	TwDefine(" Look size='200 300' color='96 216 224' "); // change default tweak bar size and color
	TwDefine(" Look position='250 100' ");
	TwAddButton(bar, "Look_Default", Look_Default, NULL, " label=' Default' ");
	TwAddButton(bar, "Look_Left", Look_Left, NULL, " label='Look_Left' ");
	TwAddButton(bar, "Look_Right", Look_Right, NULL, " label='Look_Right' ");
	TwAddButton(bar, "Look_Up", Look_Up, NULL, " label='Look_Up' ");
	TwAddButton(bar, "Look_Down", Look_Down, NULL, " label='Look_Down' ");
	*/


	bar = TwNewBar("Action_normal");
	TwDefine(" GLOBAL help='Your action' "); // Message added to the help bar.
	TwDefine(" Action_normal size='200 180' color='96 216 224' "); // change default tweak bar size and color
	TwDefine(" Action_normal position='250 10' ");
	TwAddButton(bar, "Front", Action_Front, NULL, " label='Front' ");
	TwAddButton(bar, "Back", Action_Back, NULL, " label='Back' ");
	TwAddButton(bar, "Left", Action_Left, NULL, " label='Left' ");
	TwAddButton(bar, "Right", Action_Right, NULL, " label='Right' ");
	TwAddButton(bar, "Up", Action_Up, NULL, " label='Up' ");
	TwAddButton(bar, "Down", Action_Down, NULL, " label='Down' ");
	TwAddButton(bar, "M", Action_M, NULL, " label='M' ");
	TwAddButton(bar, "E", Action_E, NULL, " label='E' ");
	TwAddButton(bar, "S", Action_S, NULL, " label='S' ");


	bar = TwNewBar("Action_inverse");
	TwDefine(" GLOBAL help='Your action' "); // Message added to the help bar.
	TwDefine(" Action_inverse size='200 180' color='96 216 224' "); // change default tweak bar size and color
	TwDefine(" Action_inverse position='490 10' ");
	TwAddButton(bar, "Front_inverse", Action_Front_inverse, NULL, " label='Front_inverse' ");
	TwAddButton(bar, "Back_inverse", Action_Back_inverse, NULL, " label='Back_inverse' ");
	TwAddButton(bar, "Left_inverse", Action_Left_inverse, NULL, " label='Left_inverse' ");
	TwAddButton(bar, "Right_inverse", Action_Right_inverse, NULL, " label='Right_inverse' ");
	TwAddButton(bar, "Up_inverse", Action_Up_inverse, NULL, " label='Up_inverse' ");
	TwAddButton(bar, "Down_inverse", Action_Down_inverse, NULL, " label='Down_inverse' ");
	TwAddButton(bar, "M_inverse", Action_M_inverse, NULL, " label='M_inverse' ");
	TwAddButton(bar, "E_inverse", Action_E_inverse, NULL, " label='E_inverse' ");
	TwAddButton(bar, "S_inverse", Action_S_inverse, NULL, " label='S_inverse' ");


	//初始化魔方
	myRubik = new rubik(RubikPosition, RubikColor, RubikLength);
	controller = new RubikController();
	controller->setRubik(myRubik);
	controller->setSpeed(speed);

	glutKeyboardFunc(processNormalKeys);
	glutMainLoop();
}


void subProcess(unsigned char key) {
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

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 'Q' || key == 'q') {
		if (!restore.empty() && !controller->getRotatingState()) {
			subProcess(restore.back());
			restore.pop_back();
		}
	}
	else {
		if (!controller->getRotatingState()) {
			subProcess(key);
			if (isupper(key))
				restore += tolower(key);
			if (islower(key))
				restore += toupper(key);
		}
	}
	cout << restore << endl;
}
