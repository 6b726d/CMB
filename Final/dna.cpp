#include "dna.hpp"

dna::dna(int _size) {
	acgt = "ACGT";
	size = _size;
}

char dna::rand_base() {
	return acgt[rand() % 4];
}

void dna::gen_seq() {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		seq += rand_base();
	}
}

string dna::get() {
	gen_seq();
	return seq;
}
