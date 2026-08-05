#include <iostream>
#include "compiler.h"
#include "infos.h"
using namespace std;
using namespace bf;

using comp = compiler;

#ifndef ERROR_EXIT
#define ERROR_EXIT         \
cout << "[Exit]" << endl;  \
return 1;
#endif // !ERROR_EXIT

// compare two string, if they are equal, return true, else return false
bool streql(const char value[], const char cmp_value[]) {
	return (strcmp(value, cmp_value) == 0);
}

// print some characters as a line, the default character is '='
void line(int count, char ch = '=') {
	for (int i = 0; i < count; i++) {
		putchar(ch);
	}
	putchar('\n');
}

int main(int argc, const char* argv[]) {
	// if not has any argument, this is 1 argument caused by the program name
	if (argc == 1) {
		cout << "Enter \"nox --help\" for more infomation." << endl;
		return 0; // Exit if not has any argument
	}

	// 1. parse every argument
	bool has_s = false; // has source file argument
	bool has_o = false; // has output file argument
	comp compiler;
	ifstream input;
	for (int i = 1; i < argc; i++) {
		if (streql(argv[i], "-o")) {
			if (i == argc - 1) { // if i is finally argument
				cout << arg_error("An argument must follow \"-o\" to specify the output file.") << endl;

				cout << "Enter \"nox --help\" for more infomation." << endl;

				ERROR_EXIT;
			}

			// no error todo:
			compiler.out_path = string(argv[i + 1]);
			has_o = true;
			i++;

			continue;
		}
		if (streql(argv[i], "-arg")) {
			if ((i + 2) > argc - 1) {
				const char* info =
					"Two arguments must follow \"-arg\".\n"
						"\tThe first one is argument name.\n"
						"\tThe second one is argument value.";
				cout << arg_error(info) << endl;

				cout << "Enter \"nox --help\" for more infomation." << endl;

				ERROR_EXIT;
			}

			// no error todo:
			if (streql(argv[i + 1], "cardinal")) {
				istringstream(argv[i + 2]) >> compiler.cardinal;
			}
			else if (streql(argv[i + 1], "length")) {
				istringstream(argv[i + 2]) >> compiler.len;
			}
			else if (streql(argv[i + 1], "ascii")) {

				// parse the argument following "ascii"
				if      (streql(argv[i + 2], "true")  || streql(argv[i + 2], "1"))compiler.ascii_enable = true;
				else if (streql(argv[i + 2], "false") || streql(argv[i + 2], "0"))compiler.ascii_enable = false;
				else { // throw the error
					cout << arg_error((ostringstream() << "Illegal argument: " << argv[i + 2] << ".").str().c_str()) << endl;
					cout << "Enter \"nox --help\" for more infomation." << endl;
					ERROR_EXIT;
				}

				debug << "ascii_enable = " << compiler.ascii_enable << endl;
			}
			else {
				cout << arg_error((ostringstream() << "Illegal argument: " << argv[i + 1] << ".").str().c_str()) << endl;

				cout << "Enter \"nox --help\" for more infomation." << endl;

				ERROR_EXIT;
			}
			i += 2;

			continue;
		}
		if (streql(argv[i], "-s")) {
			if (i == argc - 1) { // if i is finally argument
				cout << arg_error("A argument must follow \"-s\" to specify the source file.") << endl;

				cout << "Enter \"nox --help\" for more infomation." << endl;

				ERROR_EXIT;
			}

			input.open(argv[i + 1]);
			if (!input.is_open()) {
				cout << file_error(string(
					"The file: " + string(argv[i + 1]) + " cannot open."
				).c_str());
				ERROR_EXIT;
			}
			has_s = true;
			i++;

			continue;
		}

		if (streql(argv[i], "--debug")) {
			debug.set_out(true);
			continue;
		}

		if (streql(argv[i], "--help")) {
			infos::help();
			return 0; // Exit
		}
		if (streql(argv[i], "--version")) {
			infos::version();
			return 0; // Exit
		}

		// if has any other argument, ignore it
		
		cout << arg_error((ostringstream() << "Illegal argument: " << argv[i] << ".").str().c_str()) << endl;

		cout << "Enter \"nox --help\" for more infomation." << endl;

		ERROR_EXIT;
		
	}

	// 2. if not has source file argument or output file argument
	debug << "has_s = " << has_s << ", has_o = " << has_o << endl;
	if (!(has_s && has_o)) {
		if (!has_s)cout << arg_error("The source file argument is required.") << endl; // output source file error
		if (!has_o)cout << arg_error("The output file argument is required.") << endl; // output output file error
		
		cout << "Enter \"nox --help\" for more infomation." << endl;
		
		ERROR_EXIT; // Exit if not has source file or output file argument
	}
	
	// 3. read the source code file and save it to compiler.codes
	{
		string temp; // every line
		while (getline(input, temp)) {
			compiler.codes.push_back(temp);
		}
	}

	// 4. compile
	cout << "Compiling..." << endl;
	cout << endl;





	
	
	compiler.compile(); // compile, the main process of compilation is in this function, and it may make some error
	






	// 5. output compile result
	if (errors.size() == 0) { // no any error
		cout << "Compile successfully." << endl;
	}
	else { // it has error
		for (file_error& e : file_errors) { // output every file error
			cout << "\033[91m" << e << "\033[0m" << endl;
		}
		for (char_excepter& e : errors) { // output every error
			cout << "\033[91m" << e << "\033[0m" << endl;
		}
		ERROR_EXIT;
	}

	// 6. close the source code file
	input.close(); // close the file
	if (input.is_open()) { // if the file wasn't saved successfully
		cout << file_error(string("The file: " + string(argv[1]) + " cannot close.").c_str()) << endl; // output the error
		ERROR_EXIT; // and exit
	}

	// 7. exit
	cout << "[Exit]" << endl;

	cout << "\033[0m";

	return 0;
}
