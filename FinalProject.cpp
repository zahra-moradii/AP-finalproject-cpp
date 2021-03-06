// FinalProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#define studentPath "student.bin"
#define bookPath "book.bin"
#define libPath "library.bin"


int Adaptor::adaptorType = _FixRecFixStrAdap;

int main()
{
	int state = 0, in;
	File F(bookPath);
	//F.rest(_FixRecFixStrAdap);


	while (true) {
		if (state == 0)
		{
			state = -1;
			system("cls");
			cout << "---------- LIBRARY ----------\n";
			cout << "press number of your funcation\n";
			cout << "1- add student\n";
			cout << "2- search student\n";
			cout << "3- edit student\n";
			cout << "4- add book\n";
			cout << "5- search book\n";
			cout << "6- edit book\n";
			cout << "7- borrowing book\n";
			cout << "8- search borrowing book record\n";
			cout << "9- print all student\n";
			cout << "10- print all book\n";
			cout << "11- print all borrowing record\n";
			

			cin >> in;
			switch (in)
			{
			case 1:
				state = 1;
				break;
			case 2:
				state = 2;
				break;
			case 3:
				state = 3;
				break;
			case 4:
				state = 4;
				break;
			case 5:
				state = 5;
				break;
			case 6:
				state = 6;
				break;
			case 7:
				state = 7;
				break;
			case 8:
				state = 8;
				break;
			case 9:
				state = 9;
				break;
			case 10:
				state = 10;
				break;
			case 11:
				state = 11;
				break;

			default:
				state == 0;
				break;
			}
		}
		else if (state == 1)
		{
			state = 0;
			system("cls");
			cout << "---------- add student ----------\n";
			int id; 
			string n, ln;
			float g; 
			cout << "Enter id: ";
			cin >>  id; 
			cout << "Enter Name: ";
			cin >> n;
			cout << "Enter Last Name: ";
			cin >> ln;
			cout << "Enter grade: ";
			cin >>  g; 

			Student s(id,n,ln,g, studentPath);
			s.write(s);
		}
		else if (state == 2)
		{
			state = 0;
			system("cls");
			cout << "---------- search student ----------\n";
			string str;
			Student s(0, " ", " ", 0, studentPath);
			cout << "Enter id or name or last name or grade: ";
			cin >> str;
			int tempRow;
			s = s.search(str, &tempRow);
			if (s.getID() != -1)
				cout << s.toSring();
			else
				cout << "can't finde this student\n";

			cout << "press any key to return to menu";
			_getch();

		}
		else if (state == 3)
		{
			state = 0;
			system("cls");
			cout << "---------- edite student ----------\n";
			string str;
			Student s(0, " ", " ", 0, studentPath);
			cout << "Enter id or name or last name or grade of student you want edit: ";
			cin >> str;
			int tempRow; 
			s = s.search(str,&tempRow);
			if (s.getID() != -1)
				cout <<"edit this student: "<< s.toSring();
			else
				cout << "can't finde this student\n";
			s.deleteLine(studentPath, tempRow);

			int id;
			string n, ln;
			float g;
			cout << "Enter new id: ";
			cin >> id;
			cout << "Enter new Name: ";
			cin >> n;
			cout << "Enter new Last Name: ";
			cin >> ln;
			cout << "Enter new grade: ";
			cin >> g;

			s.setID(id);
			s.setName(n);
			s.setLastName(ln);
			s.setGrade(g);

			s.write(s);

			cout << "edited student: " << s.toSring() << endl;
			cout << "press any key to return to menu";
			_getch();

		}
		else if (state == 4)
		{
			state = 0;
			system("cls");
			cout << "---------- add book ----------\n";
			int id,ed;
			string n, wn;
			cout << "Enter book id: ";
			cin >> id;
			cout << "Enter book Name: ";
			cin >> n;
			cout << "Enter writer Name: ";
			cin >> wn;
			cout << "Enter edition: ";
			cin >> ed;
			Book b(id, n, wn, ed, bookPath);
			b.write(b);

		}
		else if (state == 5)
		{
			state = 0;
			system("cls");
			cout << "---------- search book ----------\n";
			string str;
			Book b(0, " ", " ", 0, bookPath);
			cout << "Enter id or name or last name or grade: ";
			//cout << "Enter id or name or writername or edition :";
			cin >> str;
			int tempRow;
			b = b.search(str, &tempRow);
			if (b.getID() != -1)
				cout << b.toSring();
			else
				cout << "can't finde this book\n";

			cout << "press any key to return to menu";
			_getch();

		}
		else if (state == 6)
		{
			state = 0;
			system("cls");
			cout << "---------- edit book ----------\n";
			string str;
			Book b(0, " ", " ", 0, bookPath);
			cout << "Enter id or name or writer name or edition of book you want edit: ";
			cin >> str;
			int tempRow;
			b = b.search(str, &tempRow);
			if (b.getID() != -1)
				cout << "edit this book: " << b.toSring();
			else
				cout << "can't finde this book\n";
			b.deleteLine(bookPath, tempRow);

			int id,ed;
			string n, wn;
			
			cout << "Enter new id: ";
			cin >> id;
			cout << "Enter new Name: ";
			cin >> n;
			cout << "Enter new writer Name: ";
			cin >> wn;
			cout << "Enter new edition: ";
			cin >> ed;

			b.setID(id);
			b.setName(n);
			b.setWriterName(wn);
			b.setEdition(ed);

			b.write(b);

			cout << "edited book: " << b.toSring() << endl;
			cout << "press any key to return to menu";
			_getch();

		}
		else if (state == 7)
		{
			state = 0;
			system("cls");
			cout << "---------- borrowing book ----------\n";
			int sId,bId;
			time_t t = time(0);

			cout << "Enter student id: ";
			cin >> sId;
			cout << "Enter book Id: ";
			cin >> bId;

			Library lib(sId, bId,t , libPath);
			lib.write(lib);
		}
		else if (state == 8)
		{
			state = 0;
			system("cls");
			cout << "---------- search borrowing book record ----------\n";
			string str;
			Library lib(-1, -1, time(0), libPath);
			cout << "Enter student or book id ";
			cin >> str;
			int tempRow;
			lib = lib.search(str, &tempRow);
			if (lib.getStudentID() != -1)
				cout << lib.toSring();
			else
				cout << "can't finde this record\n";

			cout << "press any key to return to menu";
			_getch();

		}
		else if (state == 9)
		{
			state = 0;
			system("cls");
			cout << "---------- print all students ----------\n";
			Student s(0, " ", " ", 0, studentPath);
			s.printAll();
			cout << "press any key to return to menu";
			_getch();
		}
		else if (state == 10)
		{
			state = 0;
			system("cls");
			cout << "---------- print all book ----------\n";
			Book b(0, " ", " ", 0, bookPath);
			b.printAll();
			cout << "press any key to return to menu";
			_getch();
		}
		else if (state == 11)
		{
			state = 0;
			system("cls");
			cout << "---------- print all borrowing record ----------\n";
			Library lib(-1, -1, time(0), libPath);
			lib.printAll();
			cout << "press any key to return to menu";
			_getch();
		}
	}
	return 0;
}

