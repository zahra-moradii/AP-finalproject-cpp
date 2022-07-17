#include "stdafx.h"
#include "Book.h"
#include <iostream>
#include "Student.h"


Book::Book(int i, string n, string wn, int ed, string p) :File{ p }
{
	this->id = i;
	this->name = n;
	this->writerName = wn;
	this->edition = ed;

}

void Book::setID(int i) {
	this->id = i;
}

int Book::getID() {
	return this->id;
}
void Book::setName(string n) {
	this->name = n;
}
string Book::getName() {
	return this->name;
}
void Book::setWriterName(string ln) {
	this->writerName = ln;
}
string Book::getWriterName() {
	return this->writerName;
}
void Book::setEdition(int ed) {
	this->edition = ed;
}
int Book::getEdition() {
	return this->edition;
}

void  Book::write(Book b) {

	ofstream myFile(b.getPath(), ios::out | ios::binary | ios::app);

	if (b.getAdaptorType() == _FixRecFixStrAdap)
	{
		char ch[50];

		sprintf_s(ch, "%4d,%4d,%10s,%20s\n", b.id, b.edition, b.name.c_str(), b.writerName.c_str());
		myFile.write(ch, strlen(ch));

	}
	else if (b.getAdaptorType() == _FixRecDynStrAdap)
	{
		char ch[50];

		sprintf_s(ch, "%4d,%4d,%s,%s\n", b.id, b.edition, b.name.c_str(), b.writerName.c_str());
		myFile.write(ch, strlen(ch));
	}
	else if (b.getAdaptorType() == _DynRecFixStrAdap)
	{
		b.name.resize(10);
		b.writerName.resize(20);
		myFile.write(reinterpret_cast<const char *>(&b.id), sizeof(b.id));
		myFile.write(reinterpret_cast<const char *>(&b.edition), sizeof(b.edition));
		myFile.write(b.name.c_str(), b.name.length());
		myFile.write(b.writerName.c_str(), b.writerName.length());
		myFile.write("\n", 1);
	}
	else if (b.getAdaptorType() == _DynRecDynStrAdap)
	{
		myFile.write(reinterpret_cast<const char *>(&b.id), sizeof(b.id));
		myFile.write(reinterpret_cast<const char *>(&b.edition), sizeof(b.edition));
		myFile.write(b.name.c_str(), b.name.length());
		myFile.write(",", 1);
		myFile.write(b.writerName.c_str(), b.writerName.length());
		myFile.write("\n", 1);
	}

	myFile.close();
}


Book  Book::search(string s, int *row) {


	string line;
	ifstream infile(this->getPath(), ios::in | ios::binary);

	*row = 1;

	if (this->getAdaptorType() == _FixRecFixStrAdap)
	{
		while (infile.peek() != EOF)
		{
			getline(infile, line);
			if (line.find(s) != string::npos) {
				int id, ed;
				string n, wn;

				id = stoi(line.substr(0, 4));
				ed = stof(line.substr(5, 4));
				n = line.substr(11, 10);
				wn = line.substr(22, 20);
				n.erase(std::remove_if(n.begin(), n.end(), ::isspace), n.end());
				wn.erase(std::remove_if(wn.begin(), wn.end(), ::isspace), wn.end());
				return Book(id, n, wn, ed, this->getPath());
			}
			*row += 1;
		}
		return Book(-1, "", "", 0, this->getPath());
	}
	else if (this->getAdaptorType() == _FixRecDynStrAdap)
	{
		while (infile.peek() != EOF)
		{
			getline(infile, line);
			if (line.find(s) != string::npos) {
				int id, ed;
				string n, wn;

				id = stoi(line.substr(0, 4));
				ed = stof(line.substr(5, 4));
				n = line.substr(11, line.find(",", 11) - 11);
				wn = line.substr(line.find(",", 11) + 1);
				n.erase(std::remove_if(n.begin(), n.end(), ::isspace), n.end());
				wn.erase(std::remove_if(wn.begin(), wn.end(), ::isspace), wn.end());
				return Book(id, n, wn, ed, this->getPath());
			}
			*row += 1;
		}
		return Book(-1, "", "", 0, this->getPath());
	}
	else if (this->getAdaptorType() == _DynRecFixStrAdap)
	{
		while (infile.peek() != EOF)
		{
			int id, ed;
			char temp[20];
			string n, wn;

			infile.read(reinterpret_cast<char *>(&id), sizeof(id));
			infile.read(reinterpret_cast<char *>(&ed), sizeof(ed));
			infile.read(temp, 10);
			n = temp;
			infile.read(temp, 20);
			wn = temp;
			infile.read(temp, 1);
			if (n.find(s) != string::npos ||
				wn.find(s) != string::npos ||
				to_string(id).find(s) != string::npos ||
				to_string(ed).find(s) != string::npos) {
				return Book(id, n, wn, ed, this->getPath());
			}
			*row += 1;
		}
		return Book(-1, "", "", 0, this->getPath());
	}
	else if (this->getAdaptorType() == _DynRecDynStrAdap)
	{
		while (infile.peek() != EOF)
		{
			int id, ed;
			char temp[20];
			string n, wn;

			infile.read(reinterpret_cast<char *>(&id), sizeof(id));
			infile.read(reinterpret_cast<char *>(&ed), sizeof(ed));
			getline(infile, line);
			n = line.substr(0, line.find(","));
			wn = line.substr(line.find(",") + 1);

			if (n.find(s) != string::npos ||
				wn.find(s) != string::npos ||
				to_string(id).find(s) != string::npos ||
				to_string(ed).find(s) != string::npos) {
				return Book(id, n, wn, ed, this->getPath());
			}
			*row += 1;
		}
		return Book(-1, "", "", 0, this->getPath());
	}

	infile.close();
}

