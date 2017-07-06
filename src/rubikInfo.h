#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <vector>
using namespace std;

class rubikInfo {
private:
	GLfloat RubikPosition[3];
	GLfloat RubikColor[6][3];
	GLfloat RubikLength;

public:
	rubikInfo();
	~rubikInfo();

	void setRubikPosition(GLfloat RubikPosition_[3]);
	GLfloat* getRubikPosition();

	void setRubikColor(GLfloat RubikColor_[6][3]);
	GLfloat(*getRubikColor())[3];

	void setRubikLength(GLfloat RubikLength_);
	GLfloat getRubikLength();
};
