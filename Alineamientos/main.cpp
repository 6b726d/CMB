#include "cluster.hpp"
#include "neighbor_joining.hpp"

int main() {
	//Cluster
	/*
	int size = 0;
	string cad = "";
	cout << "Ingrese cantidad de cadenas: ";
	cin >> size;
	vector<string> cads(size);
	vector<string> nodes(size);
	cout << "Ingrese cadenas: " << endl;
	for (int i = 0; i < size; i++) {
		cin >> cads[i];
	}
	cout << "Ingrese nodos: " << endl;
	for (int i = 0; i < size; i++) {
		cin >> nodes[i];
	}
	double constant = 100.0;
	bool cluster_type = 0;
	int type = 0;
	cout << "Ingrese el tipo de cluster: " << endl;
	cin >> cluster_type;
	cout << "Ingrese tipo (1.min 2.max 3.prom): " << endl;
	cin >> type;
	cluster c(nodes, cads);
	c.generate("cluster",constant,true,type);
	*/
	int n = 0;
	cout << "Ingrese cantidad de nodos: ";
	cin >> n;
	vector<string> nodes(n);
	vector<vector<double>> dmatrix(n);
	double d_val = 0.0;
	cout << "Ingrese los nodos: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> nodes[i];
	}
	cout << "Ingrese la matriz: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> d_val;
			dmatrix[i].push_back(d_val);
		}
	}
	int op = 0;
	int type = 0;
	cout << "1.Agglomerative 2.Dissociative 3.NJ: " << endl;
	cin >> op;

	if (op == 1) {
		cout << "Ingrese tipo (1.min 2.max 3.prom):" << endl;
		cin >> type;
		agglomerative a(nodes, dmatrix);
		a.generate("cluster_a", type);
	}
	else if (op == 2) {
		dissociative d(nodes, dmatrix);
		string c = d.generate("cluster_d");
		cout << "Cluster: " << c << endl;
	}
	else if (op == 3) {
		neighbor_joining nj(nodes, dmatrix);
		nj.generate("nj");
	}
	else {
		cout << "Ingrese una opcion correcta." << endl;
	}
}
