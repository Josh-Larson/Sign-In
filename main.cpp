#include <iostream>
#include <ncurses.h>
#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"
using namespace std;

bool ncurses_clear(int rows, int cols);

int main(int argc, char *argv[]) {
	/*
		Starts the Window
	*/
	initscr();
	int rows = 0, cols = 0;
	getmaxyx(stdscr, rows, cols);
	int quit = 0;
	getmaxyx(stdscr, rows, cols); /* Get the width/height of the terminal window */
	MEVENT event;
	list users; /* User List - Stores the signed in users (users.h) */
	while (quit == 0) {
		int line = 1;
		ncurses_clear(rows, cols); /* Clears the screen - Function declared at end of file */
		getmaxyx(stdscr, rows, cols);
		/*
		 * Outputs Users on Screen
		 * Acts as "Home Page"
		 */
		mvprintw(0, 0, "User List:");
		
		/* Stores Time in HH:MM:SS Format for _buf2 and _buf */
		time_t _t;
		struct tm * _timeinfo;
		time(&_t);
		_timeinfo = localtime(&_t);
		char _buf[100] = "";
		strftime(_buf, 100, "%I:%M:%S", _timeinfo);
		string _buf2 = _buf;
		
		/* Cycles through Users */
		for (int i = 0; i < users.size(); i++) {
			/* Retrieves User's first name and last name from the list (users) */
			string fname = users.user(i, 0);
			string lname = users.user(i, 1);
			/* Print out the name (tabbed) */
			mvprintw(line, 4, fname.c_str());
			mvprintw(line, fname.length()+5, lname.c_str());
			/* Get the time signed in by the user */
			int diff[3] = {0, 0, 0};
			int total[2][3] = {{0, 0, 0}, {0, 0, 0}};
			string time_in = users.user(i, 2);
			string buffer = "";
			int pos[2] = {0, 0};
			/* Seperate time_in into the array (total[0]) in format HH:MM:SS */
			for (int a = 0; a < time_in.length(); a++) {
				if (time_in[a] == ':') {
					stringstream STREAM;
					STREAM << buffer;
					STREAM >> total[pos[0]][pos[1]];
					pos[1]++;
					if (pos[1] > 2) { pos[0]++; pos[1] = 0; }
					if (pos[0] > 0) { break; }
					buffer = "";
					continue;
				} else {
					buffer.push_back(time_in[a]);
				}
			}
			pos[0] = 1;
			pos[1] = 0;
			/* Seperate _buf2 into array (total[1]) same as the for loop above */
			for (int a = 0; a < _buf2.length(); a++) {
				if (_buf2[a] == ':') {
					stringstream STREAM;
					STREAM << buffer;
					STREAM >> total[pos[0]][pos[1]];
					pos[1]++;
					if (pos[1] > 2) { pos[0]++; pos[1] = 0; }
					if (pos[0] > 1) { break; }
					buffer = "";
					continue;
				} else {
					buffer.push_back(_buf2[a]);
				}
			}
			/*
			 * Get difference from total ([0] && [1] => diff)
			 */
			get_diff(total, diff);
			stringstream STREAM;
			STREAM << ((diff[0]*60)+diff[1]);
			string minute = "";
			STREAM >> minute;
			printw(string(" ["+users.user(i, 2)+"] (" + minute + ")").c_str());
			line++;
		}
		/* Print Info at the bottom */
		mvprintw(rows-2, 0, "Type in 'Help' to view function list.");
		mvprintw(rows-1, 0, "[Team2502@localhost SignIn]$ ");
		refresh();
		char strc[256];
		getstr(strc); // Get Input from bottom of page
		string str = strc;
		/*
		 * Uses the input from (str)
		 */
		if (strtolower(str) == "quit" || strtolower(str) == "exit") {
			quit = 1; // Ends the main loop
		} else if (strtolower(str) == "add" || strtolower(str) == "signin" || strtolower(str) == "sign in") {
			ncurses_clear(rows, cols);
			string fname = "";
			string lname = "";
			string timein = "";
			/* Gets current time */
			time_t t;
			struct tm * timeinfo;
			time(&t);
			timeinfo = localtime(&t);
			char buf[100] = "";
			strftime(buf, 100, "%I:%M:%S", timeinfo);
			/* Outputs the fields */
			mvprintw(0, 0, "First Name:   ");
			mvprintw(1, 0, "Last Name:    ");
			mvprintw(2, 0, "Sign In Time: ");
			mvprintw(3, 0, string("Current Time: ").append(buf).c_str());
			/* Move to first field postition */
			move(0, 14);
			if (1==1) {
				/* 
				 * Uses 1==1 (or true) to allocate strc2
				 * and de-allocate it so I can use the
				 * same variable again later
				 */
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
				if (str2 == "") {
					timein = buf;
				} else {
					timein = str2;
				}
			}
			ncurses_clear(rows, cols);
			users.append(fname, lname, timein); // Add the user to the list
		} else if (strtolower(str) == "signout" || strtolower(str) == "sign out") {
			ncurses_clear(rows, cols);
			// Show user list
			int line = 5;
			mvprintw(4, 0, "User List:");
			for (int i = 0; i < users.size() && line < rows-1; i++) {
				string fname = users.user(i, 0);
				string lname = users.user(i, 1);
				mvprintw(line, 4, fname.c_str());
				mvprintw(line, fname.length()+5, lname.c_str());
				line++;
			}
			// Query to input first and last name
			mvprintw(0, 0, "First Name:   ");
			mvprintw(1, 0, "Last Name:    ");
			move(0, 14); // Move to First Name Input
			string fname = "";
			string lname = "";
			if (1==1) {
				char str2c[256];
				getstr(str2c); // Get Input
				fname = str2c;
			}
			move(1, 14); // Move to Last Name Input
			if (1==1) {
				char str2c[256];
				getstr(str2c); // Get Input
				lname = str2c;
			}
			// Sign out from users
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
			/*
			 * Clear Screen
			 * Then Show the help screen
			 */
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
	// Cycle through each character of screen
	// And set them to a space
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			mvaddch(y, x, ' ');
		}
	}
}
