#include "watson_crick.hpp"

watson_crick::watson_crick(string _arn) {
	arn = _arn;
}

int watson_crick::alpha(char ri, char rj) {
	int score = 0;
	if (((ri == 'C') and (rj == 'G')) or ((ri == 'G') and (rj == 'C'))) {
		score = -1;
	}
	else if (((ri == 'A') and (rj == 'U')) or ((ri == 'U') and (rj == 'A'))) {
		score = -1;
	}
	else {
		score = 0;
	}
	return score;
}

void watson_crick::create() {
	vector<array<int, 5>> row(arn.size());
	for (int i = 0; i < arn.size(); i++) {
		matrix.push_back(row);
	}
}

void watson_crick::initialization() {
	create();
	matrix[0][0][0] = 0;
	for (int i = 1; i < matrix.size(); i++) {
		matrix[i][i-1][0] = 0;
		matrix[i][i][0] = 0;
	}
}

void watson_crick::generate() {
	initialization();
	int j = 0;
	int cmp_k = 1;		//min
	int val_k = 0;
	int min_val = 0;
	for (int d = 1; d < arn.size(); d++) {
		for (int i = 0; i + d < arn.size(); i++) {
			j = i + d;
			//cout << "i: " << i << ", j: " << j << ", i+1:" << i + 1 << ", j-1:" << j - 1 << endl;
			cmp[0] = matrix[i + 1][j][0];	//(|)
			cmp[1] = matrix[i][j - 1][0];	//(-)
			cmp[2] = matrix[i + 1][j - 1][0] + alpha(arn[i], arn[j]);	//(/)
			//k
			if ((j - i) > 2) {
				//min_k
				cmp_k = matrix[i][i + 1][0] + matrix[i + 2][j][0];
				for (int k = i + 2; k < j; k++) {
					val_k = matrix[i][k][0] + matrix[k + 1][j][0];
					if (val_k < cmp_k) {
						cmp_k = val_k;
					}
				}
			}
			cmp[3] = cmp_k;
			min_val = cmp[0];
			for (int p = 1; p < 3; p++) {
				if (cmp[p] < min_val) {
					min_val = cmp[p];
				}
			}
			//trace_back
			for (int p = 0; p < 4; p++) {
				if (min_val == cmp[p]) {
					matrix[i][j][p + 1] = 1;
				}
			}
			//value
			matrix[i][j][0] = min_val;
			cmp_k = 1;
		}
		//cout << endl;
	}
}

array<int, 2> watson_crick::find_min() {
	array<int, 2> pos;
	int min_val = 0;
	for (int i = 0; i < arn.size(); i++) {
		for (int j = i; j < arn.size(); j++) {
			if (matrix[i][j][0] < min_val) {
				min_val = matrix[i][j][0];
				pos[0] = i;
				pos[1] = j;
			}
		}
	}
	return pos;
}

void watson_crick::trace_back() {
	array<int, 2> pos = find_min();
	int i = pos[0];
	int j = pos[1];
	cout << "  ___" << endl;
	while (matrix[i][j][0] != 0) {
		// 3/, 2-, 1|
		if (matrix[i][j][3] == 1) {
			cout << "  " << arn[i] << "-" << arn[j] << endl;
			cout << "  | |" << endl;
			i += 1;
			j -= 1;
		}
		else {
			if (matrix[i][j][2] == 1) {
				//Bucle
				cout << " /   \\" << endl;
				cout << "|     " << arn[j] << endl;
				cout << " \\   /" << endl;
				cout << "  | |" << endl;
				j -= 1;
			}
			else if (matrix[i][j][1] == 1) {
				//Bucle
				cout << " /   \\" << endl;
				cout << arn[i] << "     |" << endl;
				cout << " \\   /" << endl;
				cout << "  | |" << endl;
				i += 1;
			}
			else {
				//Bucle
				cout << " /   \\" << endl;
				cout << "|     |" << endl;
				cout << " \\   /" << endl;
				cout << "  | |" << endl;
				//i?
				//j?
			}
		}
	}
	//Bucle
	cout << " /   \\" << endl;
	cout << arn[i] << "     " << arn[j] << endl;
	cout << " \\___/" << endl;
}

void watson_crick::print_matrix() {
	//cout << arn << endl;
	for (int i = 0; i < arn.size(); i++) {
		for (int j = 0; j < arn.size(); j++) {
			cout << matrix[i][j][0] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}