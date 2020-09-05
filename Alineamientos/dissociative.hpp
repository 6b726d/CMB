#pragma once

#include "needleman_wunsch.hpp"

class dissociative {
private:
	vector<string> nodes;
	vector<vector<double>> dmatrix;
	vector<bool> vrev;
	vector<double> vdist;
	vector<double> ndist;
	vector<double> vdiff;
	int max_pos = 0;
	string order = "";
	int count = 0;
public:
	dissociative(vector<string> _nodes, vector<vector<double>> _dmatrix);
	void calc_vdist();
	void calc_max_pos();
	void calc_ndist();
	void calc_vdiff();
	void g_join();
	void print();
	void to_txt(string file_name);
	string generate(string file_name);
};