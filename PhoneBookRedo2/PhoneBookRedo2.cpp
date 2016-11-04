// PhoneBookRedo2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;



class entry
{
	char name[20];
	char homePhone[14];
	char mobilePhone[14];
public:
	entry();
	void setEntry(char n[], char home[], char cell[]);
	void display();
	friend class phoneBook;

};



entry::entry()
{
	strcpy_s(name, "");
	strcpy_s(homePhone, "");
	strcpy_s(mobilePhone, "");
}



void entry::setEntry(char n[], char home[], char cell[])
{
	strcpy_s(name, n);
	strcpy_s(homePhone, home);
	strcpy_s(mobilePhone, cell);
}

void entry::display()
{
	printf(" name: %s\n home phone: %s\n mobile phone: %s\n\n",
		name, homePhone, mobilePhone);
}

class phoneBook
{
	char filename[100];
	int entryCount;
	entry **mylist;
public:
	phoneBook();
	~phoneBook();
	void setFilename(char f[]);
	int getCount();
	void addToList(entry *b);
	void showList();
	int saveList();
	void readList();
};

phoneBook::phoneBook()
{
	mylist = new entry*[100];
	entryCount = 0;
}

phoneBook::~phoneBook()
{
	delete mylist;
}

void phoneBook::setFilename(char f[])
{
	strcpy_s(filename, f);
}

void phoneBook::addToList(entry *b)
{
	mylist[entryCount] = b;
	entryCount++;;
}

int phoneBook::getCount()
{
	return entryCount;
}

void phoneBook::showList()
{
	for (int i = 0; i < entryCount; i++)
	{
		mylist[i]->display();
	}
}

int phoneBook::saveList()
{
	ofstream output(filename);
	if (!output)
	{
		cout << "Fail!! " << endl;
		return -1;
	}
	for (int i = 0; i < entryCount; i++)
	{
		output << mylist[i]->name << ",";
		output << mylist[i]->homePhone << ",";
		output << mylist[i]->mobilePhone << ",";
	}
	output.close();
	return 0;
}


void phoneBook::readList()
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		entry *ptr;
		char name[50];
		char homePhone[14];
		char mobilePhone[14];

		infile.getline(name, 50, ',');
		if (strlen(name))
		{
			infile.getline(homePhone, 14, ',');
			infile.getline(mobilePhone, 14, ',');
			ptr = new entry();
			ptr->setEntry(name, homePhone, mobilePhone);
			addToList(ptr);
		}
	}
	infile.close();
}


int main()
{
	int answer = 0;
	char homePhone[50];
	char name[14];
	char mobilePhone[14];
	double rating;
	double alcohol;
	char filename[50];

	// create a new beerlist object
	phoneBook *booklist = new phoneBook();

	// now get and set filename
	cout << "please enter full path filename" << endl;
	gets_s(filename);
	booklist->setFilename(filename);

	// Read in any existing file
	booklist->readList();
	if (booklist->getCount() == 0)
	{
		cout << "your list is empty!  Start recording!! " << endl;
	}
	else
	{
		cout << "You have " << booklist->getCount() << " in your list." << endl;
	}



	do
	{
		cout << "Would you like to add another entry? enter 1 to add, 2 to display, or 9 to quit" << endl;
		cin >> answer;
		cin.clear();
		cin.ignore();

		if (answer == 1)
		{
			cout << "enter name" << endl;
			gets_s(name);
			cout << "enter home phone" << endl;
			gets_s(homePhone);
			cout << "enter mobile phone" << endl;
			gets_s(mobilePhone);


			entry *myEntry = new entry();
			myEntry->setEntry(name, homePhone, mobilePhone);
			booklist->addToList(myEntry);

		}
		else if (answer == 2)
		{
			booklist->showList();
		}
		else if (answer == 9)
		{
			cout << "Closing program, here is your phonebook: " << endl;
		}
		else
		{
			cout << "error. invalid entry, please try again." << endl;
		}
	} while (answer != 9);


	// show list 
	booklist->showList();
	booklist->saveList();

	return 0;
}
