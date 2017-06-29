#include "cube.h"

cube::cube() {
	for (int i = 0; i < 3; i++) {
		position[i] = 0;
		direction[i] = 0;
		for (int j = 0; j < 6; j++) {
			color[j][i] = 0;
		}
	}
	direction[3] = 0;
	int length = 0.1f;
}

cube::cube(GLfloat p[], GLfloat d[], GLfloat c[][3], GLfloat l) {
	for (int i = 0; i < 3; i++) {
		position[i] = p[i];
		direction[i] = d[i];
		for (int j = 0; j < 6; j++) {
			color[j][i] = c[j][i];
		}
	}
	int length = l;
	IsRoate = false;
}

cube::~cube() {}

GLfloat * cube::getPosition() {
	return position;
}
void cube::setPosition(GLfloat* p) {
	for (int i = 0; i < 3; i++) {
		position[i] = p[i];
	}
}
GLfloat* cube::getDirection() {
	return direction;
}
void cube::setDirection(GLfloat* d) {
	for (int i = 0; i < 6; i++) {
		direction[i] = d[i];
	}
}
GLfloat * cube::getColor(int num) {
	return color[num];
}
void cube::setColor(int num, GLfloat* c) {
	for (int i = 0; i < 3; i++) {
		color[num][i] = c[i];
	}
}
GLfloat cube::getLength() {
	return length;
}
void cube::setLength(GLfloat l) {
	length = l;
}

bool cube::getIsRoate() {
	return IsRoate;
}
void cube::setIsRoate(bool b) {
	IsRoate = b;
}

void cube::DrawCube() {
	GLfloat l = length;
	GLfloat l2 = l / 2 - 0.01f;
	GLfloat CubePoint[8][3] = {
		{ -l2, -l2, -l2 },
		{ l2, -l2, -l2 },
		{ -l2, -l2, l2 },
		{ l2, -l2, l2 },
		{ -l2, l2, -l2 },
		{ l2, l2, -l2 },
		{ -l2, l2, l2 },
		{ l2, l2, l2 },
	}; //cube的八个顶点

	const int Index[6][4] = {
		{ 0, 1, 3, 2 },  //底面
		{ 2, 3, 7, 6 },  //前面
		{ 1, 5, 7, 3 },  //右面
		{ 0, 1, 5, 4 },  //后面
		{ 0, 2, 6, 4 },  //左面
		{ 4, 5, 7, 6 },  //顶面
	};//六个面的顶点索引

	glPushMatrix();

	int x;
	int y;
	int z;
	int angle1;
	GLfloat d2 = 0;
	int angle2;
	if (direction[2] != 0) {
		x = 0;
		y = 1;
		z = 0;
		angle1 = 90 - 90 * direction[2];
	}
	else if (direction[0] != 0) {
		x = 0;
		y = 1;
		z = 0;
		angle1 = direction[0] * 90;
	}
	else if (direction[1] != 0) {
		x = 1;
		y = 0;
		z = 0;
		angle1 = -direction[1] * 90;
		d2 = -direction[1];
	}
	if (d2 == 0) {
	    if (direction[4] != 0) {
	    	angle2 = 90 - direction[4] * 90;
	    }
	    else if (direction[3] != 0) {
			angle2 = -direction[2] * 90 * direction[3];
		}
		else if (direction[5] != 0) {
			angle2 = direction[0] * 90 * direction[5];
		}
    } else {
		if (direction[5] != 0) {
			angle2 = 90 - d2 * direction[5] * 90;
		}
		else if (direction[4] != 0) {
			angle2 = -d2 * direction[0] * 90 * direction[4];
		}
		else if (direction[3] != 0) {
			angle2 = d2 * direction[1] * 90 * direction[3];
		}
	}
	glTranslatef(position[0], position[1], position[2]);
	glRotatef(angle2, direction[0], direction[1], direction[2]);
	glRotatef(angle1, x, y, z);
	int i, j;
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++) {
		glColor3f(color[i][0], color[i][1], color[i][2]);
		for (j = 0; j < 4; j++) {
			l2 = l2 - 0.1f;
			glVertex3fv(CubePoint[Index[i][j]]);
			l2 = l / 2;
		}
	}
	glEnd();
	
    glPopMatrix();
}//绘制一个cube。

