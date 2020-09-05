#include "needleman_wunsch.hpp"

//(p > q)
needleman_wunsch::needleman_wunsch(string _cad1, string _cad2, int _p, int _q) {
	cad1 = _cad1;
	cad2 = _cad2;
	p = _p;
	q = _q;
}

needleman_wunsch::~needleman_wunsch() {
	cads.clear();
	scores.clear();
	best_cads.clear();
}

//3. Construir matriz
vector<vector<array<int, 4>>> needleman_wunsch::g_matrix() {
	//cad1(down), cad2(right)
	//array(val, bool(left), bool(diag), bool(up))
	int cols = gcad2.size();
	array<int, 4> a;
	a.fill(0);
	vector<array<int, 4>> row;
	int f_val = 0;
	for (int j = 0; j < cols; j++) {
		row.push_back(a);
		f_val -= 2;
		a[0] = f_val;		//val
		a[1] = 1;			//left
	}
	vector<vector<array<int, 4>>> res;
	res.push_back(row);
	//Matriz
	int rows = gcad1.size();
	f_val = -2;
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;
	for (int i = 1; i < rows; i++) {
		row[0][0] = f_val;	//val
		row[0][1] = 0;		//left
		row[0][3] = 1;		//up
		res.push_back(row);
		for (int j = 1; j < cols; j++) {
			//init
			res[i][j][1] = 0;
			res[i][j][2] = 0;
			res[i][j][3] = 0;
			//First Val
			val1 = res[i - 1][j - 1][0];
			if (gcad2[j] == gcad1[i]) {
				val1 += 1;					//diag
			}
			else {
				val1 -= 1;					//diag
			}
			//Second Val
			val2 = res[i - 1][j][0] - 2;	//up
			//Third Val
			val3 = res[i][j - 1][0] - 2;	//left
			//Compare Vals (0:val, 1:left, 2:diag, 3:up)
			//(val1:2, val2:3, val3:1)
			//val1 max
			if ((val1 >= val2) && (val1 >= val3)) {
				res[i][j][0] = val1;
				res[i][j][2] = 1;
				if (val1 == val2) {
					res[i][j][3] = 1;
				}
				if (val1 == val3) {
					res[i][j][1] = 1;
				}
			}
			//val2 max
			if ((val2 >= val1) && (val2 >= val3)) {
				res[i][j][0] = val2;
				res[i][j][3] = 1;
				if (val2 == val1) {
					res[i][j][2] = 1;
				}
				if (val2 == val3) {
					res[i][j][1] = 1;
				}
			}
			//val3 max
			if ((val3 >= val1) && (val3 >= val2)) {
				res[i][j][0] = val3;
				res[i][j][1] = 1;
				if (val3 == val1) {
					res[i][j][2] = 1;
				}
				if (val3 == val2) {
					res[i][j][3] = 1;
				}
			}
		}
		f_val -= 2;
	}
	return res;
}

void needleman_wunsch::getCads(vector<vector<array<int, 4>>> matrix) {
	int i = 0;
	int j = 0;
	pair<string, string> pcads;
	cads.push_back(pcads);
	bool del = false;
	int a_cads = 0;
	array<int, 3> a;
	a.fill(-1);
	vector<array<int, 3>> path;							//(i,j,p)
	int l_pos = 0;										//last pos of path
	int i_pos = 0;
	int j_pos = 0;
	int p_pos = 0;
	int n = 0;
	int m = 0;
	while (a_cads < cads.size()) {
		i = gcad1.size() - 1;
		j = gcad2.size() - 1;
		n = gcad1.size() - 1;
		m = gcad2.size() - 1;
		while ((i >= 0) && (j >= 0)) {
			//add
			if ((matrix[i][j][2] == 1) && (matrix[i][j][3] == 1)) {
				del = true;
			}
			//diag
			if (matrix[i][j][2] == 1) {
				if (del == true) {
					a[0] = i;
					a[1] = j;
					a[2] = 2;
					path.push_back(a);
				}
				cads[a_cads].second = gcad2[m] + cads[a_cads].second;
				cads[a_cads].first = gcad1[n] + cads[a_cads].first;
				m -= 1;	//
				n -= 1; //
				i -= 1;
				j -= 1;
			}
			//up
			else if (matrix[i][j][3] == 1) {
				if (del == true) {
					a[0] = i;
					a[1] = j;
					a[2] = 3;
					path.push_back(a);
				}
				cads[a_cads].second = '-' + cads[a_cads].second;
				cads[a_cads].first = gcad1[n] + cads[a_cads].first;
				n -= 1; //
				i -= 1;
			}
			//left
			else if (matrix[i][j][1] == 1) {
				if (del == true) {
					a[0] = i;
					a[1] = j;
					a[2] = 1;
					path.push_back(a);
				}
				cads[a_cads].second = gcad2[m] + cads[a_cads].second;
				cads[a_cads].first = '-' + cads[a_cads].first;
				m -= 1;	//
				j -= 1;
			}
			else {
				i -= 1;
				j -= 1;
			}
			del = false;
		}
		if (path.size() > 0) {
			l_pos = path.size() - 1;
			i_pos = path[l_pos][0];
			j_pos = path[l_pos][1];
			p_pos = path[l_pos][2];
			matrix[i_pos][j_pos][p_pos] = 0;
			cads.push_back(pcads);
		}
		path.clear();
		a_cads += 1;
	}
}

