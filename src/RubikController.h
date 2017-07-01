#ifndef _RUBIKC_H_
#define _RUBIKC_H_
#include "rubik.h"

class RubikController {
private:
	rubik* MyRubik = NULL;
	GLfloat RoateSpeed = 0.1; //魔方旋转的速度(一帧旋转的角度)
	bool IsRoating = false; //是否正在旋转
	int xyz = 0;  //xyz轴旋转
	int num = -1;  //选择0/1/2面，3全部，-1表示不旋转
	int dir = 0;  //旋转的方向，0/1为顺/逆时针
	GLfloat RoateCount = 0; //做一个旋转试累计到RoateCount = 90即结束旋转

public:
	RubikController();
	~RubikController();
	bool getRotatingState();
	void setSpeed(GLfloat s);
	void setRubik(rubik* rubik_); //设置魔方
	void RoateSetting(int xyz_, int num_, int dir_); //只有在IsRoating是false的情况下才能更改xyz,num,dir
	void RubikMainCycle(); //主循环里每次循环都调用本函数，在这个函数调用MyRubik->RotatPlane(),并更新IsRoating和RoateCount,然后绘制魔方
	void doReset(); //还原魔方
};

#endif
