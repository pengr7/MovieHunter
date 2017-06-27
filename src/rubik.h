#ifndef _RUBIK_H_
#define _RUBIK_H_
#include "cube.h"

class rubik {
private:
	GLfloat position[3];
	GLfloat length;  //С��߳�
	GLfloat direction[3]; //����
	GLfloat color[6][3]; //���������ɫ
	cube* Cube[3][3][3]; //ħ������½ǿ�Ϊ(0,0,0)������X��������ǰZ����������Y������
public:
	rubik(GLfloat* p, GLfloat* d, GLfloat* c[], GLfloat l); //��Ҫ��ʼ��Cube����
	~rubik();
	GLfloat * getPosition();
	void setPosition(GLfloat* p);

	GLfloat * getDirection();

	GLfloat * getColor(int num);
	void setColor(int num, GLfloat* c);

	GLfloat getLength();
	void setLength(GLfloat l);

	cube* getACube(int x, int y, int z);  //����Cube[x][y][z]��ָ��
	void AllCubeDO(void (*a)(void));
	//void RotatRubik(int xyz, int dir, GLfloat angle, int update);  
	//xyz = 0/1/2ʱ��ӦΧ��X/Y/Z��תangle�ȣ�dir = 0/1Ϊ˳/��ʱ��,updateΪ0�������Cube����,1Ϊ��Ҫ���¡�
	void RotatPlane(int xyz, int num, int dir, GLfloat angle, int update); 
	//xyz = 0�� num = 1 ��Ϊ��ת x = 1 ��ƽ�� xyz = 1, num = 2��Ϊ��ת y = 2���棬���ƣ�num = 3Ϊͬʱ��ת3���棬������ħ��
	//dir = 0/1Ϊ˳/��ʱ��, angleΪ��ת�Ƕȣ�updateΪ0�������Cube����,1Ϊ��Ҫ���¡�
};
#endif