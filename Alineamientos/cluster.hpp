#pragma once

#include "agglomerative.hpp"
#include "dissociative.hpp"

class cluster {
private:
	vector<string> nodes;
	vector<string> cads;
	vector<vector<double>> dmatrix;
public:
	cluster(vector<string> _nodes, vector<string> _cads);
	double calc_dist(int i, int j, double constant);
	void calc_dmatrix(double constant);
	void generate(string file_name, double constant, bool cluster_type, int a_type);
};