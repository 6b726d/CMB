#include "star_alignment.hpp"

star_alignment::star_alignment(vector<string> _cads) {
	cads = _cads;
}

int star_alignment::calc_score(int i, int j) {
	needleman_wunsch nw(cads[i], cads[j], 4 , 3);
	int score = nw.getScore();
	return score;
}

vector<vector<int>> star_alignment::gen_matrix() {
	int score = 0;
	int r_score = 0;
	vector<vector<int>> matrix(cads.size());
	for (int i = 0; i < cads.size(); i++) {
		for (int j = 0; j < cads.size(); j++) {
			if (j > i) {
				score = calc_score(i, j);
				matrix[i].push_back(score);
			}
			else if (j < i) {
				score = matrix[j][i];
				matrix[i].push_back(score);
			}
			else {
				score = 0;
				matrix[i].push_back(score);
			}
			r_score += score;
		}
		scores.push_back(r_score);
		r_score = 0;
	}
	return matrix;
}

void star_alignment::calc_center() {
	int max_val = scores[0];
	int pos = 0;
	for (int i = 1; i < scores.size(); i++) {
		if (scores[i] > max_val) {
			max_val = scores[i];
			pos = i;
		}
	}
	center = pos;
}

pair<string, string> star_alignment::p_sequence(int i, int j) {
	needleman_wunsch nw(cads[i], cads[j], 4, 3);
	pair<string, string> sequence = nw.best_cad();
	//special begin
	string cad1 = sequence.first;
	string cad2 = sequence.second;
	if (cads[j].size() > cads[i].size()) {
		sequence.first = cad2;
		sequence.second = cad1;
	}
	//special end
	return sequence;
}

vector<pair<string, string>> star_alignment::align_sequences() {
	vector<pair<string, string>> sequences;
	pair<string, string> sequence;
	int max_size = 0;
	int it = -1;					//no pointer
	int pos = 0;
	for (int i = 0; i < cads.size(); i++) {
		if (i != center) {
			sequence = p_sequence(center, i);
			sequences.push_back(sequence);
			it += 1;
			//cout << "First: " << sequence.first.size() << endl;
			//cout << "Second: " << sequence.second.size() << endl;
			if (sequence.first.size() > max_size) {
				max_size = sequence.first.size();
				pos = it;
			}
		}
	}
	//cout << "Size: " << max_size << endl;
	sc_max = pos;
	return sequences;
}

string star_alignment::mutation(string sc_cad, string cad) {
	needleman_wunsch nw(sc_cad, cad, 4, 3);
	pair<string, string> sequence = nw.best_cad();
	return sequence.second;//'
}

//??
void star_alignment::multiple_alignment() {
	vector<vector<int>> matrix = gen_matrix();
	iMatrixToTxt(matrix, scores, "imatrix");
	calc_center();
	vector<pair<string, string>> sequences = align_sequences();
	string sc_cad = sequences[sc_max].first;//'?
	alignment.push_back(sc_cad);
	int c_size = sc_cad.size();
	string cad = "";
	string n_sequence = "";
	for (int i = 0; i < sequences.size(); i++) {
		cad = sequences[i].second;
		if (cad.size() < c_size) {
			n_sequence = mutation(sc_cad, cad);
			alignment.push_back(n_sequence);
		}
		else {
			alignment.push_back(cad);
		}
	}
	cadsToTxt(alignment, "alignment");
}

void star_alignment::print() {
	cout << "Sc: " << cads[center] << endl;
	cout << "Sc(score): " << scores[center] << endl;
 }
