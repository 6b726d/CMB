#pragma once

#include "needleman_wunsch.hpp"

class star_alignment {
private:
	vector<string> cads;
	vector<int> scores;
	int center = 0;				//Sc pos
	int sc_max = 0;				//Sc(max_size) pos
	vector<string> alignment;
public:
	star_alignment(vector<string> _cads);
	int calc_score(int i, int j);
	vector<vector<int>> gen_matrix();
	void calc_center();
	pair<string, string> p_sequence(int i, int j);
	vector<pair<string, string>> align_sequences();
	string mutation(string sc_cad, string cad);
	void multiple_alignment();
	void print();
};