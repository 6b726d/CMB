#pragma once

#include "func_alignments.hpp"

class needleman_wunsch {
private:
	string cad1 = "";
	string cad2 = "";
	int p = 0;
	int q = 0;
	string gcad1 = "";
	string gcad2 = "";
	int score = 0;
	vector<pair<string, string>> cads;
	vector<int> scores;									//scores with penalty
	vector<pair<pair<string, string>, int>> best_cads;	//best_cads (penalty)
public:
	needleman_wunsch(string _cad1, string _cad2, int _p, int _q);
	~needleman_wunsch();
	vector<vector<array<int, 4>>> g_matrix();
	void getCads(vector<vector<array<int, 4>>> matrix);
	void generate();
	void print();
	int penalty(int pos);
	void f_best_cads();
	void p_best_cads();
	//Special (Star)
	int getScore();
	pair<string, string> best_cad();
	//Special (Progressive)
	double getDist(double constant);
};
