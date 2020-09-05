#pragma once

#include <iostream>
#include <vector>

class matrix {
private:
	int rows;
	int cols;
	std::vector<int> mtx;
public:
	matrix();
	matrix(int r, int c);
	void resize(int r, int c);
	int operator()(int i, int j);
	void operator()(int i, int j, int val);
	void print();
};