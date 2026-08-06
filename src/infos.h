#ifndef INFOS_H
#define INFOS_H

#include <iostream>
#include <Windows.h>
using namespace std;

namespace infos {
	void version() {
		// Enable ANSI escape codes for colorful text in Windows console
#ifdef _WIN32
#ifndef COLORFUL_TEXT
		// ANSI colorful text (Windows 10+)
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwMode = 0;
		GetConsoleMode(hOut, &dwMode);
		SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif // COLORFUL_TEXT	
#endif // _WIN32
		cout <<
			"\033[93m"
			" _   _                ____                           _  _                ___      _     _  _     ___  \n| \\ | |  ___  __  __ / ___|  ___   _ __ ___   _ __  (_)| |  ___  _ __   / _ \\    / |   | || |   ( _ ) \n|  \\| | / _ \\ \\ \\/ /| |     / _ \\ | '_ ` _ \\ | '_ \\ | || | / _ \\| '__| | | | |   | |   | || |_  / _ \\ \n| |\\  || (_) | >  < | |___ | (_) || | | | | || |_) || || ||  __/| |    | |_| | _ | | _ |__   _|| (_) |\n|_| \\_| \\___/ /_/\\_\\ \\____| \\___/ |_| |_| |_|| .__/ |_||_| \\___||_|     \\___/ (_)|_|(_)   |_|   \\___/ \n                                             |_|                                                      \n"
			"\033[0m"
			<< endl;


	}
	void help() {
		cout << "Usage: nox -s source -o output [-arg { cardinal cardinal-num | length length-num | ascii ascii-state }][--debug]" << endl;
		cout << "       nox --help" << endl;
		cout << "       nox --version" << endl;
		cout << endl;
		cout << "Comments:" << endl;
		cout << "    source         source code file name" << endl;
		cout << "    cardinal-num   the base of each storage cell in brainf**k or its maximum value plus one" << endl;
		cout << "    output         output file name" << endl;
		cout << "    length-num     size for brainf**k array" << endl;
		cout << "    ascii-state    true or false, enable of output as ASCII characters " << endl;
		cout << "                   default value is false" << endl;
		cout << endl;
		cout << "    --debug        output the debug infomation" << endl;
		cout << endl;
		cout << "    --help         output this message, use only" << endl;
		cout << "    --version      output the version for nox compiler, use only" << endl;
		cout << endl;
		cout << "Examples:" << endl;
		cout << "    nox --help" << endl;
		cout << "    nox --version" << endl;
		cout << "    nox -s D:\\my_code.txt" << endl;
		cout << "    nox -s D:\\my_code.txt -o D:\\output.exe" << endl;
		cout << "    nox -s D:\\my_code.txt -o D:\\output.exe -arg cardinal 1000" << endl;
		cout << "    nox -s D:\\my_code.txt -o D:\\output.exe -arg length 10000" << endl;
		cout << "    nox -s D:\\my_code.txt -o D:\\output.exe -arg ascii true" << endl;
		cout << "    nox -s D:\\my_code.txt -o D:\\output.exe -arg cardinal 1000 -arg length 10000" << endl;
		cout << "    nox -s D:\\my_code.txt -o D:\\output.exe -arg cardinal 1000 -arg length 10000 --debug" << endl;
		cout << endl;
		cout << "More:" << endl;
		cout << "    1  Nox Compiler supported Windows only (now version)" << endl;
		cout << "    2  Nox Compiler relies on the GNU compiler toolset" << endl;
		cout << "       Because during the compilation process C++ source code files will be generated" << endl;
		cout << "    3  Nox Compiler remains open source" << endl;

	}
}

#endif // !INFOS_H
