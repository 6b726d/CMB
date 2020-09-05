#include "smith_waterman.hpp"

smith_waterman::smith_waterman(string _cad1, string _cad2) {
	cad1 = _cad1;
	cad2 = _cad2;
}

smith_waterman::~smith_waterman() {
	cads.clear();
}

//3. Construir matriz
vector<vector<array<int, 4>>> smith_waterman::g_matrix() {
	//cad1(down), cad2(right)
	//array(val, bool(left), bool(diag), bool(up))
	int cols = gcad2.size();
	array<int, 4> a;
	a.fill(0);
	vector<array<int, 4>> row;
	for (int j = 0; j < cols; j++) {
		row.push_back(a);
	}
	int max_val = 0;
	vector<vector<array<int, 4>>> res;
	res.push_back(row);
	//Matriz
	int rows = gcad1.size();
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;
	for (int i = 1; i < rows; i++) {
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
			if ((val1 >= val2) && (val1 >= val3) && (val1 >= 0)) {
				res[i][j][0] = val1;
				res[i][j][2] = 1;
				if (val1 == val2) {
					res[i][j][3] = 1;
				}
				if (val1 == val3) {
					res[i][j][1] = 1;
				}
				if (val1 > max_val) {
					max_val = val1;
				}
			}
			//val2 max
			if ((val2 >= val1) && (val2 >= val3) && (val2 >= 0)) {
				res[i][j][0] = val2;
				res[i][j][3] = 1;
				if (val2 == val1) {
					res[i][j][2] = 1;
				}
				if (val2 == val3) {
					res[i][j][1] = 1;
				}
				if (val2 > max_val) {
					max_val = val2;
				}
			}
			//val3 max
			if ((val3 >= val1) && (val3 >= val2) && (val3 >= 0)) {
				res[i][j][0] = val3;
				res[i][j][1] = 1;
				if (val3 == val1) {
					res[i][j][2] = 1;
				}
				if (val3 == val2) {
					res[i][j][3] = 1;
				}
				if (val3 > max_val) {
					max_val = val3;
				}
			}
			// 0 max
			if ((0 >= val1) && (0 >= val2) && (0 >= val3)) {
				if (0 == val1) {
					res[i][j][2] = 1;
				}
				if (0 == val2) {
					res[i][j][3] = 1;
				}
				if (0 == val3) {
					res[i][j][1] = 1;
				}
			}
		}
	}
	score = max_val;
	return res;
}

void smith_waterman::getCads(vector<vector<array<int, 4>>> matrix) {
	for (int i = 0; i < gcad1.size(); i++) {
		for (int j = 0; j < gcad2.size(); j++) {
			if (matrix[i][j][0] == score) {
				cout << matrix[i][j][0] << ":(" << i << "," << j << ")" << endl;
				getSubCads(matrix, i, j);
			}
		}
	}
}

void smith_waterman::getSubCads(vector<vector<array<int, 4>>> matrix, int r, int c) {
	vector<string> subcads;
	int i = 0;
	int j = 0;
	string cad = "";
	subcads.push_back(cad);
	bool del = false;
	int a_subcads = 0;
	array<int, 3> a;
	a.fill(-1);
	vector<array<int, 3>> path;							//(i,j,p)
	int l_pos = 0;										//last pos of path
	int i_pos = 0;
	int j_pos = 0;
	int p_pos = 0;
	int n = 0;
	while (a_subcads < subcads.size()) {
		i = r;
		j = c;
		n = j;
		while (matrix[i][j][0] > 0) {
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
				subcads[a_subcads] = gcad2[n] + subcads[a_subcads];
				n -= 1;	//
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
				subcads[a_subcads] = '-' + subcads[a_subcads];
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
				subcads[a_subcads] = gcad2[n] + subcads[a_subcads];
				n -= 1;	//
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
			subcads.push_back(cad);
		}
		path.clear();
		cads.push_back(subcads[a_subcads]);
		a_subcads += 1;
	}
}

void smith_waterman::generate() {
	vector<string> cads1 = add_gab(cad1, cad2);
	gcad1 = cads1[0];
	gcad2 = cads1[1];
	vector<string> cads2 = max_2string(gcad1, gcad2);
	gcad1 = cads2[0];
	gcad2 = cads2[1];
	vector<vector<array<int, 4>>> matrix = g_matrix();
	//printMatrix(matrix);
	matrixToTxt(matrix, "matrix");
	getCads(matrix);
	cadsToTxtSW(cads, "cads");
}

void smith_waterman:: print() {
	printCadsSW(cads);
	cout << "Score: " << score << endl;
	cout << "Number of Strings: " << cads.size() << endl;
}
