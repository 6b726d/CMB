#include "additive_distance.hpp"

additive_distance::additive_distance(vector<string> _nodes, vector<vector<int>> _dmatrix) {
	nodes = _nodes;
	dmatrix = _dmatrix;
}

int additive_distance::calc_min() {
	int min_val = dmatrix[0][1];
	for (int i = 0; i < dmatrix.size(); i++) {
		for (int j = i + 1; j < dmatrix[0].size(); j++) {
			if (dmatrix[i][j] < min_val) {
				min_val = dmatrix[i][j];
			}
		}
	}
	return min_val;
}

int additive_distance::calc_alpha() {
	int min_val = calc_min();
	int alpha = min_val / 2;
	if ((alpha % 2) == 0) {
		alpha--;
		if (alpha < 0) {
			alpha = 0;
		}
	}
	vec_alpha.push_back(alpha);
	return alpha;
}

void additive_distance::calc_dmatrix_alpha() {
	double alpha = calc_alpha();
	for (int i = 0; i < dmatrix.size(); i++) {
		for (int j = 0; j < dmatrix[0].size(); j++) {
			if (i != j) {
				dmatrix[i][j] = dmatrix[i][j] - (2 * alpha);
			}
		}
	}
}

int additive_distance::calc_transitive_pos() {
	int transitive_pos = -1;
	int n = dmatrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (j != k) {
					if (dmatrix[i][j] + dmatrix[j][k] == dmatrix[i][k]) {
						transitive_pos = j;
					}
				}
			}
		}
	}
	if (transitive_pos == -1) {
		end = true;
	}
	else {
		//vec_transitive.push_back(transitive_pos);
		vec_transitive.push_back(nodes[transitive_pos]);
	}
	return transitive_pos;
}

void additive_distance::calc_dmatrix_transitive() {
	int transitive_pos = calc_transitive_pos();
	if (end == false) {
		vector<string> vec_node;	//graphics
		vector<int> vec_val;		//graphics
		// nodes begin
		vector<string> t_nodes = nodes;
		nodes.clear();
		int n = t_nodes.size() - 1;
		int p = 0;
		for (int i = 0; i < n; i++) {
			if (p == transitive_pos) {
				p++;
			}
			nodes.push_back(t_nodes[p]);
			// graphics begin
			vec_node.push_back(t_nodes[p]);
			vec_val.push_back(dmatrix[transitive_pos][p]);
			// graphics end
			p++;
		}
		tree.push_back(make_pair(vec_node, vec_val));	//graphics
		t_nodes.clear();
		// nodes end
		vector<vector<int>> t_dmatrix = dmatrix;
		dmatrix.clear();
		vector<int> row;
		n = nodes.size();
		int r = 0;
		int c = 0;
		for (int i = 0; i < n; i++) {
			dmatrix.push_back(row);
			for (int j = 0; j < n; j++) {
				if (r == transitive_pos) {
					r++;
				}
				if (c == transitive_pos) {
					c++;
				}
				dmatrix[i].push_back(t_dmatrix[r][c]);
				c++;
			}
			c = 0;
			r++;
		}
		r = 0;
		t_dmatrix.clear();
	}
}

void additive_distance::dmatrixToTxt(string file_name) {
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

void additive_distance::printValues() {
	cout << "Alpha Values: ";
	for (int i = 0; i < vec_alpha.size(); i++) {
		cout << vec_alpha[i] << " ";
	}
	cout << endl;
	cout << "Transitive Nodes: ";
	for (int i = 0; i < vec_transitive.size(); i++) {
		cout << vec_transitive[i] << " ";
	}
	cout << endl;
}

void additive_distance::generate() {
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
	vector<vector<int>> dmatrix0 = dmatrix;
	dmatrixToTxt("dmatrix");
	while ((nodes.size() > 2) and (end == false)) {
		calc_dmatrix_alpha();
		dmatrixToTxt("dmatrix");
		calc_dmatrix_transitive();
		dmatrixToTxt("dmatrix");
	}
	printValues();
	if (end == true) {
		cout << "No Tree." << endl;
	}
}

bool additive_distance::findNode(string node, int p,  int &pos) {
	bool f = false;
	int i = 0;
	while ((i < tree[p].first.size()) and (f == false)) {
		if (node == tree[p].first[i]) {
			f = true;
			pos = i;
		}
		i++;
	}
	return f;
}

// Busco el valor mas cercano a la posicion del nodo interno insertado
// Una vez encontrada dicha posicion, elimino el valor cercano a dicha posicion
// Creo los dos nuevos valores
void additive_distance::findPosVal(double pos, double unit) {
	double pos_left = 0.0;
	double pos_right = 100.0;
	for (int i = 0; i < pos_line.size(); i++) {
		if (pos_line[i] < pos) {	//left
			if (pos_line[i] > pos_left) {
				pos_left = pos_line[i];
			}
		}
		if (pos_line[i] > pos) {	//right
			if (pos_line[i] < pos_right) {
				pos_right = pos_line[i];
			}
		}
	}
	double pos_med = (pos_left + pos_right) / 2;
	int p = 0;
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].second == pos_med) {
			p = i;
		}
	}
	lines.erase(lines.begin() + p); //'
	double pos_lm = (pos + pos_left) / 2;
	double pos_rm = (pos + pos_right) / 2;
	double l_val = (pos - pos_left) / unit;
	double r_val = (pos_right - pos) / unit;
	int lv = nearbyint(l_val);	//'
	int rv = nearbyint(r_val);	//'
	lines.push_back(make_pair(lv, pos_lm));
	lines.push_back(make_pair(rv, pos_rm));
}

