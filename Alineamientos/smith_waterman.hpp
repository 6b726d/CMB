#pragma once

#include "func_alignments.hpp"

class smith_waterman {
private:
	string cad1 = "";
	string cad2 = "";
	string gcad1 = "";
	string gcad2 = "";
	int score = 0;
	vector<string> cads;
public:
	smith_waterman(string _cad1, string _cad2);
	~smith_waterman();
	vector<vector<array<int, 4>>> g_matrix();
	void getCads(vector<vector<array<int, 4>>> matrix);
	void getSubCads(vector<vector<array<int, 4>>> matrix, int r, int c);
	void generate();
	void print();
};
