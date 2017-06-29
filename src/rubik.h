#ifndef _RUBIK_H_
#define _RUBIK_H_
#include "cube.h"

class rubik {
private:
	GLfloat position[3];
	GLfloat length;  //С��߳�
	GLfloat color[6][3]; //���������ɫ ˳��Ϊ��ǰ�Һ���
	cube* Cube[3][3][3]; //ħ������½ǿ�Ϊ(0,0,0)������X��������ǰZ����������Y������
public:
	rubik(GLfloat p[], GLfloat c[][3], GLfloat l); //��Ҫ��ʼ��Cube����
	~rubik();

	GLfloat * getPosition();
	void setPosition(GLfloat* p);

	GLfloat * getColor(int num);
	void setColor(int num, GLfloat* c);

	GLfloat getLength();
	void setLength(GLfloat l);

	cube* getACube(int x, int y, int z);  //����Cube[x][y][z]��ָ��

	void RotatPlane(int xyz, int num, int dir, int update); 
	//xyz = 0�� num = 1 ��Ϊ��ת x = 1 ��ƽ�� xyz = 1, num = 2��Ϊ��ת y = 2���棬���ƣ�num = 3Ϊͬʱ��ת3���棬������ħ�� num = -1 Ϊ��
	//dir = -1/1Ϊ˳/��ʱ��, ��ת�Ƕ�90 ��updateΪ0�������Cube����,1Ϊ��Ҫ���¡�
};
#endif