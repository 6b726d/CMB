#include "neighbor_joining.hpp"

neighbor_joining::neighbor_joining(vector<string> _nodes, vector<vector<double>> _dist_matrix) {
	nodes = _nodes;
	dist_matrix = _dist_matrix;
}

void neighbor_joining::print_scores(vector<double> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	cout << endl;
}

void neighbor_joining::print_matrix(vector<string> v, vector<vector<double>> m) {
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

void neighbor_joining::print_nodes_matrix(vector<string> v, vector<vector<double>> m) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[0].size(); j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void neighbor_joining::txt_scores(vector<double> v, string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name, ofstream::app);
	string line = "";
	if (myfile.is_open())
	{
		myfile << "Scores (D Matrix): \n";
		for (int i = 0; i < v.size(); i++) {
			line = d2s_precision(v[i], 2);
			myfile << line << "\t";
		}
		myfile << "\n";
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

void neighbor_joining::txt_matrix(vector<string> v, vector<vector<double>> m, string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name, ofstream::app);
	string line = "";
	if (myfile.is_open())
	{
		myfile << "\t";
		for (int i = 0; i < v.size(); i++) {
			myfile << v[i] << "\t";
		}
		myfile << "\n";
		for (int i = 0; i < m.size(); i++) {
			for (int j = 0; j <= m[0].size(); j++) {
				if (j == 0) {
					myfile << v[i] << "\t";
				}
				else {
					line = d2s_precision(m[i][j - 1], 2);
					myfile << line << "\t";
				}
			}
			myfile << "\n";
		}
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

void neighbor_joining::txt_nodes_matrix(vector<string> v, vector<vector<double>> m, string file_name, bool type) {
	file_name += ".txt";
	ofstream myfile(file_name, ofstream::app);
	string line = "";
	if (myfile.is_open())
	{
		if (type == true) {
			myfile << "D Matrix \n";
		}
		else {	//0
			myfile << "Q Matrix \n";
		}
		for (int i = 0; i < v.size(); i++) {
			myfile << v[i] << "\t";
		}
		myfile << endl;
		for (int i = 0; i < m.size(); i++) {
			for (int j = 0; j < m[0].size(); j++) {
				line = d2s_precision(m[i][j], 2);
				myfile << line << "\t";
			}
			myfile << "\n";
		}
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

void neighbor_joining::calc_scores() {
	double r_score = 0;
	for (int i = 0; i < dist_matrix.size(); i++) {
		for (int j = 0; j < dist_matrix[0].size(); j++) {
			r_score += dist_matrix[i][j];
		}
		scores.push_back(r_score);
		r_score = 0;
	}
}

void neighbor_joining::calc_q_matrix() {
	vector<double> row;
	int n = nodes.size();
	double q_val = 0.0;
	int min_val = dist_matrix[0][1] - ((scores[0] + scores[1]) / (n - 2));				//(0,1)
	min_pos.first = 0;
	min_pos.second = 1;
	for (int i = 0; i < dist_matrix.size(); i++) {
		q_matrix.push_back(row);
		for (int j = 0; j < dist_matrix[0].size(); j++) {
			if (j > i) {
				q_val = dist_matrix[i][j] - ((scores[i] + scores[j]) / (n - 2));
				if (q_val < min_val) {
					min_val = q_val;
					min_pos.first = i;
					min_pos.second = j;
				}
			}
			else if (j < i) {
				q_val = q_matrix[j][i];
				q_val = round(q_val * 100.0) / 100.0;
			}
			else {
				q_val = 0.0;
			}
			q_matrix[i].push_back(q_val);
		}
	}
}

void neighbor_joining::calc_dist_matrix() {
	//nodes begin
	vector<string> t_nodes = nodes;
	nodes.clear();
	string n_node = "U(" + t_nodes[min_pos.first] + ", " + t_nodes[min_pos.second] + ")";
	nodes.push_back(n_node);
	for (int i = 0; i < t_nodes.size(); i++) {
		if ((i != min_pos.first) && (i != min_pos.second)) {
			nodes.push_back(t_nodes[i]);
			other_pos.push_back(i);
		}
	}
	//nodes end
	vector<vector<double>> t_matrix = dist_matrix;
	dist_matrix.clear();
	int pos = 0;  //'
	int ipos = 0;
	int jpos = 0;
	vector<double> row;
	int n = nodes.size();
	double d_val = 0.0;
	for (int i = 0; i < n; i++) {
		dist_matrix.push_back(row);
		for (int j = 0; j < n; j++) {
			if (j > i) {
				if (i == 0) {
					pos = other_pos[j - 1]; //'
					d_val = (t_matrix[min_pos.first][pos] + t_matrix[min_pos.second][pos] - t_matrix[min_pos.first][min_pos.second]) / 2;
					d_val = round(d_val * 100.0) / 100.0;
				}
				else {
					ipos = other_pos[i - 1]; //'
					jpos = other_pos[j - 1]; //'
					d_val = t_matrix[ipos][jpos];
					d_val = round(d_val * 100.0) / 100.0;
				}
			}
			else if (j < i) {
				d_val = dist_matrix[j][i];
			}
			else {
				d_val = 0.0;
			}
			dist_matrix[i].push_back(d_val);
		}
	}
}

void neighbor_joining::generate(string file_name) {
	//DELETE
	string file_name_d = file_name + ".txt";
	ofstream myfile(file_name_d);
	string line = "";
	if (myfile.is_open())
	{
		myfile << " ";
		myfile.close();
	}
	else cout << "Unable to open file";
	print_matrix(nodes, dist_matrix);
	txt_matrix(nodes, dist_matrix, file_name);
	while (nodes.size() > 2) {
		calc_scores();
		//print_scores(scores);
		txt_scores(scores, file_name);
		calc_q_matrix();
		//print_nodes_matrix(nodes, q_matrix);
		txt_nodes_matrix(nodes, q_matrix, file_name, false);
		calc_dist_matrix();
		//print_nodes_matrix(nodes, dist_matrix);
		txt_nodes_matrix(nodes, dist_matrix, file_name, true);
		q_matrix.clear();
		scores.clear();
	}
}
