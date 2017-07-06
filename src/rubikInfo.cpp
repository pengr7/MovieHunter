#include "rubikInfo.h"

GLfloat RubikPositionInit[3] = { 0, 0, 0 };
GLfloat RubikColorInit[6][3] = {
	{ 1, 1, 1 },
	{ 1, 0, 0 },
	{ 0, 1, 0 },
	{ 1, 0.5, 0 },
	{ 0, 0, 1 },
	{ 1, 1, 0 }
};
GLfloat RubikLengthInit = 0.2;

rubikInfo::rubikInfo() {
	setRubikPosition(RubikPositionInit);
	setRubikColor(RubikColorInit);
	setRubikLength(RubikLengthInit);
}

rubikInfo::~rubikInfo() {
	setRubikPosition(RubikPositionInit);
	setRubikColor(RubikColorInit);
	setRubikLength(RubikLengthInit);
}

void rubikInfo::setRubikPosition(GLfloat RubikPosition_[3]) {
	for (int i = 0; i < 3; ++i)
		RubikPosition[i] = RubikPosition_[i];
}

GLfloat* rubikInfo::getRubikPosition() {
	return RubikPosition;
}

void rubikInfo::setRubikColor(GLfloat RubikColor_[6][3]) {
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 3; ++j)
			RubikColor[i][j] = RubikColor_[i][j];
}

GLfloat(*rubikInfo::getRubikColor())[3]{
	return RubikColor;
}

void rubikInfo::setRubikLength(GLfloat RubikLength_) {
	RubikLength = RubikLength_;
}

GLfloat rubikInfo::getRubikLength() {
	return RubikLength;
}

