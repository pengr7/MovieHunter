#pragma once

#include "rubik.h"
#include "rubikInfo.h"
#include <fstream>
#include <string>
using namespace std;

rubikInfo readFromFile();
void writeToFile(rubik* rubik_);
