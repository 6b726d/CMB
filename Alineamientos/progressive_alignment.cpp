#include "progressive_alignment.hpp"

progressive_alignment::progressive_alignment(vector<string> _nodes, vector<string> _cads) {
	nodes = _nodes;
	cads = _cads;
}

void progressive_alignment::print_matrix(vector<string> v, vector<vector<double>> m) {
	cout << "  ";
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j <= m[0].size(); j++) {
			if (j == 0) {
				cout << v[i] << " ";
			}
			else {
				cout << m[i][j - 1] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void progressive_alignment::txt_matrix(vector<string> v, vector<vector<double>> m, string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name);
	string line = "";
	if (myfile.is_open())
	{
		myfile << " ";
		for (int i = 0; i < v.size(); i++) {
			myfile << v[i] << " ";
		}
		myfile << "\n";
		for (int i = 0; i < m.size(); i++) {
			for (int j = 0; j <= m[0].size(); j++) {
				if (j == 0) {
					myfile << v[i] << " ";
				}
				else {
					line = d2s_precision(m[i][j - 1], 2);
					myfile << line << " ";
				}
			}
			myfile << "\n";
		}
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

double progressive_alignment::calc_dist(int i, int j, double constant) {
	double dist = 0.0;
	needleman_wunsch nw(cads[i], cads[j], 4, 3);
	dist = nw.getDist(constant);
	dist = round(dist * 100.0) / 100.0;
	return dist;
}

vector<vector<double>> progressive_alignment::calc_dist_matrix(double constant) {
	vector<vector<double>> dist_matrix(nodes.size());
	for (int i = 0; i < dist_matrix.size(); i++) {
		for (int j = 0; j < dist_matrix.size(); j++) {
			dist_matrix[i].push_back(calc_dist(i, j, constant));
		}
	}
	return dist_matrix;
}
