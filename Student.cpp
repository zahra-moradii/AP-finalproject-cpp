#include "stdafx.h"
#include "Student.h"
#include <iostream>

Student::Student(int i, string n, string ln, float g, string p) :File{ p }
{
	this->id = i;
	this->name = n;
	this->lastName = ln;
	this->grade = g;

}

void Student::setID(int i) {
	this->id = i;
}

int Student::getID() {
	return this->id;
}
void Student::setName(string n) {
	this->name = n;
}
string Student::getName() {
	return this->name;
}
void Student::setLastName(string ln) {
	this->lastName = ln;
}
string Student::getLastName() {
	return this->lastName;
}
void Student::setGrade(float g) {
	this->grade = g;
}
float Student::getGrade() {
	return this->grade;
}

void  Student::write(Student s) {

	ofstream myFile(s.getPath(), ios::out | ios::binary | ios::app);

	if (s.getAdaptorType() == _FixRecFixStrAdap)
	{
		char ch[50];

		sprintf_s(ch, "%4d,%2.2f,%10s,%20s\n", s.id, s.grade, s.name.c_str(), s.lastName.c_str());
		myFile.write(ch, strlen(ch));


	}
	else if (s.getAdaptorType() == _FixRecDynStrAdap)
	{
		char ch[50];

		sprintf_s(ch, "%4d,%2.2f,%s,%s\n", s.id, s.grade, s.name.c_str(), s.lastName.c_str());
		myFile.write(ch, strlen(ch));
	}
	else if (s.getAdaptorType() == _DynRecFixStrAdap)
	{
		s.name.resize(10);
		s.lastName.resize(20);
		myFile.write(reinterpret_cast<const char *>(&s.id), sizeof(s.id));
		myFile.write(reinterpret_cast<const char *>(&s.grade), sizeof(s.grade));
		myFile.write(s.name.c_str(), s.name.length());
		myFile.write(s.lastName.c_str(), s.lastName.length());
		myFile.write("\n", 1);
	}
	else if (s.getAdaptorType() == _DynRecDynStrAdap)
	{
		myFile.write(reinterpret_cast<const char *>(&s.id), sizeof(s.id));
		myFile.write(reinterpret_cast<const char *>(&s.grade), sizeof(s.grade));
		myFile.write(s.name.c_str(), s.name.length());
		myFile.write(",", 1);
		myFile.write(s.lastName.c_str(), s.lastName.length());
		myFile.write("\n", 1);
	}

	myFile.close();
}


Student  Student::search(string s, int *row) {


	string line;
	ifstream infile(this->getPath(), ios::in | ios::binary);

	*row = 1;

	if (this->getAdaptorType() == _FixRecFixStrAdap)
	{
		while (infile.peek() != EOF)
		{
			getline(infile, line);
			if (line.find(s) != string::npos) {
				int id;
				float gr;
				string n, ln;

				id = stoi(line.substr(0, 4));
				gr = stof(line.substr(5, 4));
				n = line.substr(11, 10);
				ln = line.substr(22, 20);
				n.erase(std::remove_if(n.begin(), n.end(), ::isspace), n.end());
				ln.erase(std::remove_if(ln.begin(), ln.end(), ::isspace), ln.end());
				return Student(id, n, ln, gr, this->getPath());
			}
			*row += 1;
		}
		return Student(-1, "", "", 0, this->getPath());
	}
	else if (this->getAdaptorType() == _FixRecDynStrAdap)
	{
		while (infile.peek() != EOF)
		{
			getline(infile, line);
			if (line.find(s) != string::npos) {
				int id;
				float gr;
				string n, ln;

				id = stoi(line.substr(0, 4));
				gr = stof(line.substr(5, 4));
				n = line.substr(11, line.find(",", 11) - 11);
				ln = line.substr(line.find(",", 11) + 1);
				n.erase(std::remove_if(n.begin(), n.end(), ::isspace), n.end());
				ln.erase(std::remove_if(ln.begin(), ln.end(), ::isspace), ln.end());
				return Student(id, n, ln, gr, this->getPath());
			}
			*row += 1;
		}
		return Student(-1, "", "", 0, this->getPath());
	}
	else if (this->getAdaptorType() == _DynRecFixStrAdap)
	{
		while (infile.peek() != EOF)
		{
			int id;
			float gr;
			char temp[20];
			string n, ln;

			infile.read(reinterpret_cast<char *>(&id), sizeof(id));
			infile.read(reinterpret_cast<char *>(&gr), sizeof(gr));
			infile.read(temp, 10);
			n = temp;
			infile.read(temp, 20);
			ln = temp;
			infile.read(temp, 1);
			if (n.find(s) != string::npos ||
				ln.find(s) != string::npos ||
				to_string(id).find(s) != string::npos ||
				to_string(gr).find(s) != string::npos) {
				return Student(id, n, ln, gr, this->getPath());
			}
			*row += 1;
		}
		return Student(-1, "", "", 0, this->getPath());
	}
	else if (this->getAdaptorType() == _DynRecDynStrAdap)
	{
		while (infile.peek() != EOF)
		{
			int id;
			float gr;
			char temp[20];
			string n, ln;

			infile.read(reinterpret_cast<char *>(&id), sizeof(id));
			infile.read(reinterpret_cast<char *>(&gr), sizeof(gr));
			getline(infile, line);
			n = line.substr(0, line.find(","));
			ln = line.substr(line.find(",") + 1);

			if (n.find(s) != string::npos ||
				ln.find(s) != string::npos ||
				to_string(id).find(s) != string::npos ||
				to_string(gr).find(s) != string::npos) {
				return Student(id, n, ln, gr, this->getPath());
			}
			*row += 1;
		}
		return Student(-1, "", "", 0, this->getPath());
	}

	infile.close();
}

