#pragma once

#include "needleman_wunsch.hpp"

class neighbor_joining {
private:
	vector<string> nodes;
	vector<vector<double>> dist_matrix;
	vector<double> scores;
	vector<vector<double>> q_matrix;
	pair<int, int> min_pos;
	vector<int> other_pos;
public:
	neighbor_joining(vector<string> _nodes, vector<vector<double>> _dist_matrix);
	void print_scores(vector<double> v);
	void print_matrix(vector<string> v, vector<vector<double>> m);
	void print_nodes_matrix(vector<string> v, vector<vector<double>> m);
	void txt_scores(vector<double> v, string file_name);
	void txt_matrix(vector<string> v, vector<vector<double>> m, string file_name);
	void txt_nodes_matrix(vector<string> v, vector<vector<double>> m, string file_name, bool type);
	void calc_scores();
	void calc_q_matrix();
	void calc_dist_matrix();
	void generate(string file_name);
};
