#include "fileIO.h"

rubikInfo readFromFile() {
	rubikInfo rubikInfoInstance;
	ifstream fin("rubikInfo.avi");

	GLfloat RubikPosition_[3];
	GLfloat RubikColor_[6][3];
	GLfloat RubikLength_;

	for (int i = 0; i < 3; ++i)
		fin >> RubikPosition_[i];
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 3; ++j)
			fin >> RubikColor_[i][j];
	fin >> RubikLength_;

	rubikInfoInstance.setRubikPosition(RubikPosition_);
	rubikInfoInstance.setRubikColor(RubikColor_);
	rubikInfoInstance.setRubikLength(RubikLength_);

	return rubikInfoInstance;
}

void writeToFile(rubik* rubik_) {
	ofstream fout("rubikInfo.avi");
	for (int i = 0; i < 3; ++i)
		fout << rubik_->getPosition()[i] << ' ';
	fout << endl;
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 3; ++j)
			fout << rubik_->getColor(i)[j] << ' ';
	fout << endl;
	fout << rubik_->getLength() << endl;
}
