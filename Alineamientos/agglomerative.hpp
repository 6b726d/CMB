#pragma once

#include "needleman_wunsch.hpp"

class agglomerative {
private:
	vector<string> nodes;
	vector<vector<double>> dmatrix;
	pair<int, int> min_pos;
	vector<int> other_pos;
	//Cophenetic
	vector<vector<double>> cmatrix;
	vector<vector<int>> cpos;
	//ccc
	vector<double> xs;
	vector<double> ys;
public:
	agglomerative(vector<string> _nodes, vector<vector<double>> _dmatrix);
	void print_nodes_matrix(vector<string> v, vector<vector<double>> m);
	void txt_nodes_matrix(vector<string> v, vector<vector<double>> m, string file_name);
	void calc_min_pos();
	void calc_dmatrix(int type);
	void gen_cmatrix();
	pair<double,double> avg(vector<vector<double>> dmatrix0);
	void gen_xs_ys(vector<vector<double>> dmatrix0);
	double gen_ccc(vector<vector<double>> dmatrix0);
	void generate(string file_name, int type);
};