#ifndef OVERLOADS_H
#define OVERLOADS_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "excepter.h"
using namespace std;
using namespace bf;

// output object of vector
template<typename t>
ostream& operator<<(ostream& out, const vector<t>& vec) {
	out << "[ ";
	for (int i = 0; i < vec.size();i++) {
		out << vec[i];
		if (i != vec.size() - 1) { // if not finally element
			out << ", ";
		}
	}
	out << " ]";
	return out;
}

// output object of char_excepter
ostream& operator<<(ostream& out, const char_excepter& exc) {
	ostringstream output;
	output << "CharacterError:\n";
		output << "\tAt line " << exc.line << ", colcumn " << exc.column << ":\n";
		output << "\tThe character: \'" << exc.error_char << "\' is illegal in BrainF**k syntax.";

	out << output.str();

	return out;
}

// output object of arg_error
ostream& operator<<(ostream& out, const arg_error& e) {
	ostringstream output;
	output << "ArgumentError:\n";
	output << "\t" << e.error_arg;
	out << output.str() << endl;

	return out;
}

// output object of file_error
ostream& operator<<(ostream& out, const file_error& e) {
	ostringstream output;
	output << "FileError:\n";
	output << "\t" << e.error_file;

	out << output.str();

	return out;
}

// output object of compile_data_error
ostream& operator<<(ostream& out, const compile_data_error& e) {
	ostringstream output;
	output << "CompileDataError:\n";
	output << "\t" << e.error_compile_data;

	out << output.str();

	return out;
}

// output object to string object as a string
template<typename T>
string& operator<<(string& str, const T& element) {
	ostringstream oss;
	oss << element; // parse as a string

	str += oss.str();

	return str;
}

#endif // !OVERLOADS_H
