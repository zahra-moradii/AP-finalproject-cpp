#include "stdafx.h"
#include "File.h"
#include <fstream>

File::File(string p)
{
	this->path = p;
}

void File::setPath(string s)
{
	this->path = s; 
}
string File::getPath() {
	return this->path; 
}


string File::read() {
	string line;
	ifstream infile(this->path, ios::in | ios::binary);
	getline(infile, line);
	infile.close();
	return line; 
}

void File::write(string s) {

	ofstream myFile(this->path, ios::out | ios::binary | ios::app);
	myFile.write(s.c_str(), s.length());
	myFile.close();
}


void File::rest(int adapt) {
	remove(this->path.c_str());
	setAdaptorType(adapt);

}


void File::deleteLine(const char *file_name, int n)
{
	ifstream is(file_name);
	ofstream ofs;
	ofs.open("temp.txt", ofstream::out);

	char c;
	int line_no = 1;
	while (is.get(c))
	{
		
		if (line_no != n)
			ofs << c;
		if (c == '\n')
			line_no++;
	}

	ofs.close();
	is.close();

	remove(file_name);
	rename("temp.txt", file_name);
}