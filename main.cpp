#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int counter = 0;

vector<string> aritmetical_functions;
vector<string> conditional_functions;
vector<vector<pair<string, string>>> saved_programs;
vector<map<int, int>> saved_pre_computed_solutions;
map<int, int> pre_computed;

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

//Executing the command of mod
int comand_mod(int a, int b) {

	if (b == 0)
		return 0;
	return a % b;
}

//Executing the command of addition
int comand_add(int a, int b) {

	if (a + b > 999)
		return comand_mod(a + b, 1000);
	return a + b;

}

//Executing the command of subtraction
int comand_sub(int a, int b) {

	if(a-b<0)
		return 1000 + (a - b);
	return a - b;
}

//Executing the command of multiplication
int comand_mul(int a, int b) {

	int aux = b;
	if (a == 0 || b == 0)
		return 0;
	else
		for (int i = 1; i < a; i++)
			b = comand_add(b, aux);
	return b;
}

//Executing the command of division
int comand_div(int a, int b) {

	if (b == 0)
		return 0;

	return (a / b);
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

	if (s.compare("MOV") != 0 && s.compare("ADD") != 0 && s.compare("SUB") != 0 && s.compare("MUL") != 0 && s.compare("DIV") != 0 && s.compare("MOD") != 0)
		return false;
	else
		return true;

}

//Check if a given function is conditional or not
bool checkIfConditional(string s) {

	if (s.compare("IFEQ") != 0 && s.compare("IFNEQ") != 0 && s.compare("IFG") != 0 && s.compare("IFL") != 0 && s.compare("IFGE") != 0 && s.compare("IFLE") != 0)
		return false;
	else
		return true;

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

	if (counter == 800) {

		return 1000;
	}

	else {
		
		counter++;
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

			if (command_parameter.find(',') != string::npos && if_check) {

				pair<string, string> function_parameters = splitString(program_lines.at(i).second, ",");
				variable = function_parameters.first;
				var1 = getNumber(local_variables, function_parameters.first);
				var2 = getNumber(local_variables, function_parameters.second);

			}
			else if (command_name.compare("ENDIF") && if_check) {
				variable = command_parameter;
				var1 = getNumber(local_variables, command_parameter);

			}

			if (checkIfAritmetical(command_name) && if_check) {
				it = local_variables.find(variable);
				it->second = RunAritmeticalFunctions(program_lines.at(i).first, local_variables, var1, var2);

			}

			//If it enters in the if, following subsequent the program lines, if it does not, it looks for the next endif.
			//cout << program_lines.at(i).first << " ";
			else if (checkIfConditional(command_name) && if_check)
				if_check = runConditionals(program_lines.at(i).first, local_variables, var1, var2);

			else if (!command_name.compare("ENDIF")) {

				if_check = true;
			}

			else if (!command_name.compare("RET") && if_check) {
				pre_computed.insert(make_pair(n, var1));
				return var1;
			}

			else if (!command_name.compare("CALL") && if_check) {

				map<int, int>::iterator it_pre_computed;
				it = local_variables.find("R9");
				it_pre_computed = pre_computed.find(var1);

				if (it_pre_computed != pre_computed.end())
					it->second = it_pre_computed->second;
				else
					it->second = runProgram(program_lines, var1);

				if (it->second == 1000)
					return 1000;

			}

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

		bool existent_program = false;
		int j;

		for (int i = 0; i < saved_programs.size(); i++) {
			if (program_lines == saved_programs.at(i)) {
				j = i;
				existent_program = true;
				pre_computed = saved_pre_computed_solutions.at(i);
				break;
			}
		}

		int i = runProgram(program_lines, n);
		if (i == 1000)
			cout << "*" << endl;
		else
			cout << i << endl;

		counter = 0;
		
		if (!existent_program) {
			
			saved_pre_computed_solutions.push_back(pre_computed);
			saved_programs.push_back(program_lines);

		}
		else if (existent_program) {
			saved_pre_computed_solutions.at(j) = pre_computed;
		}
		pair<string, string> line = getLine();
		l = stoi(line.first);
		n = stoi(line.second);
		program_lines.clear();
		pre_computed.clear();

	}
}


// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
int main() {

	getIteration();

	return 0;
}
