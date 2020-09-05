#include "pointing_matrix.hpp"

pointing_matrix::pointing_matrix(string _seq1, string _seq2, int _mr, int _mp, int _gp) {
	seq1 = _seq1;
	seq2 = _seq2;
	mr = _mr;
	mp = _mp;
	gp = _gp;
	//matrix
	n = seq1.size();
	m = seq2.size();
	point_mat.resize(n + 1, m + 1);
	score_mat.resize(2, m + 1);
	//sequences
	seq1 = '-' + seq1;
	seq2 = '-' + seq2;
}

void pointing_matrix::initialization() {
	//score_mat
	int val = 0;
	for (int j = 0; j <= m; j++) {
		score_mat(0, j, val);
		val--;
	}
	score_mat(1, 0, -1);
	
	//point_mat
	for (int j = 1; j <= m; j++) {
		point_mat(0, j, 3);
	}
	for (int i = 1; i <= n; i++) {
		point_mat(i, 0, 1);
	}
}

void pointing_matrix::formation() {
	int sm_or = 0;			//score matrix old row
	int sm_cr = 1;			//score matrix current row
	int cs = 0;				//score value of a matrix cell
	int pointer = 0;		//direction pointer of a cell in point_mat
	int val_max = 0;		//max value
	//BEGIN
	sm_cr = 1;
	for (int i = 1; i <= n; i++) {
		sm_or = 1 - sm_cr;
		for (int j = 1; j <= m; j++) {
			if (seq1[i] == seq2[j]) {
				cs = mr;
			}
			else {
				cs = mp;
			}
			val_max = score_mat(sm_or, j - 1) + cs;
			pointer = 2;
			if (val_max < (score_mat(sm_or, j) + gp)) {
				val_max = score_mat(sm_or, j) + gp;
				pointer = 1;
			}
			if (val_max < (score_mat(sm_cr, j - 1) + gp)) {
				val_max = score_mat(sm_cr, j - 1) + gp;
				pointer = 3;
			}
			score_mat(sm_cr, j, val_max);
			point_mat(i, j, pointer);
		}
		sm_cr = sm_or;
	}
	//END
}

void pointing_matrix::print_matrix() {
	score_mat.print();
	point_mat.print();
}

void pointing_matrix::alignment() {
	score = 0;
	real_score = 0;
	int row = n;
	int col = m;
	while (point_mat(row, col) != 0) {
		if (point_mat(row, col) == 3) {
			seq1_as += '-';
			seq2_as += seq2[col];
			col -= 1;
			score -= 1;
			real_score += gp;
		}
		else if (point_mat(row, col) == 1) {
			seq1_as += seq1[row];
			seq2_as += '-';
			row -= 1;
			score -= 1;
			real_score += gp;
		}
		else if (point_mat(row, col) == 2) {
			seq1_as += seq1[row];
			seq2_as += seq2[col];
			if (seq1[row] == seq2[col]) {
				score += 1;
				real_score += mr;
			}
			else {
				score -= 1;
				real_score += mp;
			}
			row -= 1;
			col -= 1;
		}
	}
}

void pointing_matrix::sort_alignment() {
	string s1_as = seq1_as;
	string s2_as = seq2_as;
	seq1_as = string(s1_as.rbegin(), s1_as.rend());
	seq2_as = string(s2_as.rbegin(), s2_as.rend());
}

void pointing_matrix::print_alignment() {
	cout << "S1: " << seq1_as << endl;
	cout << "S2: " << seq2_as << endl;
	cout << "Score: " << score << endl;
	cout << "Real_Score: " << real_score << endl;
}

void pointing_matrix::generate() {
	initialization();
	formation();
	alignment();
	sort_alignment();
}

void pointing_matrix::print() {
	print_matrix();
	print_alignment();
}

void pointing_matrix::get_time() {
	//Pointing Matrix Formation
	chrono::time_point<chrono::system_clock> Formation_Start, Formation_End;
	cout << "Pointing Matrix Formation ..." << endl;
	Formation_Start = chrono::system_clock::now();
	initialization();
	formation();
	Formation_End = chrono::system_clock::now();
	cout << "Pointing Matrix Formation Complete. Time: " << chrono::duration_cast<chrono::nanoseconds>(Formation_End - Formation_Start).count() << "ns." << endl;
	//Sequence Alignment
	chrono::time_point<chrono::system_clock> Alignment_Start, Alignment_End;
	cout << "Sequence Alignment ..." << endl;
	Alignment_Start = chrono::system_clock::now();
	alignment();
	sort_alignment();
	Alignment_End = chrono::system_clock::now();
	cout << "Sequence Alignment Complete. Time: " << chrono::duration_cast<chrono::nanoseconds>(Alignment_End - Alignment_Start).count() << "ns." << endl;
}
