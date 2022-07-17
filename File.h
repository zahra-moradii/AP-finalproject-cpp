#pragma once

using namespace std;
#include <string>
#include "Adaptor.h"

class File : public Adaptor
{
private:
	string path;
public:
	File(string p);
	void setPath(string);
	string getPath();

	string read(); 
	void write(string);
	void deleteLine(const char *file_name, int n);
	void rest(int adapt);
};

