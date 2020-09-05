#pragma once

#include <array>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void matrixToTxt(vector<vector<array<int, 4>>> m, string file_name);

void iMatrixToTxt(vector<vector<int>> m, vector<int> v, string file_name);

void cadsToTxtNW(vector<pair<string, string>> cads, string file_name);

void cadsToTxtSW(vector<string> cads, string file_name);

void cadsToTxt(vector<string> cads, string file_name);

void printMatrix(vector<vector<array<int, 4>>> m);

void printCadsNW(vector<pair<string, string>> cads);

void printCadsSW(vector<string> cads);

vector<string> add_gab(string cad1, string cad2);

vector<string> max_2string(string cad1, string cad2);

string d2s_precision(double num, int precision);
