#include "pointing_matrix.hpp"
#include "needleman_wunsch.hpp"

int main() {
	
	//seq1, seq2, 1, -1, -2
	//seq1.size() < seq2.size() (no relevant)
	// TEST Begin
	//string seq1 = "GTAC";
	//string seq2 = "GTTGC";
	string seq3 = "CGAACTATTCGGACGC";
	string seq4 = "TCGGTAGAATCCGTCT";
	string seq5 = "CTGTGAGG";
	string seq6 = "TACACGCCTCTTCGCC";
	// TEST End
	//pointing_matrix pm1(seq1, seq2, 1, -1, -2);
	//pm1.generate();
	//pm1.print();
	//needleman_wunsch nw1(seq1, seq2, 2, 1);
	//nw1.pm_compare();
	cout << endl << seq3 << ", " << seq4 << endl;
	pointing_matrix pm2(seq3, seq4, 1, -1, -2);
	pm2.generate();
	pm2.print_alignment();
	needleman_wunsch nw2(seq3, seq4, 2, 1);
	nw2.pm_compare();
	cout << endl << seq5 << ", " << seq6 << endl;
	pointing_matrix pm3(seq5, seq6, 1, -1, -2);
	pm3.generate();
	pm3.print_alignment();
	needleman_wunsch nw3(seq5, seq6, 2, 1);
	nw3.pm_compare();
	

	/*
	// TABLE Begin
	//DNA
	dna s1(512);
	string seq1 = s1.get();
	dna s2(512);
	string seq2 = s2.get();
	//Pointing Matrix
	pointing_matrix pm(seq1, seq2, 1, -1, -2);
	pm.get_time();
	//Needleman Wunsch
	needleman_wunsch nw(seq1, seq2, 2, 1);
	nw.get_time();
	// TABLE End
	*/
}