#include "agglomerative.hpp"

agglomerative::agglomerative(vector<string> _nodes, vector<vector<double>> _dmatrix) {
	nodes = _nodes;
	dmatrix = _dmatrix;
	cmatrix = _dmatrix;
	//cpos
	cpos.resize(cmatrix.size());
	for (int i = 0; i < cmatrix.size(); i++) {
		cpos[i].push_back(i);
	}
}


void agglomerative::print_nodes_matrix(vector<string> v, vector<vector<double>> m) {
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

void agglomerative::txt_nodes_matrix(vector<string> v, vector<vector<double>> m, string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name, ofstream::app);
	string line = "";
	if (myfile.is_open())
	{
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

void agglomerative::calc_min_pos() {
	double min_val = dmatrix[0][1];				//(0,1)
	min_pos.first = 0;
	min_pos.second = 1;
	for (int i = 0; i < dmatrix.size(); i++) {
		for (int j = 0; j < dmatrix[0].size(); j++) {
			if (j > i) {
				if (dmatrix[i][j] < min_val) {
					min_val = dmatrix[i][j];
					min_pos.first = i;
					min_pos.second = j;
				}
			}
		}
	}
}

void agglomerative::calc_dmatrix(int type) {
	//nodes begin
	vector<string> t_nodes = nodes;
	nodes.clear();
	string n_node = "U(" + t_nodes[min_pos.first] + ", " + t_nodes[min_pos.second] + ")";
	nodes.push_back(n_node);
	//cmatrix begin
	vector<vector<int>> t_cpos = cpos;
	cpos.clear();
	int ipos = 0;
	int jpos = 0;
	double c_val = 0;
	vector<int> n_pos = t_cpos[min_pos.first];
	for (int i = 0; i < t_cpos[min_pos.first].size(); i++) {
		ipos = t_cpos[min_pos.first][i];
		for (int j = 0; j < t_cpos[min_pos.second].size(); j++) {
			n_pos.push_back(t_cpos[min_pos.second][j]);
			jpos = t_cpos[min_pos.second][j];
			c_val = dmatrix[min_pos.first][min_pos.second];
			cmatrix[ipos][jpos] = c_val;
			cmatrix[jpos][ipos] = c_val;
		}
	}
	cpos.push_back(n_pos);
	//cmatrix end
	for (int i = 0; i < t_nodes.size(); i++) {
		if ((i != min_pos.first) && (i != min_pos.second)) {
			nodes.push_back(t_nodes[i]);
			cpos.push_back(t_cpos[i]);	//cmatrix
			other_pos.push_back(i);
		}
	}
	//nodes end
	vector<vector<double>> t_matrix = dmatrix;
	dmatrix.clear();
	int pos = 0;  //'
	ipos = 0;
	jpos = 0;
	vector<double> row;
	int n = nodes.size();
	double d_val = 0.0;
	for (int i = 0; i < n; i++) {
		dmatrix.push_back(row);
		for (int j = 0; j < n; j++) {
			if (j > i) {
				if (i == 0) {
					pos = other_pos[j - 1]; //'
					if (type == 1) { //min
						d_val = min(t_matrix[min_pos.first][pos], t_matrix[min_pos.second][pos]);
					}
					else if (type == 2) { //max
						d_val = max(t_matrix[min_pos.first][pos], t_matrix[min_pos.second][pos]);
					}
					else { //avg
						d_val = (t_matrix[min_pos.first][pos] + t_matrix[min_pos.second][pos]) / 2;
					}
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
				d_val = dmatrix[j][i];
			}
			else {
				d_val = 0.0;
			}
			dmatrix[i].push_back(d_val);
		}
	}
}

void agglomerative::gen_cmatrix() {
	calc_min_pos();
	int ipos = 0;
	int jpos = 0;
	double c_val = 0;
	for (int i = 0; i < cpos[min_pos.first].size(); i++) {
		ipos = cpos[min_pos.first][i];
		for (int j = 0; j < cpos[min_pos.second].size(); j++) {
			jpos = cpos[min_pos.second][j];
			c_val = dmatrix[min_pos.first][min_pos.second];
			cmatrix[ipos][jpos] = c_val;
			cmatrix[jpos][ipos] = c_val;
		}
	}
}

pair<double, double> agglomerative::avg(vector<vector<double>> dmatrix0) {
	double x_sum = 0.0;
	double y_sum = 0.0;
	int n = 0;
	for (int i = 0; i < dmatrix0.size(); i++) {
		for (int j = 0; j < dmatrix0[0].size(); j++) {
			x_sum += dmatrix0[i][j];
			y_sum += cmatrix[i][j];
			n++;
		}
	}
	n -= dmatrix0.size();	//not sure
	double x_avg = x_sum / n;
	double y_avg = y_sum / n;
	return make_pair(x_avg, y_avg);
}

void agglomerative::gen_xs_ys(vector<vector<double>> dmatrix0) {
	pair<double, double> xy_avg = avg(dmatrix0);
	double x_val = 0.0;
	double y_val = 0.0;
	for (int i = 0; i < dmatrix0.size(); i++) {
		for (int j = 0; j < dmatrix0[0].size(); j++) {
			x_val = dmatrix0[i][j] - xy_avg.first;
			y_val = cmatrix[i][j] - xy_avg.second;
			xs.push_back(x_val);
			ys.push_back(y_val);
		}
	}
}

double agglomerative::gen_ccc(vector<vector<double>> dmatrix0) {
	gen_xs_ys(dmatrix0);
	double sum_xy = 0.0;	//x*y
	double sum_x2 = 0.0;	//x**2
	double sum_y2 = 0.0;	//y**2
	for (int i = 0; i < xs.size(); i++) {
		sum_xy += (xs[i]*ys[i]);
		sum_x2 += (xs[i]*xs[i]);
		sum_y2 += (ys[i]*ys[i]);
	}
	double numerator = sum_xy;
	double denominator = sqrt(sum_x2*sum_y2);
	double ccc = numerator / denominator;
	return ccc;
}

void agglomerative::generate(string file_name, int type) {
	//DELETE BEGIN
	string file_name_d = file_name + ".txt";
	ofstream myfile(file_name_d);
	string line = "";
	if (myfile.is_open())
	{
		myfile << "";
		myfile.close();
	}
	else cout << "Unable to open file";
	//DELETE END
	vector<string> nodes0 = nodes;
	vector<vector<double>> dmatrix0 = dmatrix;
	txt_nodes_matrix(nodes, dmatrix, file_name);
	while (nodes.size() > 2) {
		calc_min_pos();
		calc_dmatrix(type);
		txt_nodes_matrix(nodes, dmatrix, file_name);
		other_pos.clear();
	}
	gen_cmatrix();
	print_nodes_matrix(nodes0, cmatrix);
	double ccc = gen_ccc(dmatrix0);
	cout << "ccc: " << ccc << endl;
}
