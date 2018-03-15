#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "competitor.h"

using namespace std;

int competitor::counter = 0;

competitor::competitor()
{
}

competitor::competitor(bool setIndex)
{
	if (setIndex)
	{
		id = counter;
		counter++;
	}
}

const char * competitor::CategoryDescription()
{
	const char * names[] = {
		"Men Open",
		"Women Open",
		"Men Amator",
		"Women Amator",
		"Men Junior",
		"Women Junior" };

	return names[category];
}

int competitor::GetId()
{
	return id;
}

int competitor::GetTop()
{
	return top;
}

int competitor::GetBonus()
{
	return bonus;
}

void competitor::SetPlace(int newPlace)
{
	place = newPlace;
}

void competitor::Save(const char * newName, const char * newLastName,
	int newTop, int newBonus, categories newCategory,
	int newId, int newPlace)
{
	strcpy_s(name, (newName ? newName : "Anonim"));
	strcpy_s(lastName, (newLastName ? newLastName : "Anonim"));
	top = newTop;
	bonus = newBonus;
	category = newCategory;

	//999 - default Id and Place
	if (newId != 999)
		id = newId;

	if (newPlace != 999)
		place = newPlace;
}

void competitor::SaveToFile(const char * fileName)
{
	fstream file;
	file.open(fileName, ios::out | ios::app);

	if (file.good() == true)
	{
		file << id << "," << place << "," << name << "," << lastName << ","
			<< top << "," << bonus << "," << CategoryDescription() << ",\n";

		file.close();
	}
}

void competitor::Show()
{
	cout << setw(5) << id <<
		setw(10) << place <<
		setw(10) << name <<
		setw(15) << lastName <<
		setw(6) << top <<
		setw(8) << bonus <<
		setw(15) << CategoryDescription() << "\n";
}