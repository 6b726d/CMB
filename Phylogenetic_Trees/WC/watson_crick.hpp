#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

class watson_crick {
private:
	string arn;								//sequences
	vector<vector<array<int, 5>>> matrix;	//matrix (valor,|,-,/,.)
	array<int, 4> cmp;						//compare array
public:
	watson_crick(string _arn);
	int alpha(char ri, char rj);
	void create();
	void initialization();
	void generate();
	array<int, 2> find_min();
	void trace_back();
	void print_matrix();
	//void print();
};