#pragma once

#include "neighbor_joining.hpp"

class progressive_alignment {
private:
	vector<string> nodes;
	vector<string> cads;
public:
	progressive_alignment(vector<string> _nodes, vector<string> _cads);
	void print_matrix(vector<string> v, vector<vector<double>> m);
	void txt_matrix(vector<string> v, vector<vector<double>> m, string file_name);
	double calc_dist(int i, int j, double constant);
	vector<vector<double>> calc_dist_matrix(double constant);
};
