#include "func_alignments.hpp"

void matrixToTxt(vector<vector<array<int, 4>>> m, string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name);
	string line = "";
	if (myfile.is_open())
	{
		for (int i = 0; i < m.size(); i++) {
			for (int j = 0; j < m[0].size(); j++) {
				line = to_string(m[i][j][0]) + "(" + to_string(m[i][j][1]) + "," + to_string(m[i][j][2]) + "," + to_string(m[i][j][3]) + ") ";
				myfile << line;
			}
			myfile << "\n";
		}
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

void iMatrixToTxt(vector<vector<int>> m, vector<int> v, string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name);
	string line = "";
	if (myfile.is_open())
	{
		for (int i = 0; i < m.size(); i++) {
			for (int j = 0; j < m[0].size(); j++) {
				line = to_string(m[i][j]) + " ";
				myfile << line;
			}
			myfile << "\n";
		}
		myfile << "\n";
		for (int i = 0; i < v.size(); i++) {
			line = to_string(v[i]) + " ";
			myfile << line;
		}
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

void cadsToTxtNW(vector<pair<string, string>> cads, string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name);
	string line = "";
	if (myfile.is_open())
	{
		for (int i = 0; i < cads.size(); i++) {
			myfile << cads[i].first << "\n";
			myfile << cads[i].second << "\n";
			myfile << "\n";
		}
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

void cadsToTxtSW(vector<string> cads, string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name);
	string line = "";
	if (myfile.is_open())
	{
		for (int i = 0; i < cads.size(); i++) {
			myfile << cads[i] << "\n";
		}
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

void cadsToTxt(vector<string> cads, string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name);
	string line = "";
	if (myfile.is_open())
	{
		for (int i = 0; i < cads.size(); i++) {
			myfile << cads[i] << "\n";
		}
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

void printMatrix(vector<vector<array<int, 4>>> m) {
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[0].size(); j++) {
			cout << m[i][j][0] << "(" << m[i][j][1] << "," << m[i][j][2] << "," << m[i][j][3] << ") ";
		}
		cout << endl;
	}
	cout << endl;
}

void printCadsNW(vector<pair<string, string>> cads) {
	for (int i = 0; i < cads.size(); i++) {
		cout << cads[i].first << endl;
		cout << cads[i].second << endl;
		cout << endl;
	}
	cout << endl;
}

void printCadsSW(vector<string> cads) {
	for (int i = 0; i < cads.size(); i++) {
		cout << cads[i] << endl;
	}
	cout << endl;
}

//1. An~adir guiones al inicio de las cadenas
vector<string> add_gab(string cad1, string cad2) {
	vector<string> res;
	string n_cad1 = "-" + cad1;
	string n_cad2 = "-" + cad2;
	res.push_back(n_cad1);
	res.push_back(n_cad2);
	return res;
}

//2. Devuelve 2 cadenas ordenados de mayor a menor
vector<string> max_2string(string cad1, string cad2) {
	vector<string> res;
	if (cad2.size() > cad1.size()) {
		res.push_back(cad2);
		res.push_back(cad1);
	}
	else {
		res.push_back(cad1);
		res.push_back(cad2);
	}
	return res;
}

string d2s_precision(double num, int precision) {
	stringstream ss;
	ss << fixed << setprecision(precision) << num;
	string s = ss.str();
	return s;
}
