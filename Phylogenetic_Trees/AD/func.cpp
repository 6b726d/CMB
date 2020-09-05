#include "func.hpp"

string d2s_precision(double num, int precision) {
	stringstream ss;
	ss << fixed << setprecision(precision) << num;
	string s = ss.str();
	return s;
}

void drawText(string text, double x, double y) {
	glRasterPos2d(x, y);
	//glColor3f(1.0f, 1.0f, 1.0f);
	const unsigned char* c_text = (const unsigned char*)text.c_str();
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, c_text);
}
