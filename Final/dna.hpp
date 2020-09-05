#pragma once

#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

//ADN: A, G, C, T
class dna {
private:
	string acgt;
	int size;
	string seq;
public:
	dna(int _size);
	char rand_base();
	void gen_seq();
	string get();
};