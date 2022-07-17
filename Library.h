#pragma once
using namespace std;
#include <string>
#include "File.h"
#include <ctime>

class Library:public File
{
private:
	int studentId,bookID;
	time_t borrowTime; 
public:
	Library(int, int, time_t, string);
	void setStudentID(int);
	int getStudentID();
	void setBookID(int);
	int getBookID();
	void setBorrowTime(time_t);
	time_t getBorrowTime();

	void write(Library);
	Library  search(int id, int*);
	Library  search(time_t t, int*);
	Library  search(string s, int*);
	string  toSring();
	void  printAll();

};

