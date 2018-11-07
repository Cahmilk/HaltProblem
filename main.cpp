#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<string> parameter_functions;
vector<string> aritmetical_functions;
vector<string> conditional_functions;
vector<string> parameterless_functions;

//Initiate the possible program commands
void fill_parameters() {

	parameter_functions.push_back("CALL");
	parameter_functions.push_back("RET");

	aritmetical_functions.push_back("MOV");
	aritmetical_functions.push_back("ADD");
	aritmetical_functions.push_back("SUB");
	aritmetical_functions.push_back("MUL");
	aritmetical_functions.push_back("DIV");
	aritmetical_functions.push_back("MOD");

	conditional_functions.push_back("IFEQ");
	conditional_functions.push_back("IFNEQ");
	conditional_functions.push_back("IFG");
	conditional_functions.push_back("IFL");
	conditional_functions.push_back("IFGE");
	conditional_functions.push_back("IFLE");

	parameterless_functions.push_back("ENDIF");

}

vector<string> global_variables;

//Initiate the possible program commands
void fill_variables() {

	global_variables.push_back("R0");
	global_variables.push_back("R1");
	global_variables.push_back("R2");
	global_variables.push_back("R3");
	global_variables.push_back("R4");
	global_variables.push_back("R5");
	global_variables.push_back("R6");
	global_variables.push_back("R7");
	global_variables.push_back("R8");
	global_variables.push_back("R9");

}

map<string, int> fill_variables(int n) {

	map<string, int> local_variables;
	local_variables.insert(make_pair("R0", n));
	local_variables.insert(make_pair("R1", 0));
	local_variables.insert(make_pair("R2", 0));
	local_variables.insert(make_pair("R3", 0));
	local_variables.insert(make_pair("R4", 0));
	local_variables.insert(make_pair("R5", 0));
	local_variables.insert(make_pair("R6", 0));
	local_variables.insert(make_pair("R7", 0));
	local_variables.insert(make_pair("R8", 0));
	local_variables.insert(make_pair("R9", 0));
	return local_variables;

}

//Execute the command to associate b to a.
int comand_mov(int a, int b) {

	return b;
}

//Executing the command of addition
int comand_add(int a, int b) {

	return a + b;
}

//Executing the command of subtraction
int comand_sub(int a, int b) {

	return a - b;
}

//Executing the command of multiplication
int comand_mul(int a, int b) {

	return a * b;
}

//Executing the command of division
int comand_div(int a, int b) {

	if (b == 0)
		return 0;
	return (a/b);
}

//Executing the command of mod
int comand_mod(int a, int b) {

	return a % b;
}

//Executing the command of ifeq
bool comand_ifeq(int a, int b) {

	if (a == b)
		return true;
	else
		return false;

}

//Executing the command of ifneq
bool comand_ifneq(int a, int b) {

	if (a != b)
		return true;
	else
		return false;

}

//Executing the command of ifg
bool comand_ifg(int a, int b) {

	if (a > b)
		return true;
	else
		return false;

}

//Executing the command of ifl
bool comand_ifl(int a, int b) {

	if (a < b)
		return true;
	else
		return false;

}

//Executing the command of ifge
bool comand_ifge(int a, int b) {

	if (a >= b)
		return true;
	else
		return false;

}

//Executing the command of ifle
bool comand_ifle(int a, int b) {

	if (a <= b)
		return true;
	else
		return false;

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

int RunTwoParametersFunction(string function_name, map<string, int> local_variables, string a, int var2) {

	map<string, int>::iterator it;

	it = local_variables.find(a);
	int var1 = it->second;
	   
	if (function_name.compare("MOV") == 0)
		it->second = comand_mov(var1, var2);

	else if(function_name.compare("ADD") == 0)
		it->second = comand_add(var1, var2);

	else if (function_name.compare("SUB") == 0)
		it->second = comand_sub(var1, var2);

	else if (function_name.compare("MUL") == 0)
		it->second = comand_mul(var1, var2);

	else if (function_name.compare("DIV") == 0)
		it->second = comand_div(var1, var2);

	else if (function_name.compare("MOD") == 0)
		it->second = comand_mod(var1, var2);

	return it->second;

}

//str1.compare(str2) != 0)
void runProgram(vector<pair<string, string>> program_lines, int n) {

	map<string, int> local_variables;
	local_variables = fill_variables(n);
	map<string, int>::iterator it;

	for (int i = 0; i < program_lines.size(); i++) {

		cout << program_lines.at(i).first << " ";

		if (find(aritmetical_functions.begin(), aritmetical_functions.end(), program_lines.at(i).first) != aritmetical_functions.end()) {
			
			cout << program_lines.at(i).first << " ";
			
			pair<string, string> function_variables = splitString(program_lines.at(i).second, ",");
			
			it = local_variables.find(function_variables.second);
			int var2;
			if (it != local_variables.end())
				var2 = it->second;
			else
				var2 = stoi(function_variables.second);

			it = local_variables.find(function_variables.first);
			
			cout << function_variables.first << " " << function_variables.second << " ";
			
			it->second = RunTwoParametersFunction(program_lines.at(i).first, local_variables, function_variables.first, var2);
			
			cout << it->first<<"="<<it->second<<endl;
		
		}
		else if (program_lines.at(i).first.compare("RET") == 0) {

			it = local_variables.find(program_lines.at(i).second);
			int aux = it->second;
			it = local_variables.find("R9");
			it->second = aux;
			cout << "RETORNA:" << aux;

		}
		else {
			cout << "nao tratado ainda" << endl;
		}

	}

}

void getIteration() {

	int l = 1, n = 1;

	while (l != 0 && n != 0) {

		pair<string, string> line = getLine();
		l = stoi(line.first);
		n = stoi(line.second);
		vector<pair<string, string>> program_lines;

		for (int i = 0; i < l; i++)
			program_lines.push_back(getLine());

		runProgram(program_lines, n);

	}
}


// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
int main() {

	fill_parameters();
	fill_variables();
	getIteration();

	return 0;
}
