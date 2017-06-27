#ifndef _RUBIKC_H_
#define _RUBIKC_H_
#include "rubik.h"

class RubikController {
private:
	rubik* MyRubik = NULL;
	GLfloat RoateSpeed = 0.1f; //ħ����ת���ٶ�(һ֡��ת�ĽǶ�)
	bool IsRoating = false; //�Ƿ�������ת
	int xyz = 0;  //xyz����ת
	int num = -1;  //ѡ��0/1/2�棬3ȫ����-1��ʾ����ת
	int dir = 0;  //��ת�ķ���0/1Ϊ˳/��ʱ��
	GLfloat RoateCount = 0; //��һ����ת���ۼƵ�RoateCount = 90��������ת

public:
	RubikController();
	~RubikController();
	void setRubik(rubik* rubik_); //����ħ��
	void RoateSetting(int xyz_, int num_, int dir_); //ֻ����IsRoating��false������²��ܸ���xyz,num,dir
	void RubikMainCycle(); //��ѭ����ÿ��ѭ�������ñ��������������������MyRubik->RotatPlane(),������IsRoating��RoateCount,Ȼ�����ħ��
	void DrawCube(cube* c); //����һ��cube��
};

#endif