Book Book::search(int i, int *row) {
	return this->search(to_string(i), row);
}

string  Book::toSring() {
	char ch[50];
	sprintf_s(ch, "%d, %d, %s, %s\n", this->id, this->edition, this->name.c_str(), this->writerName.c_str());
	return ch;
}

void  Book::printAll() {

	string line;
	ifstream infile(this->getPath(), ios::in | ios::binary);

	if (this->getAdaptorType() == _FixRecFixStrAdap)
	{
		while (infile.peek() != EOF)
		{
			getline(infile, line);

			int id, ed;
			string n, wn;

			id = stoi(line.substr(0, 4));
			ed = stof(line.substr(5, 4));
			n = line.substr(11, 10);
			wn = line.substr(22, 20);
			n.erase(std::remove_if(n.begin(), n.end(), ::isspace), n.end());
			wn.erase(std::remove_if(wn.begin(), wn.end(), ::isspace), wn.end());
			cout << Book(id, n, wn, ed, this->getPath()).toSring();
		}
	}
	else if (this->getAdaptorType() == _FixRecDynStrAdap)
	{
		while (infile.peek() != EOF)
		{
			getline(infile, line);
			int id, ed;
			string n, wn;
			id = stoi(line.substr(0, 4));
			ed = stof(line.substr(5, 4));
			n = line.substr(11, line.find(",", 11) - 11);
			wn = line.substr(line.find(",", 11) + 1);
			n.erase(std::remove_if(n.begin(), n.end(), ::isspace), n.end());
			wn.erase(std::remove_if(wn.begin(), wn.end(), ::isspace), wn.end());
			cout << Book(id, n, wn, ed, this->getPath()).toSring();
		}
	}
	else if (this->getAdaptorType() == _DynRecFixStrAdap)
	{
		while (infile.peek() != EOF)
		{
			int id, ed;
			char temp[20];
			string n, wn;

			infile.read(reinterpret_cast<char *>(&id), sizeof(id));
			infile.read(reinterpret_cast<char *>(&ed), sizeof(ed));
			infile.read(temp, 10);
			n = temp;
			infile.read(temp, 20);
			wn = temp;
			infile.read(temp, 1);
			cout << Book(id, n, wn, ed, this->getPath()).toSring();
		}
	}
	else if (this->getAdaptorType() == _DynRecDynStrAdap)
	{
		while (infile.peek() != EOF)
		{
			int id, ed;
			char temp[20];
			string n, wn;

			infile.read(reinterpret_cast<char *>(&id), sizeof(id));
			infile.read(reinterpret_cast<char *>(&ed), sizeof(ed));
			getline(infile, line);
			n = line.substr(0, line.find(","));
			wn = line.substr(line.find(",") + 1);
			cout << Book(id, n, wn, ed, this->getPath()).toSring();
		}
	}
	infile.close();
}
