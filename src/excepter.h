#ifndef EXCEPTER_H
#define EXCEPTER_H

#include <iostream>
#include <string>

namespace bf {
	class char_excepter {
	public:
		char error_char;
		int line;
		int column;

		char_excepter(char error_char, int line, int column) {
			this->error_char = error_char;
			this->line = line;
			this->column = column;
		}
	};


}

class arg_error {
public:
	const char* error_arg;
	arg_error(const char* error_arg) {
		this->error_arg = error_arg;
	}
};

class file_error {
public:
	const char* error_file;
	file_error(const char* error_file) {
		this->error_file = error_file;
	}
	file_error(std::string error_file) {
		this->error_file = error_file.c_str();
	}
};

class compile_data_error {
public:
	const char* error_compile_data;
	compile_data_error(const char* error_compile_data) {
		this->error_compile_data = error_compile_data;
	}
};

#endif // !EXCEPTER_H
