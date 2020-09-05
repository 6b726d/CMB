#include "matrix.hpp"

matrix::matrix() {
	rows = 0;
	cols = 0;
}

matrix::matrix(int r, int c) {
	rows = r;
	cols = c;
	mtx.resize(r*c);
}

void matrix::resize(int r, int c) {
	rows = r;
	cols = c;
	mtx.resize(r*c);
}

int matrix::operator()(int i, int j) {
	int pos = (i * cols) + j;
	return mtx[pos];
}

void matrix::operator()(int i, int j, int val) {
	int pos = (i * cols) + j;
	mtx[pos] = val;
}

void matrix::print() {
	int pos = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			pos = (i * cols) + j;
			std::cout << mtx[pos] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
