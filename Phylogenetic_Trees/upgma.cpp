#include "upgma.hpp"

upgma::upgma(vector<string> _nodes, vector<vector<double>> _dmatrix) {
	nodes = _nodes;
	dmatrix = _dmatrix;
}

pair<int,int> upgma::calc_min_pos() {
	pair<int, int> min_pos(0,1);
	double min_val = dmatrix[0][1];
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
	int ipos = min_pos.first;
	int jpos = min_pos.second;
	array<string, 2> u_nodes = {nodes[ipos], nodes[jpos]};
	tree_values.push_back(make_pair(u_nodes,dmatrix[ipos][jpos]));
	return min_pos;
}

void upgma::update() {
	pair<int, int> min_pos = calc_min_pos();
	vector<int> other_pos;
	//nodes begin
	vector<string> t_nodes = nodes;
	nodes.clear();
	string n_node = "(" + t_nodes[min_pos.first] + "," + t_nodes[min_pos.second] + ")";
	nodes.push_back(n_node);
	for (int i = 0; i < t_nodes.size(); i++) {
		if ((i != min_pos.first) && (i != min_pos.second)) {
			nodes.push_back(t_nodes[i]);
			other_pos.push_back(i);
		}
	}
	//nodes end
	vector<vector<double>> t_matrix = dmatrix;
	dmatrix.clear();
	int pos = 0;  //'
	int ipos = 0;
	int jpos = 0;
	vector<double> row;
	int n = nodes.size();
	double d_val = 0.0;
	for (int i = 0; i < n; i++) {
		dmatrix.push_back(row);
		for (int j = 0; j < n; j++) {
			if (j > i) {
				if (i == 0) {
					pos = other_pos[j - 1]; //'
					d_val = (t_matrix[min_pos.first][pos] + t_matrix[min_pos.second][pos]) / 2;
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

void upgma::dmatrixToTxt(string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name, ofstream::app);
	string line = "";
	if (myfile.is_open())
	{
		for (int i = 0; i < nodes.size(); i++) {
			myfile << nodes[i] << "\t";
		}
		myfile << endl;
		for (int i = 0; i < dmatrix.size(); i++) {
			for (int j = 0; j < dmatrix[0].size(); j++) {
				line = d2s_precision(dmatrix[i][j], 2);
				myfile << line << "\t";
			}
			myfile << "\n";
		}
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

void upgma::tree_valuesToTxt(string file_name) {
	file_name += ".txt";
	ofstream myfile(file_name);
	string line = "";
	if (myfile.is_open())
	{
		for (int i = 0; i < tree_values.size(); i++) {
			line = tree_values[i].first[0] + "\t" + tree_values[i].first[1] + "\t" + d2s_precision(tree_values[i].second, 2);
			myfile << line << "\n";
		}
		myfile << "\n";
		myfile.close();
	}
	else cout << "Unable to open file";
}

void upgma::generate() {
	//DELETE BEGIN
	ofstream myfile("dmatrix.txt");
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
	dmatrixToTxt("dmatrix");
	while (nodes.size() > 2) {
		update();
		dmatrixToTxt("dmatrix");
	}
	pair<int, int> min_pos = calc_min_pos();
	tree_valuesToTxt("tree_values");
}

bool upgma::findNode(string node, pair<int,int> &pos, int &p) {
	bool f = false;
	int i = 0;
	while ((i < tree_nodes.size()) and (f == false)) {
		if (node == tree_nodes[i].first) {
			f = true;
			pos.first = tree_nodes[i].second.first;
			pos.second = tree_nodes[i].second.second;
			p = i;
		}
		i++;
	}
	return f;
}

void upgma::drawText(string text, double x, double y) {
	glRasterPos2d(x, y);
	//glColor3f(1.0f, 1.0f, 1.0f);
	const unsigned char* c_text = (const unsigned char*)text.c_str();
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, c_text);
}

void upgma::display() {
	//Primer Nodo
	double xpos1 = 1.0;
	double ypos1 = 1.0;
	//Segundo Nodo
	double xpos2 = 1.0;
	double ypos2 = 10.0;
	//Nodo Resultante
	double xpos3 = 0.0;
	double ypos3 = 0.0;
	//Valor de Nodo1
	double xpos1l = 0.0;
	double ypos1l = 0.0;
	//Valor de Nodo2
	double xpos2l = 0.0;
	double ypos2l = 0.0;
	//Other
	double xpos = 1.0;
	double ypos = 1.0;
	double val = 0.0;
	string s_val1 = "";
	string s_val2 = "";
	string node1 = "";
	string node2 = "";
	string node3 = "";
	bool f1 = false;
	bool f2 = false;
	pair<int, int> pos;
	int p = 0;
	double val1 = 0.0;
	double val2 = 0.0;

	for (int i = 0; i < tree_values.size(); i++) {
		glColor3f(1.0f, 1.0f, 1.0f);
		//node1
		node1 = tree_values[i].first[0];
		if (findNode(node1, pos, p) == true) {
			f1 = true;
			xpos1 = pos.first;
			ypos1 = pos.second;
			val1 = tree_nodes_values[p];
		}
		else {
			f1 = false;
			xpos1 = xpos;
			ypos = ypos + 10.0;
			ypos1 = ypos;
			tree_nodes.push_back(make_pair(node1, make_pair(xpos1, ypos1)));
			tree_nodes_values.push_back(0.0);
			drawText(node1, xpos1, ypos1);
		}
		//node2
		node2 = tree_values[i].first[1];
		if (findNode(node2, pos, p) == true) {
			f2 = true;
			xpos2 = pos.first;
			ypos2 = pos.second;
			val2 = tree_nodes_values[p];
		}
		else {
			f2 = false;
			xpos2 = xpos;
			ypos = ypos + 10.0;
			ypos2 = ypos;
			tree_nodes.push_back(make_pair(node2, make_pair(xpos2, ypos2)));
			tree_nodes_values.push_back(0.0);
			drawText(node2, xpos2, ypos2);
		}
		//union begin
		xpos3 = (max(xpos1, xpos2)) + 20.0;
		ypos3 = (ypos1 + ypos2) / 2;
		node3 = "(" + node1 + "," + node2 + ")";
		tree_nodes.push_back(make_pair(node3, make_pair(xpos3, ypos3)));
		val = tree_values[i].second / 2;
		val = round(val * 100.0) / 100.0;
		tree_nodes_values.push_back(val);
		drawText(node3, xpos3, ypos3);
		//union end
		//lines begin
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex2d(xpos1 + 1.0, ypos1 + 1.5);
		glVertex2d(xpos3 - 1.0, ypos3 - 0.5);
		glEnd();
		glBegin(GL_LINES);
		glVertex2d(xpos2 + 1.0, ypos2 + 1.5);
		glVertex2d(xpos3 - 1.0, ypos3 - 0.5);
		glEnd();
		//lines end
		//values begin
		glColor3f(1.0f, 1.0f, 1.0f);
		//val node 1
		if (f1 == true) {
			val1 = val - val1;
		}
		else {
			val1 = val;
		}
		f1 = false;
		val1 = round(val1 * 100.0) / 100.0;
		s_val1 = d2s_precision(val1, 2);
		xpos1l = (xpos3 + xpos1) / 2;
		ypos1l = (ypos3 + ypos1) / 2;
		drawText(s_val1, xpos1l, ypos1l);
		//val node2
		if (f2 == true) {
			val2 = val - val2;
		}
		else {
			val2 = val;
		}
		f2 = false;
		val2 = round(val2 * 100.0) / 100.0;
		s_val2 = d2s_precision(val2, 2);
		xpos2l = (xpos3 + xpos2) / 2;
		ypos2l = (ypos3 + ypos2) / 2;
		drawText(s_val2, xpos2l, ypos2l);
		//values end
	}
}
