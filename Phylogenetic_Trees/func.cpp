#include "func.hpp"

string d2s_precision(double num, int precision) {
	stringstream ss;
	ss << fixed << setprecision(precision) << num;
	string s = ss.str();
	return s;
}
