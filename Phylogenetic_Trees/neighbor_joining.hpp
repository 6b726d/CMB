#pragma once

#pragma once

#define GLUT_DISABLE_ATEXIT_HACK

#include "func.hpp"
#include <GL/freeglut.h>

class neighbor_joining {
private:
	vector<string> nodes;
	vector<vector<double>> dmatrix;
	vector<vector<double>> qmatrix;
	vector<double> uvector; //u_i, u_j
	vector<pair<array<string, 2>, array<double, 2>>> tree_values;
	//Nodes
	vector<pair<string, pair<int, int>>> tree_nodes;
public:
	neighbor_joining(vector<string> _nodes, vector<vector<double>> _dmatrix);
	void calc_uvector();
	pair<int, int> calc_min_pos();
	void update();
	//void const_tree();
	void dmatrixToTxt(string file_name);
	void tree_valuesToTxt(string file_name);
	void generate();
	bool findNode(string node, pair<int, int> &pos);
	void drawText(string text, double x, double y);
	void display();
};
