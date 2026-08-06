#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>
#include "overloads.h"
#include "excepter.h"
#include "uncert.h"
#include "debugger.h"

using namespace std;

using code_list = vector<string>;

namespace bf {
	vector<bf::char_excepter> errors;

	vector<file_error>        file_errors;

	string install_path;

	class compiler {
	public:
		code_list codes;
		string out_path;
		unsigned int cardinal;
		unsigned int len;
		bool ascii_enable;

		compiler(code_list codes, string out_path) {
			this->codes = codes;
			this->out_path = out_path;
			this->cardinal = 255;
			this->len = 1024;
			this->ascii_enable = false;
		}
		compiler() {
			this->codes = {};
			this->out_path = "output.cpp";
			this->cardinal = 255;
			this->len = 1024;
			this->ascii_enable = false;
		}

		void compile() {
			ofstream file("output-temp.cpp");
			uncert out;

			// error throw
			if (!file.is_open()) {
				throw file_error("The file: \"output-temp.cpp\" cannot write.");
			}


			// ------ start of program output ------ //
			
			
			// output the functions and classes for output program
			{
				ostringstream oss;
				oss <<
					"#include <iostream>\n"
					"using namespace std;\n"
					"template<typename Number_Type>\n"
					"Number_Type abs(Number_Type value) {\n"
					"	if (value >= 0) {\n"
					"		return value;\n"
					"	}\n"
					"	else {\n"
					"		return 0 - value;\n"
					"	}\n"
					"}\n"
					"\n"
					"namespace bf {\n"
					"	class bf_int {\n"
					"	public:\n"
					"		int value;\n"
					"		bf_int(int value) {\n"
					"			this->value = value;\n"
					"		}\n"
					"		bf_int() {\n"
					"			this->value = 0;\n"
					"		}\n"
					"		\n"
					"		void operator++() {\n"
					"			this->value = abs((this->value + 1) % " <<
					((ostringstream()) << cardinal).str()
					<< ");\n"
					"		}\n"
					"		void operator--() {\n"
					"			this->value = abs((this->value - 1) % " <<
					((ostringstream()) << cardinal).str()
					<< ");\n"
					"		}\n"
					"\n"
					"		void print() {\n"

					// process the character output or number output
					<< (
						ascii_enable ?
						"			cout << char(this->value);\n"
						:
						"			cout << this->value << ' ';\n"
						)

					// and then
					<< "		}\n"
					"		void unprint() {\n"

					// process the character output or number output, but negative
					<< (
						(!ascii_enable) ?
						"			cout << char(this->value);\n"
						:
						"			cout << this->value << ' ';\n"
						)

					// and then
					<< "		}\n"
					"	};\n"
					"}\n"
					"bf::bf_int arr[" << ((ostringstream()) << len).str() << "];\n"
					"int main() {\n"
					"	for (int i = 0; i < " << ((ostringstream()) << len).str() << "; i++) {\n"
					"		arr[i].value = 0;\n"
					"	}\n"
					"	int index = 0;\n";
				out << oss.str();
			}


			char repeat_char = codes[0][0]; // repeat character
			int repeat_count = 0; // repeat count of repeat character
			int print_level = 1; // storage code indentation
			for (int line = 0; line < codes.size(); line++) { // every line, i = index for line
				string code = codes[line];
				string out_line = "";

				// read every character in the code
				for (int i = 0; i < code.size(); i++) {

					// print some TAB to optimize code indentation
					for (int w = 0; w < print_level - (code[i] == ']'); w++) {
						out_line << '\t'; // print some '\t'
						// if code[i] = ']', output one less
					}

					// enumerate the possibilities of all characters
					switch (code[i]) {
					case '>':
						out_line << "++index;" << '\n';
						break;
					case '<':
						out_line << "--index;" << '\n';
						break;
					case '+':
						out_line << "++arr[index];" << '\n';
						break;
					case '-':
						out_line << "--arr[index];" << '\n';
						break;
					case '.': // output a number
						out_line << "arr[index].print();" << '\n'; // a space is used to separate each output
						break;
					case ',': // input a number
						out_line << "cin >> arr[index].value;" << '\n';
						break;
					case '[': // start loop
						out_line << "while(arr[index].value) {" << '\n';
						print_level++;
						break;
					case ']': // end loop
						out_line << "}" << '\n';
						print_level--;
						break;
					case '*': // negative output
						cout << "into the negative output" << endl;
						out_line << "arr[index].unprint();" << '\n';
						break;
					case '#': // comments
						out_line << "// comment: ";
						for (; !(code[i] == '\0' || code[i] == '\n'); i++) {
							out_line << code[i];
						}
						out_line << '\n';
						break;

						// legal character enumeration
					case ' ': // space
					case '\n': // line break
					case '\t': // tab

						break; // all to break

					default:
						bf::errors.push_back(bf::char_excepter(code[i], line + 1, i + 1));
						break;
					} // end switch

					if (i % 10 == 0)debug << "--Data-- i(index of character) = " << i << endl;

					// refresh the repeat_char and repeat_count
					if (repeat_char == code[i]) {
						repeat_count++;
					}
					else {
						repeat_char = code[i];
						repeat_count = 0;
					}

					// write the out_line to out
					out << out_line;


					// optimization for repeat characters
					if (repeat_count >= 5) {
						// revoke the changes
						debug << "--Optimization-- repeat_char = " << repeat_char << ", repeat_count = " << repeat_count << endl;
						for (int x = 0;x < repeat_count;x++) {
							debug << "--Will-- out.revoke()" << endl;
							out.revoke();
						}

						// debug << "--Optimization-- after revoke, out =\n\033[93m" << out.str() << "\033[0m" << endl;


						int truth_count = repeat_count; // the count of the repeat chars
						for (int j = i + 1;code[j] == repeat_char;j++) {
							debug << "--Optimization-- found a repeat_char, index = " << j << endl;
							truth_count++;
							i = j; // move the index to the last repeat char
						}

						debug << "--Optimization-- truth_count = " << truth_count << endl;

						// write
						// enumerate the possibilities of all characters

						string write_str = "/* optimiazation */ "; // temp output string


						switch (repeat_char) {
						case '>':
							write_str << "index += " << truth_count << ";" << '\n';
							break;

						case '<':
							write_str << "index -= " << truth_count << ";" << '\n';
							break;

						case '+':
							write_str << "arr[index].value += " << truth_count << ";" << '\n';
							break;

						case '-':
							write_str << "arr[index].value -= " << truth_count << ";" << '\n';
							break;

						case '.':
							write_str << "for (int i = 0; i < " << truth_count << "; i++) {" << '\n'
								<< "\tarr[index].print();" << '\n'
								<< "}" << '\n';
							break;

						case ',':
							write_str << "for (int i = 0; i < " << truth_count << "; i++) {" << '\n'
								<< "\tcin >> arr[index].value;" << '\n'
								<< "}" << '\n';
							break;

						default:
							debug << "--Optimization-- cannot optimization char: " << repeat_char << endl;
						}

						// write to out
						debug << "--Optimization-- write_str =\n\033[93m" << write_str << "\033[0m" << endl;
						out << write_str;

						// initialize the variables for repeat chars' optimization
						repeat_char = 0;
						repeat_count = 0;
						truth_count = 0;
					} // end optimization


					out_line = ""; // clear out_line for next character
				} // end read every character
			}

			// output the end of main function
			out << "	return 0;" << '\n'
				<< "}";


			// ------ end of program output ------ //


			debug << "--Data-- out =\n\033[93m" << out.str() << "\033[0m" << endl;

			file << out.str();
			file.close();




			// Call GNU


			// read the install path from "install_path.txt"
			ifstream path_file("configs\\install_path.txt");
			if(!path_file.is_open()) {
				file_errors.push_back(file_error("The file: \"configs\\install_path.txt\" cannot read."));
				return;
			}


			getline(path_file, bf::install_path);
			path_file.close();
			
			cout << "install_path = " << bf::install_path << endl;
			cout << "gpp_path     = " << bf::install_path + "\\mingw64\\bin\\g++.exe" << endl;
			cout << "cmd          = " << "\"" + bf::install_path + "\\mingw64\\bin\\g++.exe\" output-temp.cpp -o " + out_path << endl;

			// check g++.exe 's state
			if (!bf::install_path.empty()) {
				string gpp_path = bf::install_path + "\\mingw64\\bin\\g++.exe";
				ifstream gpp_file(gpp_path);
				if (!gpp_file.is_open()) {
					file_errors.push_back(file_error(("The file: \"" + gpp_path + "\" cannot read.")));
					return;
				}
				gpp_file.close();
			}
			else {
				file_errors.push_back(file_error("The install path is not set. Please set the install path in \"configs\\install_path.txt\"."));
			}

			// call GNU Compiler Collection to compile the output program
			string cmd = "\"" + bf::install_path + "\\mingw64\\bin\\g++.exe\" output-temp.cpp -o " + out_path;

			system(cmd.c_str());







			debug << "--Will-- delete output-temp.cpp" << endl;

			if(debug.get_out()){
				system("pause");
			}
			system("del output-temp.cpp");

			cout << "\033[0m";

		}
	};
}

#endif // !COMPILER_H