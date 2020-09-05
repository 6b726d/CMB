#pragma once

#include "func.hpp"

class additive_distance {
private:
	vector<string> nodes;
	vector<vector<int>> dmatrix;
	bool end = false;
	//Graphics
	vector<int> vec_alpha;
	//vector<int> vec_transitive;
	vector<string> vec_transitive;
	vector<pair<vector<string>, vector<int>>> tree;
	//Values
	vector<pair<int, pair<double, double>>> branches;	//val,x,y
	vector<pair<int, double>> lines;					//val,x
	vector<double> pos_line;							//xpos
public:
	additive_distance(vector<string> _nodes, vector<vector<int>> dmatrix);
	int calc_min();
	int calc_alpha();
	void calc_dmatrix_alpha();
	int calc_transitive_pos();
	void calc_dmatrix_transitive();
	void dmatrixToTxt(string file_name);
	void printValues();
	void generate();
	//graphics
	bool findNode(string node, int p, int &pos);
	void findPosVal(double pos, double unit);
	pair<int, int> findPosAlpha();
	void display();
};