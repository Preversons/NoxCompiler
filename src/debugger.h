#pragma once
#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread>
using namespace std;

namespace debugger_ns {

	// version 1
	namespace v1 {

		class DebuggerStream {
		private:
			ostream* out; // point to a ostream object, default is &cout

		public:
			DebuggerStream(ostream* out) : out(out) {}

			template<typename T>
			DebuggerStream& operator<<(const T& message) {
				if (out) {
					*out << message;
				}
				return *this;
			}

			DebuggerStream& operator<<(ostream& (*manip)(ostream&)) {
				if (out) {
					*out << manip;
				}
				return *this;
			}

			DebuggerStream& operator<<(ios_base& (*manip)(ios_base&)) {
				if (out) {
					*out << manip;
				}
				return *this;
			}
		};

		class DebuggerHead {
		private:
			ostream* out; // point to a ostream object, default is &cout
			DebuggerStream* debugger; // point to a DebuggerStream object, default is nullptr

			bool out_enbale;

		public:
			DebuggerHead(ostream* out) : out(out), debugger(nullptr), out_enbale(true) {}
			DebuggerHead() : out(&cout), debugger(nullptr), out_enbale(true) {}

			// Get the current output status
			bool is_out() const { return out_enbale; }

			// Set out_enable to enable(argument)
			DebuggerHead& set_out(bool enbale) {
				this->out_enbale = enbale;

				return *this;
			}

			// Redirect the output to a new ostream object
			DebuggerHead to(ostream* out) {
				if (!out)return *this;
				this->out = out;
				this->debugger = nullptr;

				return *this;
			}

			// output the data to the ostream object, and return a DebuggerStream object to continue output
			template<typename T>
			DebuggerStream operator<<(const T& data) {
				if (out_enbale == false)return DebuggerStream(nullptr);

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

				ostream& o = (*out);

				if (debugger)delete debugger;
				debugger = new DebuggerStream(out);

				auto now = time(nullptr);

				tm localTime;
				localtime_s(&localTime, &now);

				// Output the infomations in the format:
				// [YYYY-MM-DD] [DEBUG INFOMATION] < THREAD_ID at HH:MM:SS >: DATA
				o
					<< "\033[90m" // Set DebuggerHead's text color to gray
					<< put_time(&localTime, "[%Y-%m-%d]") << " [DEBUG INFOMATION] < " << this_thread::get_id() << " at " << put_time(&localTime, "%H:%M:%S") << " >: "
					<< "\033[0m" // Close the color
					<< data;

				return *debugger;
			}
		};

		using Debugger = DebuggerHead;
	}

	// version 2, the newest version
	inline namespace v2 {
		ostream null_ostream(nullptr); // a null ostream object, used to return when output is disabled
		
		class Debugger {
		private:
			ostream* out; // point to a ostream object, default is &cout

			bool out_enbale; // whether output is enabled

		public:
			Debugger(ostream* out) : out(out), out_enbale(false) {}
			Debugger() : out(&cout), out_enbale(false) {}

			void set_out(bool enbale) {
				this->out_enbale = enbale;
			}
			bool get_out() const {
				return this->out_enbale;
			}

			template<typename T>
			ostream& operator<<(const T& data) {
				if (out_enbale == false)return debugger_ns::v2::null_ostream; // return a null ostream

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
				auto now = time(nullptr);

				tm localTime;
				localtime_s(&localTime, &now);

				// Output the infomations in the format:
				// [YYYY-MM-DD] [DEBUG INFOMATION] < THREAD_ID at HH:MM:SS >: DATA
				(*out)
					<< "\033[90m" // Set DebuggerHead's text color to gray
					<< put_time(&localTime, "[%Y-%m-%d]") << " [DEBUG INFOMATION] < " << this_thread::get_id() << " at " << put_time(&localTime, "%H:%M:%S") << " >: "
					<< "\033[0m" // Close the color
					<< data;

				return *out;

			};
		};
	}
}

namespace std {
	debugger_ns::Debugger debug;
}

#endif // !DEBUGGER_H
