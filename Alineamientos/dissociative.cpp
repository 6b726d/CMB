#include "dissociative.hpp"

dissociative::dissociative(vector<string> _nodes, vector<vector<double>> _dmatrix) {
	nodes = _nodes;
	dmatrix = _dmatrix;
}

void dissociative::calc_vdist() {
	double min_val = dmatrix[0][1];;
	for (int j = 1; j < dmatrix[0].size(); j++) {
		if (dmatrix[0][j] < min_val) {
			min_val = dmatrix[0][j];
		}
	}
	vdist.push_back(min_val);
	vrev.push_back(false);
	ndist.push_back(0.0);
	vdiff.push_back(0.0);
	for (int i = 1; i < dmatrix.size(); i++) {
		min_val = dmatrix[i][0];
		for (int j = 0; j < dmatrix[0].size(); j++) {
			if (i != j) {
				if (dmatrix[i][j] < min_val) {
					min_val = dmatrix[i][j];
				}
			}
		}
		vdist.push_back(min_val);
		vrev.push_back(false);
		ndist.push_back(0.0);
		vdiff.push_back(0.0);
	}
}

void dissociative::calc_max_pos() {
	double max_val = 0.0; //'
	for (int i = 0; i < vrev.size(); i++) {
		if (vrev[i] == false) {
			if (vdist[i] > max_val) {
				max_val = vdist[i];
				max_pos = i;
			}
		}
	}
	vrev[max_pos] = true;
	count++;
	order += nodes[max_pos];
}

void dissociative::calc_ndist() {
	for (int i = 0; i < vrev.size(); i++) {
		if (vrev[i] == false) {
			ndist[i] = dmatrix[max_pos][i];
		}
	}
}

void dissociative::calc_vdiff() {
	double diff_val = 0.0;
	for (int i = 0; i < vrev.size(); i++) {
		if (vrev[i] == false) {
			diff_val = vdist[i] - ndist[i];
			vdiff[i] = diff_val;
		}
	}
}

void dissociative::g_join() {
	for (int i = 0; i < vrev.size(); i++) {
		if (vrev[i] == false) {
			if (vdiff[i] > 0) {
				vrev[i] = true;
				count++;
				order += nodes[i];
			}
		}
	}
	order += "-";
}

void dissociative::print() {
	cout << "Revisado | Distancia | Distancia Nueva | Diferencia" << endl;
	for (int i = 0; i < vrev.size(); i++) {
		cout << vrev[i] << "\t" << vdist[i] << "\t" << ndist[i] << "\t" << vdiff[i] << endl;
	}
	cout << endl;
}

void dissociative::to_txt(string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name, ofstream::app);
	string line = "";
	if (myfile.is_open())
	{
		myfile << "Distancia | Distancia Nueva | Diferencia\n";
		for (int i = 0; i < vrev.size(); i++) {
			if (vrev[i] == false) {
				myfile << d2s_precision(vdist[i], 2) << "\t" << d2s_precision(ndist[i], 2) << "\t" << d2s_precision(vdiff[i], 2) << "\n";
			}
		}
		myfile << "\n" << order << "\n\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

string dissociative::generate(string file_name) {
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
	calc_vdist();
	while (count < vrev.size()) {
		calc_max_pos();
		calc_ndist();
		calc_vdiff();
		g_join();
		to_txt(file_name);
	}
	order.pop_back();
	return order;
}