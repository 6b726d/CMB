#pragma once

#include "dna.hpp"
#include "matrix.hpp"
#include <chrono>

class pointing_matrix {
private:
	string seq1;		//sequence1
	string seq2;		//sequence2
	matrix score_mat;	//score matrix
	matrix point_mat;	//point matrix
	int mr;				//match reward
	int mp;				//mismatch penalty
	int gp;				//gap penalty
	int n;				//size of sequence2
	int m;				//size of sequence1
	int score;			//paper score gp = -1
	int real_score;		//real score gp = -2
	string seq1_as;		//alignment sequence1
	string seq2_as;		//alignment sequence2
public:
	pointing_matrix(string _seq1, string _seq2, int _mr, int _mp, int _gp);
	void initialization();
	void formation();
	void print_matrix();
	void alignment();
	void sort_alignment();
	void print_alignment();
	void generate();
	void print();
	void get_time();
};