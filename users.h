#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <c++php.h>
using namespace std;

int update_hours(string fname, string lname, int total[3]);

class list {
	public:
	list();
	int append(string fname, string lname, string sign_in);
	int signout(string fname, string lname, string sign_out);
	string user(int i, int t);
	int size();
	
	private:
	vector <string> fnames;
	vector <string> lnames;
	vector <string> sign_in;
	vector <string> sign_out;
	int people;
};

list::list() {
	list::people = 0;
}

string list::user(int i, int t = 0) {
	if (i >= list::people) {
		return "";
	}
	if (t == 0) {
		return list::fnames[i];
	} else if (t == 1) {
		return list::lnames[i];
	} else if (t == 2) {
		return list::sign_in[i];
	} else if (t == 3) {
		return list::sign_out[i];
	}
}

int list::size() {
	return list::people;
}

int list::append(string fname, string lname, string sign_in) {
	list::fnames.push_back(fname);
	list::lnames.push_back(lname);
	list::sign_in.push_back(sign_in);
	list::sign_out.push_back("");
	list::people++;
	return 1;
}

int list::signout(string fname, string lname, string sign_out) {
	int pos = -1;
	for (int i = 0; i < list::fnames.size() && i < list::lnames.size(); i++) {
		if (list::fnames[i] == fname && list::lnames[i] == lname) {
			// Checking if there's a match
			list::sign_out[i] = sign_out;
			pos = i;
			break;
		}
	}
	if (pos != -1) {
		// Process the date-time of the user
		int total[2][3] = {{0, 0, 0}, {0, 0, 0}};
		string buf = "";
		int ins[2] = {0, 0};
		
		/*
		Sign In Time
		*/
		for (int i = 0; i < list::sign_in[pos].length(); i++) {
			if (list::sign_in[pos][i] != ':') {
				buf.push_back(list::sign_in[pos][i]);
			} else {
				stringstream STREAM;
				STREAM << buf;
				STREAM >> total[ins[0]][ins[1]];
				ins[1]++;
				if (ins[1] > 2) { ins[0]++; ins[1] = 0; }
				if (ins[0] > 0) break;
				buf = "";
			}
		}
		if (buf != "") {
			stringstream STREAM;
			STREAM << buf;
			STREAM >> total[ins[0]][ins[1]];
			buf = "";
		}
		/*
			Sign Out Time
		*/
		ins[0] = 1;
		ins[1] = 0;
		buf = "";
		for (int i = 0; i < list::sign_out[pos].length(); i++) {
			if (list::sign_out[pos][i] != ':') {
				buf.push_back(list::sign_out[pos][i]);
			} else {
				stringstream STREAM;
				STREAM << buf;
				STREAM >> total[ins[0]][ins[1]];
				ins[1]++;
				if (ins[1] > 2) { ins[0]++; ins[1] = 0; }
				if (ins[0] > 1) break;
				buf = "";
			}
		}
		if (buf != "") {
			stringstream STREAM;
			STREAM << buf;
			STREAM >> total[ins[0]][ins[1]];
			buf = "";
		}
		/*
			Now, if the difference in hours
			is negative. Then assume it wasn't
			set in 24 hour time
		*/
		int diff[3] = {0, 0, 0};
		// Hours
		if (total[1][0] - total[0][0] < 0) {
			diff[0] = (total[1][0]+12)-total[0][0];
		} else {
			diff[0] = total[1][0]-total[0][0];
		}
		// Minutes
		if (total[1][1] - total[0][1] < 0) {
			diff[1] = (total[1][1]+60)-total[0][1];
			diff[0] -= 1;
		} else {
			diff[1] = total[1][1]-total[0][1];
		}
		// Seconds
		if (total[1][2] - total[0][2] < 0) {
			diff[2] = (total[1][2]+60)-total[0][2];
			diff[1] -= 1;
		} else {
			diff[2] = total[1][2]-total[0][2];
		}
		if (diff[1] < 0) {
			diff[1] + 60;
			diff[0]--;
		}
		if (diff[0] < 0 || diff[1] < 0 || diff[2] < 0) {
			return -1;
		} else {::
			update_hours(fname, lname, diff);
			if (1==1) {
				vector <string> before;
				vector <string> after;
				int a = 0;
				list::fnames.erase(list::fnames.begin()+pos);
			}
			if (1==1) {
				vector <string> before;
				vector <string> after;
				int a = 0;
				list::lnames.erase(list::lnames.begin()+pos);
			}
			if (1==1) {
				vector <string> before;
				vector <string> after;
				int a = 0;
				list::sign_in.erase(list::sign_in.begin()+pos);
			}
			if (1==1) {
				vector <string> before;
				vector <string> after;
				int a = 0;
				list::sign_out.erase(list::sign_out.begin()+pos);
			}
			list::people--;
		}
	}
	return 1;
}

int update_hours(string fname, string lname, int total[3]) {
	ifstream stream("hours.csv");
	if (!stream.good()) {
		ofstream s2("hours.csv");
		s2.close();
	}
	string line = "";
	int found = 0;
	stream.open("hours.csv");
	while (stream.good()) {
		getline(stream, line);
		vector <string> items = explode(",", line);
		if (items[0] == fname && items[1] == lname) {
			found = 1;
		}
	}
	stream.close();
	int hour = 0;
	if (total[2] > 30) total[1]++;
	if (total[1] >= 60) { total[0]++; total[1] = 0; }
	if (found == 0) {
		ofstream stream("hours.csv", ios::out || ios::app);
		stream << fname << ", " << lname << ", " << 
	}
}
