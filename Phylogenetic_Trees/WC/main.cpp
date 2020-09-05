#include "watson_crick.hpp"

int main() {
	string arn = "";
	cout << "Ingrese ARN:" << endl;
	cin >> arn;
	watson_crick wc(arn);
	wc.generate();
	wc.print_matrix();
	wc.trace_back();
}