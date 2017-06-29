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

void RubikController::setRubik(rubik* rubik_) {
	MyRubik = rubik_;
}//����ħ��

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
} //ֻ����IsRoating��false������²��ܸ���xyz,num,dir

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

}//��ѭ����ÿ��ѭ�������ñ��������������������MyRubik->RotatPlane(),������IsRoating��RoateCount,Ȼ�����ħ��

