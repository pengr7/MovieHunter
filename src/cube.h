#ifndef _CUBE_H_
#define _CUBE_H_
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"


class cube {
private:
	GLfloat position[3];
	GLfloat length;  //边长
	GLfloat direction[3]; //方向
	GLfloat color[6][3]; //六个面的颜色

public:
	cube(GLfloat* p, GLfloat* d, GLfloat* c[], GLfloat l);
	~cube();
	GLfloat * getPosition();
	void setPosition(GLfloat* p);
	GLfloat * getDirection();
	void setDirection(GLfloat* d);
	GLfloat * getColor(int num);
	void setColor(int num, GLfloat* c);
	GLfloat getLength();
	void setLength(GLfloat l);
};

#endif