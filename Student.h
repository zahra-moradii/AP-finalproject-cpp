#pragma once
using namespace std;
#include <string>
#include "File.h"

class Student: public File
{
private:
	int id;
	string name, lastName;
	float grade; 
public:
	Student(int, string, string, float, string);
	void setID(int); 
	int getID(); 
	void setName(string);
	string getName();
	void setLastName(string);
	string getLastName();
	void setGrade(float);
	float getGrade();
	void write(Student);
	Student  search(int id, int*);
	Student  search(float g, int*);
	Student  search(string s, int*);
	string  toSring();
	void  printAll();
};

