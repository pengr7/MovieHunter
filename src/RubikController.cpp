#include "RubikController.h"

RubikController::RubikController() {
	RoateSpeed = 0.3;
    IsRoating = false;
	xyz = 0;
	num = -1;
	dir = 0;
	RoateCount = 0;
}

RubikController::~RubikController() {}

bool RubikController::getRotatingState() {
	return IsRoating;
}

void RubikController::setRubik(rubik* rubik_) {
	MyRubik = rubik_;
}//设置魔方

void RubikController::setSpeed(GLfloat s) {
	RoateSpeed = s;
}

void RubikController::RoateSetting(int xyz_, int num_, int dir_) {
	if (IsRoating == false) {
		xyz = xyz_;
		num = num_;
		dir = dir_;
		if (num != -1) {
			IsRoating = true;
		}
	}
} //只有在IsRoating是false的情况下才能更改xyz,num,dir

void RubikController::RubikMainCycle() {
	if (IsRoating) {
	    int update = 0;
	    GLfloat angle = RoateCount + RoateSpeed;
		RoateCount = angle;
	    if (angle >= 90) {
	        angle = 90;
	    	update = 1;
	    	RoateCount = 0;
		    IsRoating = false;
	    }
		MyRubik->RotatPlane(xyz, num, dir, update);
		int Tangle;
		int z[3] = {0, 0, 0 };
		z[xyz] = 1;
		Tangle = -dir * angle;
		glPushMatrix();
		glRotatef(Tangle, z[0], z[1], z[2]);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					cube* ac = MyRubik->getACube(i, j, k);
					if (ac->getIsRoate()) {
						ac->DrawCube();
					}
				}
			}
		}
		glPopMatrix();
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				cube* ac = MyRubik->getACube(i, j, k);
				if (!ac->getIsRoate()) {
					ac->DrawCube();
				}
			}
		}
	}

}//主循环里每次循环都调用本函数，在这个函数调用MyRubik->RotatPlane(),并更新IsRoating和RoateCount,然后绘制魔方

void RubikController::doReset() {
	if (!IsRoating) {
		MyRubik->reset();
	}
}//还原魔方
