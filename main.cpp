#include <iostream>
#include <ncurses.h>
#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"
using namespace std;

bool ncurses_clear(int rows, int cols);

int main() {
	initscr();
	int rows = 0, cols = 0;
	int quit = 0;
	getmaxyx(stdscr, rows, cols);
	list users;
	users.append("Josh", "Larson", "11:45:05");
	while (quit == 0) {
		int line = 1;
		ncurses_clear(rows, cols);
		mvprintw(0, 0, "User List:");
		for (int i = 0; i < users.size(); i++) {
			string fname = users.user(i, 0);
			string lname = users.user(i, 1);
			mvprintw(line, 4, fname.c_str());
			mvprintw(line, fname.length()+5, lname.c_str());
			line++;
		}
		mvprintw(rows-1, 0, "Add User or Sign Out? ");
		refresh();
		char strc[256];
		getstr(strc);
		string str = strc;
		if (strtolower(str) == "quit") {
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
				timein = str2;
			}
			ncurses_clear(rows, cols);
			users.append(fname, lname, timein);
		} else if (strtolower(str) == "signout" || strtolower(str) == "sign out") {
			ncurses_clear(rows, cols);
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
		}
	}
	ncurses_clear(rows, cols);
	mvprintw(rows-2, 0, "Users have been saved.");
	mvprintw(rows-1, 0, "Press any key to continue...");
	getch();
	endwin();
}

bool ncurses_clear(int rows, int cols) {
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			mvaddch(y, x, ' ');
		}
	}
}
