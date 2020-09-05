#pragma once

#define GLUT_DISABLE_ATEXIT_HACK

#include "func.hpp"
#include <GL/freeglut.h>

class upgma {
private:
	vector<string> nodes;
	vector<vector<double>> dmatrix;
	vector<pair<array<string, 2>, double>> tree_values;
	//Nodes
	vector<pair<string, pair<int, int>>> tree_nodes;
	vector<double> tree_nodes_values;
public:
	upgma(vector<string> _nodes, vector<vector<double>> _dmatrix);
	pair<int, int> calc_min_pos();
	void update();
	//void const_tree();
	void dmatrixToTxt(string file_name);
	void tree_valuesToTxt(string file_name);
	void generate();
	bool findNode(string node, pair<int,int> &pos, int &p);
	void drawText(string text, double x, double y);
	void display();
};
