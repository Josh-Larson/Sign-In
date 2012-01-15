#include <iostream>
#include <ncurses.h>
#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"
using namespace std;

bool ncurses_clear(int rows, int cols);

int main(int argc, char *argv[]) {
	initscr();
	int rows = 0, cols = 0;
	getmaxyx(stdscr, rows, cols);
	int quit = 0;
	getmaxyx(stdscr, rows, cols);
	mousemask(ALL_MOUSE_EVENTS, NULL);
	MEVENT event;
	list users;
	while (quit == 0) {
		int line = 1;
		ncurses_clear(rows, cols);
		getmaxyx(stdscr, rows, cols);
		mvprintw(0, 0, "User List:");
		time_t _t;
		struct tm * _timeinfo;
		time(&_t);
		_timeinfo = localtime(&_t);
		char _buf[100] = "";
		strftime(_buf, 100, "%I:%M:%S", _timeinfo);
		for (int i = 0; i < users.size(); i++) {
			string fname = users.user(i, 0);
			string lname = users.user(i, 1);
			mvprintw(line, 4, fname.c_str());
			mvprintw(line, fname.length()+5, lname.c_str());
			int diff[3] = {0, 0, 0};
			stringstream STREAM;
			STREAM << ((diff[0]*60)+diff[1]);
			string minute = "";
			STREAM >> minute;
			printw(string(" ["+users.user(i, 2)+"] (" + minute + ")").c_str());
			line++;
		}
		mvprintw(rows-2, 0, "Type in 'Help' to view function list.");
		mvprintw(rows-1, 0, "[Team2502@localhost SignIn]$ ");
		refresh();
		char strc[256];
		halfdelay(10);
		getstr(strc);
		string str = strc;
		if (strtolower(str) == "quit" || strtolower(str) == "exit") {
			quit = 1;
		} else if (strtolower(str) == "add" || strtolower(str) == "signin" || strtolower(str) == "sign in") {
			ncurses_clear(rows, cols);
			string fname = "";
			string lname = "";
			string timein = "";
			time_t t;
			struct tm * timeinfo;
			time(&t);
			timeinfo = localtime(&t);
			char buf[100] = "";
			strftime(buf, 100, "%I:%M:%S", timeinfo);
			mvprintw(0, 0, "First Name:   ");
			mvprintw(1, 0, "Last Name:    ");
			mvprintw(2, 0, "Sign In Time: ");
			mvprintw(3, 0, string("Current Time: ").append(buf).c_str());
			move(0, 14);
			if (1==1) {
				char strc2[256];
				refresh();
				getstr(strc2);
				string str2 = strc2;
				fname = str2;
			}
			move(1, 14);
			if (1==1) {
				char strc2[256];
				refresh();
				getstr(strc2);
				string str2 = strc2;
				lname = str2;
			}
			move(2, 14);
			if (1==1) {
				char strc2[256];
				refresh();
				getstr(strc2);
				string str2 = strc2;
				if (str2.compare("") == 0) {
					timein = buf;
				} else {
					timein = str2;
				}
			}
			ncurses_clear(rows, cols);
			users.append(fname, lname, timein);
		} else if (strtolower(str) == "signout" || strtolower(str) == "sign out") {
			ncurses_clear(rows, cols);
			// Show users
			int line = 5;
			mvprintw(4, 0, "User List:");
			for (int i = 0; i < users.size() && line < rows-1; i++) {
				string fname = users.user(i, 0);
				string lname = users.user(i, 1);
				mvprintw(line, 4, fname.c_str());
				mvprintw(line, fname.length()+5, lname.c_str());
				line++;
			}
			mvprintw(0, 0, "First Name:   ");
			mvprintw(1, 0, "Last Name:    ");
			move(0, 14);
			string fname = "";
			string lname = "";
			if (1==1) {
				char str2c[256];
				getstr(str2c);
				fname = str2c;
			}
			move(1, 14);
			if (1==1) {
				char str2c[256];
				getstr(str2c);
				lname = str2c;
			}
			int signouted = 0;
			for (int i = 0; i < users.size(); i++) {
				if (users.user(i, 0) == fname && users.user(i, 1) == lname) {
					signouted = 1;
					time_t t;
					struct tm * timeinfo;
					time(&t);
					timeinfo = localtime(&t);
					char buf[256];
					strftime(buf, 100, "%I:%M:%S", timeinfo);
					users.signout(fname, lname, string(buf));
					break;
				}
			}
		} else if (strtolower(str) == "help") {
			ncurses_clear(rows, cols);
			mvprintw(0, 0, "Possible Functions: (Case-Insensitive)");
			mvprintw(1, 4, "add:      This will bring up a prompt to sign on");
			mvprintw(2, 4, "sign in:  Same as add");
			mvprintw(3, 4, "sign out: This will bring up a prompt to log out. Uses current time.");
			mvprintw(4, 4, "quit:     Saves all users to the .csv file.");
			mvprintw(5, 4, "exit:     Same as quit.");
			mvprintw(rows-1, 0, "Press Any Key to Continue...");
			getch();
		}
	}
	ncurses_clear(rows, cols);
	endwin();
	cout << "Users Saved.\n";
}

bool ncurses_clear(int rows, int cols) {
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			mvaddch(y, x, ' ');
		}
	}
}
