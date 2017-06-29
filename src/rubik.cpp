#include "rubik.h"

const GLfloat colorIndex[6][3] = {
	{ -1, 0, -1 },
	{ -1, -1, 2 },
	{ 2, -1, -1 },
	{ -1, -1, 0 },
	{ 0, -1, -1 },
	{ -1, 2, -1 }
};

rubik::rubik(GLfloat p[], GLfloat c[][3], GLfloat l) {
	length = l;
	for (int i = 0; i < 3; i++) {
		position[i] = p[i];
		for (int j = 0; j < 6; j++) {
			color[j][i] = c[j][i];
		}
	}
	GLfloat d[6] = { 0, 0, 1, 0, 1, 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				Cube[i][j][k] = new cube();
				Cube[i][j][k]->setDirection(d);
				Cube[i][j][k]->setLength(l);
				GLfloat cp[3] = { position[0] + (i - 1) * length, position[1] + (j - 1) * length, position[2] + (k - 1) * length };
				Cube[i][j][k]->setPosition(cp);
				for (int num = 0; num < 6; num++) {
					for (int i = 0; i < 3; i++) {
						color[num][i] = c[num][i];
					}
					if ((i == colorIndex[num][0] || colorIndex[num][0] == -1) &&
						(j == colorIndex[num][1] || colorIndex[num][1] == -1) &&
						(k == colorIndex[num][2] || colorIndex[num][2] == -1)) {
						Cube[i][j][k]->setColor(num, c[num]);
					}
				}
			}
		}
	}
} //��Ҫ��ʼ��Cube����
rubik::~rubik() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				Cube[i][j][k]->~cube();
			}
		}
	}
}

GLfloat * rubik::getPosition() {
	return position;
}
void rubik::setPosition(GLfloat* p) {
	for (int i = 0; i < 3; i++) {
	    position[i] = p[i];
    }
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				GLfloat cp[3] = { position[0] + (i - 1) * length, position[1] + (j - 1) * length, position[2] + (k - 1) * length };
				Cube[i][j][k]->setPosition(cp);
			}
		}
	}
}


GLfloat * rubik::getColor(int num) {
	return color[num];
}
void rubik::setColor(int num, GLfloat* c) {
	for (int i = 0; i < 3; i++) {
		color[num][i] = c[i];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if ((i == colorIndex[num][0] || colorIndex[num][0] == -1) &&
					(j == colorIndex[num][1] || colorIndex[num][1] == -1) &&
					(k == colorIndex[num][2] || colorIndex[num][2] == -1)) {
					Cube[i][j][k]->setColor(num, c);
				}
			}
		}
	}
}

GLfloat rubik::getLength() {
	return length;
}

void rubik::setLength(GLfloat l) {
	length = l;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				Cube[i][j][k]->setLength(l);
			}
		}
	}
}

cube* rubik::getACube(int x, int y, int z) {
	return Cube[x][y][z];
}//����Cube[x][y][z]��ָ��

const int P_Index[12][2] = { 0,0,1,2,2,1,1,0,0,1,0,0,
				             0,0,0,2,2,2,2,0,0,0,0,0 };

