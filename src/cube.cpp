#include "cube.h"

cube::cube(GLfloat* p, GLfloat* d, GLfloat* c[], GLfloat l) {
	for (int i = 0; i < 3; i++) {
		position[i] = p[i];
		direction[i] = d[i];
		for (int j = 0; j < 6; j++) {
			color[j][i] = c[j][i];
		}
	}
	int length = l;
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
GLfloat * cube::getDirection() {
	return direction;
}
void cube::setDirection(GLfloat* d) {
	for (int i = 0; i < 3; i++) {
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
