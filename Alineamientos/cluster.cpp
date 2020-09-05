#include "cluster.hpp"

cluster::cluster(vector<string> _nodes, vector<string> _cads) {
	nodes = _nodes;
	cads = _cads;
}

double cluster::calc_dist(int i, int j, double constant) {
	double dist = 0.0;
	needleman_wunsch nw(cads[i], cads[j], 4, 3);
	dist = nw.getDist(constant);
	dist = round(dist * 100.0) / 100.0;
	return dist;
}

void cluster::calc_dmatrix(double constant) {
	vector<vector<double>> dmatrix0(nodes.size());
	for (int i = 0; i < dmatrix0.size(); i++) {
		for (int j = 0; j < dmatrix0.size(); j++) {
			dmatrix0[i].push_back(calc_dist(i, j, constant));
		}
	}
	dmatrix =  dmatrix0;
}

void cluster::generate(string file_name, double constant, bool cluster_type, int a_type) {
	calc_dmatrix(constant);
	//cluster_type = 1 -> agglomerative
	//cluster_type = 0 -> dissociative
	if (cluster_type == true) {
		agglomerative a(nodes, dmatrix);
		a.generate(file_name, a_type);
	}
	else {
		dissociative d(nodes, dmatrix);
		d.generate(file_name);
	}
}