void rubik::RotatPlane(int xyz, int num, int dir, int update) {
	int RoateIndex[3] = { 3, 3, 3 };
	RoateIndex[xyz] = num;
	int MoveTo[3][3][3][3];
	cube* temp[3][3][3];
	GLfloat posTemp[3][3][3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				for (int o = 0; o < 3; o++) MoveTo[i][j][k][o] = -1;
				if ((i == RoateIndex[0] || RoateIndex[0] == 3) &&
					(j == RoateIndex[1] || RoateIndex[1] == 3) &&
					(k == RoateIndex[2] || RoateIndex[2] == 3)) {
					if (update == 0) {
						Cube[i][j][k]->setIsRoate(true);
					}
					else {
						Cube[i][j][k]->setIsRoate(false);
						GLfloat* d = Cube[i][j][k]->getDirection();
						if (xyz == 0) {
							for (int ps = 1; ps < 11; ps++) {
								if (j == P_Index[ps][0] && k == P_Index[ps][1]) {
									int ps_next = ps + dir;
									if (ps_next == 0) ps_next = 4;
									else if (ps_next == 5) ps_next = 1;
									else if (ps_next == 6) ps_next = 10;
									else if (ps_next == 11) ps_next = 7;
									MoveTo[i][j][k][0] = i;
									MoveTo[i][j][k][1] = P_Index[ps_next][0];
									MoveTo[i][j][k][2] = P_Index[ps_next][1];
								}
								if (ps == 4) ps += 2;
							}
							for (int plus = 0; plus < 4; plus = plus + 3) {
								if (d[1 + plus] != 0) {
									d[2 + plus] = -dir*d[1 + plus];
									d[1 + plus] = 0;
								}
								else if (d[2 + plus] != 0) {
									d[1 + plus] = dir*d[2 + plus];
									d[2 + plus] = 0;
								}
							}
						}
						else if (xyz == 1) {
							for (int ps = 1; ps < 11; ps++) {
								if (i == P_Index[ps][0] && k == P_Index[ps][1]) {
									int ps_next = ps - dir;
									if (ps_next == 0) ps_next = 4;
									else if (ps_next == 5) ps_next = 1;
									else if (ps_next == 6) ps_next = 10;
									else if (ps_next == 11) ps_next = 7;
									MoveTo[i][j][k][0] = P_Index[ps_next][0];
									MoveTo[i][j][k][1] = j;
									MoveTo[i][j][k][2] = P_Index[ps_next][1];
								}
								if (ps == 4) ps += 2;
							}
							for (int plus = 0; plus < 4; plus = plus + 3) {
								if (d[0 + plus] != 0) {
									d[2 + plus] = dir*d[0 + plus];
									d[0 + plus] = 0;
								}
								else if (d[2 + plus] != 0) {
									d[0 + plus] = -dir*d[2 + plus];
									d[2 + plus] = 0;
								}
							}
						}
						if (xyz == 2) {
							for (int ps = 1; ps < 11; ps++) {
								if (i == P_Index[ps][0] && j == P_Index[ps][1]) {
									int ps_next = ps + dir;
									if (ps_next == 0) ps_next = 4;
									else if (ps_next == 5) ps_next = 1;
									else if (ps_next == 6) ps_next = 10;
									else if (ps_next == 11) ps_next = 7;
									MoveTo[i][j][k][0] = P_Index[ps_next][0];
									MoveTo[i][j][k][1] = P_Index[ps_next][1];
									MoveTo[i][j][k][2] = k;
								}
								if (ps == 4) ps += 2;
							}
							for (int plus = 0; plus < 4; plus = plus + 3) {
								if (d[0 + plus] != 0) {
									d[1 + plus] = -dir*d[0 + plus];
									d[0 + plus] = 0;
								}
								else if (d[1 + plus] != 0) {
									d[0 + plus] = dir*d[1 + plus];
									d[1 + plus] = 0;
								}
							}
						}
					}
				}
			}
		}
	} //���ø���cube����ת״̬��������Ҫ���¾͸���dirition��������position��������MoveTo
	if (update == 1) {
	    for (int i = 0; i < 3; i++) {
	    	for (int j = 0; j < 3; j++) {
	    		for (int k = 0; k < 3; k++) {
	    			if (MoveTo[i][j][k][0] == -1) {
	    				temp[i][j][k] = Cube[i][j][k];
	    				for (int o = 0; o < 3; o++) {
						posTemp[i][j][k][o] = Cube[i][j][k]->getPosition()[o];
	    				}
	    			}
	    			else {
	    				temp[MoveTo[i][j][k][0]][MoveTo[i][j][k][1]][MoveTo[i][j][k][2]] = Cube[i][j][k];
		    			Cube[MoveTo[i][j][k][0]][MoveTo[i][j][k][1]][MoveTo[i][j][k][2]]->getPosition();
	    				for (int o = 0; o < 3; o++) {
	    					posTemp[MoveTo[i][j][k][0]][MoveTo[i][j][k][1]][MoveTo[i][j][k][2]][o] = Cube[MoveTo[i][j][k][0]][MoveTo[i][j][k][1]][MoveTo[i][j][k][2]]->getPosition()[o];
	    				}
	     			}
	    		}
	    	}
	    }
	    for (int i = 0; i < 3; i++) {
		    for (int j = 0; j < 3; j++) {
			    for (int k = 0; k < 3; k++) {
				    Cube[i][j][k] = temp[i][j][k];
				    Cube[i][j][k]->setPosition(posTemp[i][j][k]);
			    }
		    }
	    }
    }
}
//xyz = 0�� num = 1 ��Ϊ��ת x = 1 ��ƽ�� xyz = 1, num = 2��Ϊ��ת y = 2���棬���ƣ�num = 3Ϊͬʱ��ת3���棬������ħ��, num = -1 Ϊ��
//dir = -1/1Ϊ˳/��ʱ��, angleΪ��ת�Ƕȣ�updateΪ0�������Cube����,1Ϊ��Ҫ���¡�
