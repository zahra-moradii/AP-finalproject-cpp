#include "stdafx.h"
#include <iostream>

using namespace std;

Library::Library(int si, int bi, time_t t, string p) :File{ p }
{
	this->studentId = si;
	this->bookID = bi;
	this->borrowTime = t;
	
}

void Library::setStudentID(int i) {
	this->studentId = i;
}

int Library::getStudentID() {
	return this->studentId;
}
void Library::setBookID(int i) {
	this->bookID = i;
}
int Library::getBookID() {
	return this->bookID;
}
void Library::setBorrowTime(time_t t) {
	this->borrowTime = t;
}
time_t Library::getBorrowTime() {
	return this->borrowTime;
}


void Library::write(Library lib) {
	ofstream myFile(lib.getPath(), ios::out | ios::binary | ios::app);

	myFile.write(reinterpret_cast<const char *>(&lib.studentId), sizeof(lib.studentId));
	myFile.write(reinterpret_cast<const char *>(&lib.bookID), sizeof(lib.bookID));
	myFile.write(reinterpret_cast<const char *>(&lib.borrowTime), sizeof(lib.borrowTime));

	myFile.close();
}

Library  Library::search(int id, int* r) {
	return this->search(to_string(id), r);
}
Library  Library::search(time_t t, int* r) {
	return this->search(to_string(t), r);
}
Library  Library::search(string s, int* r) {

	ifstream infile(this->getPath(), ios::in | ios::binary);

	*r = 1;

	while (infile.peek() != EOF)
	{
		int sId, bId;
		time_t t;

		infile.read(reinterpret_cast<char *>(&sId), sizeof(sId));
		infile.read(reinterpret_cast<char *>(&bId), sizeof(bId));
		infile.read(reinterpret_cast<char *>(&t), sizeof(t));


		if (to_string(sId).find(s) != string::npos ||
			to_string(bId).find(s) != string::npos) {

			return Library(sId, bId, t, this->getPath());
		}
		*r += 1;
	}
	infile.close();
	time_t t = time(0);
	return Library(-1, -1, t, this->getPath());
}

string  Library::toSring() {
	char ch[80];
	char buffer[40];
	tm now;
	localtime_s(&now, &this->borrowTime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &now);

	sprintf_s(ch, "student id: %d, book id: %d, time: %s\n",
		this->studentId, this->bookID, buffer);
	return ch;
}




void  Library::printAll() {

	ifstream infile(this->getPath(), ios::in | ios::binary);


	while (infile.peek() != EOF)
	{
		int sId, bId;
		time_t t;

		infile.read(reinterpret_cast<char *>(&sId), sizeof(sId));
		infile.read(reinterpret_cast<char *>(&bId), sizeof(bId));
		infile.read(reinterpret_cast<char *>(&t), sizeof(t));
		cout << Library(sId, bId, t, this->getPath()).toSring();
	
	}
	infile.close();
}
