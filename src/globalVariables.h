#pragma once

#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <algorithm>

#include "rubikInfo.h"
#include "RubikController.h"

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\AntTweakBar\AntTweakBar.h"

using namespace std;

TwBar *bar; // Pointer to the tweak bar

rubik* myRubik;
RubikController* controller;

string restore;
const string keys = "FfBbLlRrUuDdMmEeSsXxYyZz";

rubikInfo rubikInfoInstance;
GLfloat speed = 0.4;
GLfloat xadd = 0.4;
GLfloat yadd = 0.4;
GLfloat zadd = 0;
