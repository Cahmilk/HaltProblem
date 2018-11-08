/ HaltingProblem.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "pch.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<string> aritmetical_functions;
vector<string> conditional_functions;

//Initiate the possible program commands
void fill_parameters() {

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

}

//Set a value to each variable.
map<string, int> fill_local_variables(int n) {

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
	return (a / b);
}

//Executing the command of mod
int comand_mod(int a, int b) {

	if (b == 0)
		return 0;
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

//Get each line and identify what is command and what is a variable
pair<string, string> getLine() {

	string line;
	getline(cin, line);
	pair<string, string> lines = splitString(line, " ");

	return lines;

}

//Check if a given function is aritmetical or not
bool checkIfAritmetical(string s) {

	bool aux = (find(aritmetical_functions.begin(), aritmetical_functions.end(), s) != aritmetical_functions.end());
	return aux;

}

//Check if a given function is conditional or not
bool checkIfConditional(string s) {

	bool aux = (find(conditional_functions.begin(), conditional_functions.end(), s) != conditional_functions.end());
	return aux;

}


//Checks if a given string is an variable or a number.
//Return the correspondent number.
int getNumber(map<string, int> local_variables, string s) {

	map<string, int>::iterator it;
	int val;

	it = local_variables.find(s);
	if (it != local_variables.end())
		val = it->second;
	else
		val = stoi(s);

	return val;
}

//If a given function is aritmetical, run this.
int RunAritmeticalFunctions(string function_name, map<string, int> local_variables, int var1, int var2) {

	int result;

	if (function_name.compare("MOV") == 0)
		result = comand_mov(var1, var2);

	else if (function_name.compare("ADD") == 0)
		result = comand_add(var1, var2);

	else if (function_name.compare("SUB") == 0)
		result = comand_sub(var1, var2);

	else if (function_name.compare("MUL") == 0)
		result = comand_mul(var1, var2);

	else if (function_name.compare("DIV") == 0)
		result = comand_div(var1, var2);

	else if (function_name.compare("MOD") == 0)
		result = comand_mod(var1, var2);

	return result;

}

//If a given function is a conditional, run this.
bool runConditionals(string function_name, map<string, int> local_variables, int var1, int var2) {

	bool aux;

	if (function_name.compare("IFEQ") == 0)
		aux = comand_ifeq(var1, var2);

	else if (function_name.compare("IFNEQ") == 0)
		aux = comand_ifneq(var1, var2);

	else if (function_name.compare("IFG") == 0)
		aux = comand_ifg(var1, var2);

	else if (function_name.compare("IFL") == 0)
		aux = comand_ifl(var1, var2);

	else if (function_name.compare("IFGE") == 0)
		aux = comand_ifge(var1, var2);

	else if (function_name.compare("IFLE") == 0)
		aux = comand_ifle(var1, var2);

	return aux;

}

//Controls the program execution
int runProgram(vector<pair<string, string>> program_lines, int n) {

	map<string, int> local_variables;
	local_variables = fill_local_variables(n);
	map<string, int>::iterator it;

	//check if the function already entered in an if function.
	//If it is not suppose to execute the subsequent lines of an if, it is false.
	bool if_check = true;

	for (int i = 0; i < program_lines.size(); i++) {
	
		string command_name = program_lines.at(i).first;
		string command_parameter = program_lines.at(i).second;
		string variable;
		int var1, var2;

		if (command_parameter.find(',') != string::npos){

			pair<string, string> function_parameters = splitString(program_lines.at(i).second, ",");
			variable = function_parameters.first;
			var1 = getNumber(local_variables, function_parameters.first);
			var2 = getNumber(local_variables, function_parameters.second);
		
		}
		else if (command_name.compare("ENDIF")) {
			variable = command_parameter;
			var1 = getNumber(local_variables, command_parameter);
		
		}

		if (checkIfAritmetical(command_name) && if_check) {
			it = local_variables.find(variable);
			it->second = RunAritmeticalFunctions(program_lines.at(i).first, local_variables, var1, var2);

		}

		//If it enters in the if, following subsequent the program lines, if it does not, it looks for the next endif.
		//cout << program_lines.at(i).first << " ";
		else if (checkIfConditional(program_lines.at(i).first) && if_check)
			if_check = runConditionals(program_lines.at(i).first, local_variables, var1, var2);

		else if (!command_name.compare("ENDIF"))
			if_check = true;

		else if (!command_name.compare("RET") && if_check)
			return var1;

		else if (!command_name.compare("CALL") && if_check) {

			it = local_variables.find("R9");
			it->second = runProgram(program_lines, var1);

		}

	}

}

//Read Instances
void getIteration() {

	int l = 1, n = 1;

	pair<string, string> line = getLine();
	l = stoi(line.first);
	n = stoi(line.second);
	vector<pair<string, string>> program_lines;

	while (l != 0 || n != 0) {

		for (int i = 0; i < l; i++)
			program_lines.push_back(getLine());

		int i = runProgram(program_lines, n);
		cout << i << endl;

		pair<string, string> line = getLine();
		l = stoi(line.first);
		n = stoi(line.second);
		program_lines.clear();

	}
}


// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
int main() {

	fill_parameters();
	getIteration();

	return 0;
}