Student  Student::search(float g, int *row) {
	return this->search(to_string(g), row);
}
Student Student::search(int i, int *row) {
	return this->search(to_string(i), row);
}

string  Student::toSring() {
	char ch[50];
	sprintf_s(ch, "%d, %2.2f, %s, %s\n", this->id, this->grade, this->name.c_str(), this->lastName.c_str());
	return ch;
}


void  Student::printAll() {

	string line;
	ifstream infile(this->getPath(), ios::in | ios::binary);


	if (this->getAdaptorType() == _FixRecFixStrAdap)
	{
		while (infile.peek() != EOF)
		{
			getline(infile, line);
			int id;
			float gr;
			string n, ln;

			id = stoi(line.substr(0, 4));
			gr = stof(line.substr(5, 4));
			n = line.substr(11, 10);
			ln = line.substr(22, 20);
			n.erase(std::remove_if(n.begin(), n.end(), ::isspace), n.end());
			ln.erase(std::remove_if(ln.begin(), ln.end(), ::isspace), ln.end());
			cout << Student(id, n, ln, gr, this->getPath()).toSring();
		}
	}
	else if (this->getAdaptorType() == _FixRecDynStrAdap)
	{
		while (infile.peek() != EOF)
		{
			getline(infile, line);

			int id;
			float gr;
			string n, ln;

			id = stoi(line.substr(0, 4));
			gr = stof(line.substr(5, 4));
			n = line.substr(11, line.find(",", 11) - 11);
			ln = line.substr(line.find(",", 11) + 1);
			n.erase(std::remove_if(n.begin(), n.end(), ::isspace), n.end());
			ln.erase(std::remove_if(ln.begin(), ln.end(), ::isspace), ln.end());
			cout << Student(id, n, ln, gr, this->getPath()).toSring();
		}
	}
	else if (this->getAdaptorType() == _DynRecFixStrAdap)
	{
		while (infile.peek() != EOF)
		{
			int id;
			float gr;
			char temp[20];
			string n, ln;

			infile.read(reinterpret_cast<char *>(&id), sizeof(id));
			infile.read(reinterpret_cast<char *>(&gr), sizeof(gr));
			infile.read(temp, 10);
			n = temp;
			infile.read(temp, 20);
			ln = temp;
			infile.read(temp, 1);
			cout << Student(id, n, ln, gr, this->getPath()).toSring();
		}
	}
	else if (this->getAdaptorType() == _DynRecDynStrAdap)
	{
		while (infile.peek() != EOF)
		{
			int id;
			float gr;
			char temp[20];
			string n, ln;

			infile.read(reinterpret_cast<char *>(&id), sizeof(id));
			infile.read(reinterpret_cast<char *>(&gr), sizeof(gr));
			getline(infile, line);
			n = line.substr(0, line.find(","));
			ln = line.substr(line.find(",") + 1);
			cout << Student(id, n, ln, gr, this->getPath()).toSring();
		}
	}

	infile.close();
}