// Busco los valores (izq y der) más pegados a los nodos iniciales
pair<int, int> additive_distance::findPosAlpha() {
	double left_pos = lines[0].second;
	double right_pos = lines[0].second;
	int pos_l = 0;
	int pos_r = 0;
	for (int i = 1; i < lines.size(); i++) {
		if (lines[i].second < left_pos) {
			left_pos = lines[i].second;
			pos_l = i;
		}
		if (lines[i].second > right_pos) {
			right_pos = lines[i].second;
			pos_r = i;
		}
	}
	return make_pair(pos_l, pos_r);
}

void additive_distance::display() {
	if (end == false) {
		// Paso 1
		drawText(nodes[0], 10, 50);
		drawText(nodes[1], 90, 50);
		pos_line.push_back(10); //line
		pos_line.push_back(90); //line
		lines.push_back(make_pair(dmatrix[0][1], 50));	//line
		//glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex2d(15, 50);
		glVertex2d(85, 50);
		glEnd();
		// Paso 2
		double unit = 0.0;
		double dist0 = 0.0;
		double dist1 = 0.0;
		bool b = false;
		int pos = 0;
		double node_pos = 0.0;
		bool v_pos = false;
		double n_pos = 0.0;
		pair<int, int> lr_pos;
		for (int i = tree.size() - 1; i >= 0; i--) {
			b = findNode(nodes[0], i, pos);	//'
			dist0 = tree[i].second[pos];	//'
			b = findNode(nodes[1], i, pos);	//'
			dist1 = tree[i].second[pos];	//'
			unit = 80 / (dist0 + dist1);
			// En base al nodo0
			node_pos = dist0 * unit;
			n_pos = 10 + node_pos;
			if (v_pos == false) {
				branches.push_back(make_pair(0, make_pair(n_pos + 1, 35)));
				drawText(vec_transitive[i], n_pos, 20);
				v_pos = true;
				glBegin(GL_LINES);
				glVertex2d(10 + node_pos, 25);
				glVertex2d(10 + node_pos, 50);
				glEnd();
			}
			else {
				branches.push_back(make_pair(0, make_pair(n_pos + 1, 65)));
				drawText(vec_transitive[i], n_pos, 80);
				v_pos = false;
				glBegin(GL_LINES);
				glVertex2d(10 + node_pos, 75);
				glVertex2d(10 + node_pos, 50);
				glEnd();
			}
			for (int pb = 0; pb < branches.size(); pb++) {
				branches[pb].first += vec_alpha[i];
			}
			//line begin
			findPosVal(n_pos, unit);	//line
			pos_line.push_back(n_pos);	//line
			lr_pos = findPosAlpha();	//line
			lines[lr_pos.first].first += vec_alpha[i];
			lines[lr_pos.second].first += vec_alpha[i];
			//line end
		}
		string s_val = "";
		double xpos = 0;
		double ypos = 0;
		for (int i = 0; i < branches.size(); i++) {
			s_val = to_string(branches[i].first);
			xpos = branches[i].second.first;
			ypos = branches[i].second.second;
			drawText(s_val, xpos, ypos);
		}
		ypos = 45;
		for (int i = 0; i < lines.size(); i++) {
			s_val = to_string(lines[i].first);
			xpos = lines[i].second;
			drawText(s_val, xpos, ypos);
		}
	}
}
