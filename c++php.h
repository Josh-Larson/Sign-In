#include <string.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

string str_replace(string del, string rep, string str) {
	string newstr = "";
	for (int i = 0; i < str.length(); i++) {
		int matches = 0;
		for (int a = 0; a < del.length() && i+a < str.length(); a++) {
			if (del[a] == str[i+a]) {
				matches++;
			} else break;
		}
		if (matches == del.length()) {
			newstr.append(rep);
			i+=matches-1;
		} else {
			newstr.push_back(str[i]);
		}
	}
	return newstr;
}

int strpos(string str, string del) {
	int position = -1;
	for (int i = 0; i < str.length(); i++) {
		int found = 0;
		for (int a = 0; a < del.length(); a++) {
			if (del[a] != str[i]) break;
			found++;
		}
		if (found == del.length()) {
			position = i;
			break;
		}
	}
	return position;
}

string strrev(string str) {
	string other = "";
	for (int i = str.length()-1; i >= 0; i--) {
		other.push_back(str[i]);
	}
	return other;
}

string strtoupper(string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}

string strtolower(string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}

int strlen(string str) {
	return str.length();
}

int ord(char a) {
	return int(a);
}

string ucfirst(string str) {
	if (str.length() >= 1) {
		str[0] = toupper(str[0]);
	}
	return str;
}

string ucwords(string str) {
	int status = 0;
	for (int i = 0; i < str.length(); i++) {
		if (status == 0) {
			str[i] = toupper(str[i]);
			status = 1;
		} else if (str[i] == ' ') {
			status = 0;
		}
	}
	return str;
}

vector <string> explode(string del, string str) {
	vector <string> e;
	string d = "";
	for (int i = 0; i < str.length(); i++) {
		int found = 0;
		for (int a = 0; a < del.length(); a++) {
			if (str[i+a] != del[a]) { found = 0; break; }
			found++;
		}
		if (found == del.length()) {
			e.push_back(d);
			d = "";
		} else {
			d.push_back(str[i]);
		}
	}
	if (d != "") e.push_back(d);
	return e;
}

string implode(vector <string> e) {
	string str = "";
	for (int i = 0; i < e.size(); i++) {
		str.append(e[i]);
	}
	return str;
}

string implode(string glue, vector <string> e) {
	string str = "";
	for (int i = 0; i < e.size(); i++) {
		str.append(e[i]);
		if (i != e.size()-1) {
			str.append(glue);
		}
	}
	return str;
}

string inttostr(int a) {
	stringstream STREAM;
	STREAM << a;
	string str;
	STREAM >> str;
	return str;
}

int strtoint(string str) {
	stringstream STREAM;
	STREAM << str;
	int a;
	STREAM >> a;
	return a;
}
