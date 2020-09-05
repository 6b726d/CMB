#pragma once

#define GLUT_DISABLE_ATEXIT_HACK

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <vector>
#include <string>
#include <array>
#include <cmath>

#include <GL/freeglut.h>

using namespace std;

string d2s_precision(double num, int precision);

void drawText(string text, double x, double y);
