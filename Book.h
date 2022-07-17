#pragma once
#include <string>
#include "File.h"

class Book:public File 
{
private:
	int id;
	string name, writerName;
	int edition;
public:
	Book(int, string, string, int, string);
	void setID(int);
	int getID();
	void setName(string);
	string getName();
	void setWriterName(string);
	string getWriterName();
	void setEdition(int);
	int getEdition();
	void write(Book);
	Book  search(int i, int*);
	Book  search(string s, int*);
	string  toSring();
	void  printAll();

};

