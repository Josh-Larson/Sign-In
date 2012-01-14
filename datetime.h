#include <iostream>
#include <ctime>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
using namespace std;

class DateTime {
	public:
	DateTime();
	
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

DateTime::DateTime() {
	time_t t;
	struct tm * timeinfo;
	time(&t);
	timeinfo = localtime(&t);
	DateTime::year=0;DateTime::month = 0;DateTime::day = 0;DateTime::hour = 0;DateTime::minute = 0;DateTime::second = 0;
	if (1==1) {
		char buf[10];
		stringstream STREAM;
		strftime(buf, 10, "%Y", timeinfo);
		STREAM << buf;
		STREAM >> year;
	}
	
	if (1==1) {
		char buf[10];
		stringstream STREAM;
		strftime(buf, 10, "%m", timeinfo);
		STREAM << buf;
		STREAM >> month;
	}
	
	if (1==1) {
		char buf[10];
		stringstream STREAM;
		strftime(buf, 10, "%d", timeinfo);
		STREAM << buf;
		STREAM >> day;
	}
	
	if (1==1) {
		stringstream STREAM;
		char buf[10];
		strftime(buf, 10, "%H", timeinfo);
		STREAM << buf;
		STREAM >> hour;
	}
	
	if (1==1) {
		stringstream STREAM;
		char buf[10];
		strftime(buf, 10, "%M", timeinfo);
		STREAM << buf;
		STREAM >> minute;
	}
	
	if (1==1) {
		stringstream STREAM;
		char buf[10];
		strftime(buf, 10, "%S", timeinfo);
		STREAM << buf;
		STREAM >> second;
	}
}