void needleman_wunsch::generate() {
	vector<string> cads1 = add_gab(cad1, cad2);
	gcad1 = cads1[0];
	gcad2 = cads1[1];
	vector<string> cads2 = max_2string(gcad1, gcad2);
	gcad1 = cads2[0];
	gcad2 = cads2[1];
	vector<vector<array<int, 4>>> matrix = g_matrix();
	matrixToTxt(matrix, "matrix");
	getCads(matrix);
	cadsToTxtNW(cads, "cads");
	score = matrix[matrix.size() - 1][matrix[0].size() - 1][0];
}

void needleman_wunsch::print() {
	cout << "Score: " << score << endl;
	cout << "Number of Strings: " << cads.size() << endl;
}

int needleman_wunsch::penalty(int pos) {
	int cp = 0;
	int cq = 0;
	if (cads[pos].second[0] == '-') {
		cp += 1;
	}
	for (int i = 1; i < cads[pos].second.size(); i++) {
		if (cads[pos].second[i] == '-') {
			if (cads[pos].second[i-1] == '-') {
				cq += 1;
			}
			else {
				cp += 1;
			}
		}
	}
	int penalty_score = (cp * p) + (cq * q);
	return -penalty_score;
}

void needleman_wunsch::f_best_cads() {
	//Calcular todas las penalidades
	scores.resize(cads.size());
	scores[0] = penalty(0);
	int max_val = scores[0];
	for (int i = 1; i < cads.size(); i++) {
		scores[i] = penalty(i);
		if (scores[i] > max_val) {
			max_val = scores[i];
		}
	}
	//Llenar los mejores
	pair<pair<string, string>, int> b_cad;
	for (int i = 0; i < scores.size(); i++) {
		if (scores[i] == max_val) {
			b_cad = make_pair(cads[i], scores[i]);
			best_cads.push_back(b_cad);
		}
	}
}

void needleman_wunsch::p_best_cads() {
	for (int i = 0; i < best_cads.size(); i++) {
		cout << best_cads[i].first.first << endl;
		cout << best_cads[i].first.second << endl;
		cout << best_cads[i].second << endl;
	}
	cout << endl;
}

int needleman_wunsch::getScore() {
	vector<string> cads1 = add_gab(cad1, cad2);
	gcad1 = cads1[0];
	gcad2 = cads1[1];
	vector<string> cads2 = max_2string(gcad1, gcad2);
	gcad1 = cads2[0];
	gcad2 = cads2[1];
	vector<vector<array<int, 4>>> matrix = g_matrix();
	return matrix[matrix.size() - 1][matrix[0].size() - 1][0];
}

pair<string, string> needleman_wunsch::best_cad() {
	vector<string> cads1 = add_gab(cad1, cad2);
	gcad1 = cads1[0];
	gcad2 = cads1[1];
	vector<string> cads2 = max_2string(gcad1, gcad2);
	gcad1 = cads2[0];
	gcad2 = cads2[1];
	vector<vector<array<int, 4>>> matrix = g_matrix();
	getCads(matrix);
	score = matrix[matrix.size() - 1][matrix[0].size() - 1][0];
	f_best_cads();
	return best_cads[0].first;
}

double needleman_wunsch::getDist(double constant) {
	vector<string> cads1 = add_gab(cad1, cad2);
	gcad1 = cads1[0];
	gcad2 = cads1[1];
	vector<string> cads2 = max_2string(gcad1, gcad2);
	gcad1 = cads2[0];
	gcad2 = cads2[1];
	vector<vector<array<int, 4>>> matrix = g_matrix();
	getCads(matrix);
	f_best_cads();
	pair<string,string> b_cad = best_cads[0].first; //2 cads
	//Calc Dist
	double dist = 0;
	double dif_pos = 0;
	double alig_pos = 0;
	for (int i = 0; i < b_cad.first.size(); i++) {
		if ((b_cad.first[i] == '-') || (b_cad.second[i] == '-')) {
			if (b_cad.first[i] != b_cad.second[i]) {
				dif_pos += 1;
			}
		}
		else if ((b_cad.first[i] != '-') && (b_cad.second[i] != '-')) { //Not necessary
			alig_pos += 1;
		}
	}
	dist = dif_pos / alig_pos;
	return dist * constant;
}
