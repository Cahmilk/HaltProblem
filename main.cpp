#include <string>
#include <iostream>
#include <vector>

using namespace std;

vector<string> single_parameter_functions;
vector<string> double_parameter_functions;
vector<string> parameterless_functions;

//Initiate the possible program commands
void fill_parameters() {

	single_parameter_functions.push_back("CALL");
	single_parameter_functions.push_back("RET");

	double_parameter_functions.push_back("MOV");
	double_parameter_functions.push_back("ADD");
	double_parameter_functions.push_back("SUB");
	double_parameter_functions.push_back("MUL");
	double_parameter_functions.push_back("DIV");
	double_parameter_functions.push_back("MOD");
	double_parameter_functions.push_back("IFEQ");
	double_parameter_functions.push_back("IFNEQ");
	double_parameter_functions.push_back("IFG");
	double_parameter_functions.push_back("IFL");
	double_parameter_functions.push_back("IFGE");
	double_parameter_functions.push_back("IFLE");

	parameterless_functions.push_back("ENDIF");

}


//Function that splits a string, 
//return a pair with the first and second splitted part
pair<string, string> splitString(string line, string delimiter) {

	string left, right;

	size_t pos = 0;
	pos = line.find(delimiter);
	left = line.substr(0, pos);
	right = line.erase(0, pos + delimiter.length());

	return make_pair(left, right);

}

//Get first line of the entries.
//These are related to L and N, the numbers of lines of the program and the value of the input
pair<int, int> getFirstLine() {

	int l, n;

	cin >> l;
	cin >> n;

	return pair<int, int>(l, n);

}

//Get each line and identify what is command and what is a variable
pair<string, string> getLine() {

	string line;
	getline(cin, line);
	pair<string, string> lines = splitString(line, " ");

	return lines;

}

void getIteration() {

	pair<string, string> line = getLine();
	int l, n;
	l = stoi(line.first);
	n = stoi(line.second);
	vector<pair<string, string>> program_lines;

	while (l != 0 && n != 0){

		for (int i = 0; i < l; i++)
			program_lines.push_back(getLine());



	}

	cout << "Oi";
}


// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
int main() {

	fill_parameters();
	getIteration();

	return 0;
}
