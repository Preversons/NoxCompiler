#pragma once
#ifndef UNCERT_H
#define UNCERT_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include "debugger.h"
using namespace std;

class uncert {
private:
	string info;
	stack<string> aband;
	vector<int> change_len;

public:
	uncert(string info, vector<int> change_len) :
		info(info), change_len(change_len), aband(stack<string>())
	{}
	uncert() :
		info(""), change_len(vector<int>()), aband(stack<string>())
	{}

	// get the info of uncert
	string str() const { return this->info; }

	// revoke the last change
	void revoke() {
		if (change_len.size() == 0) {
			return;
		}

		string remove_string;
		int removed_len = info.size() - change_len[change_len.size() - 1]; // get the length of the string to be removed

		for (int i = info.size() - 1; i > removed_len - 1; i--) {
			remove_string.insert(remove_string.begin(), info[i]);
			info.pop_back();
		}

		aband.push(remove_string);

	}

	void restore() {
		if (aband.empty()) {
			return;
		}
		string restore_string = aband.top();
		info += restore_string;
		aband.pop();
	}

	uncert& write_str(const string& s) {
		change_len.push_back(s.size());
		info += s;

		//debug << "==Uncert== write_str:\n\tchange_len = " << change_len
		//	<< "\n\tlastest change_len = " << change_len[change_len.size() - 1]
		//	<< endl;


		return *this;
	}

	void clear() {
		info = "";
		change_len.clear();
		while (!aband.empty()) {
			aband.pop();
		}
	}

	friend ostream& operator<<(ostream&, const uncert&);
};

// output object of uncert
ostream& operator<<(ostream& out, const uncert& u) {
	out << u.info;
	return out;
}

// add data to uncert
template<typename t>
uncert& operator<<(uncert& u, const t& d) {
	ostringstream oss;
	oss << d;
	
	u.write_str(oss.str());

	return u;
}

#endif // !UNCERT_H
