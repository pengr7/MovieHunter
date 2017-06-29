#ifndef _CUBE_H_
#define _CUBE_H_
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"


class cube {
private:
	GLfloat position[3];
	GLfloat length;  //�߳�
	GLfloat direction[6]; //����
	GLfloat color[6][3]; //���������ɫ��˳��Ϊ��ǰ�Һ���
	bool IsRoate = false;

public:
	cube();
	cube(GLfloat p[], GLfloat d[], GLfloat c[][3], GLfloat l);
	~cube();
	GLfloat * getPosition();
	void setPosition(GLfloat* p);
	bool getIsRoate();
	void setIsRoate(bool b);
	GLfloat * getDirection();
	void setDirection(GLfloat* d);
	GLfloat * getColor(int num);
	void setColor(int num, GLfloat* c);
	GLfloat getLength();
	void setLength(GLfloat l);
	void DrawCube();
};



#endif