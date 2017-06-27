#ifndef _RUBIK_H_
#define _RUBIK_H_
#include "cube.h"

class rubik {
private:
	GLfloat position[3];
	GLfloat length;  //小块边长
	GLfloat direction[3]; //方向
	GLfloat color[6][3]; //六个面的颜色
	cube* Cube[3][3][3]; //魔方左后下角块为(0,0,0)，向左X轴正，向前Z轴正，向上Y轴正。
public:
	rubik(GLfloat p[], GLfloat d[], GLfloat c[][3], GLfloat l); //需要初始化Cube数组
	~rubik();
	GLfloat * getPosition();
	void setPosition(GLfloat* p);

	GLfloat * getDirection();

	GLfloat * getColor(int num);
	void setColor(int num, GLfloat* c);

	GLfloat getLength();
	void setLength(GLfloat l);

	cube* getACube(int x, int y, int z);  //返回Cube[x][y][z]的指针

	void RotatPlane(int xyz, int num, int dir, GLfloat angle, int update); 
	//xyz = 0， num = 1 即为旋转 x = 1 的平面 xyz = 1, num = 2即为旋转 y = 2的面，类推，num = 3为同时旋转3个面，即整个魔方
	//dir = 0/1为顺/逆时针, angle为旋转角度，update为0不需更新Cube数组,1为需要更新。
};
#endif
