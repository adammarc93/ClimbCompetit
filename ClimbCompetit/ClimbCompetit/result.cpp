#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

#include "result.h"

using namespace std;

result::result()
{
	size = 0;
	results = new competitor[size];
}

void result::Add(competitor &newCompetitor)
{
	size++;
	competitor *buf = new competitor[size];

	for (int i = 0; i < size; i++)
		buf[i] = results[i];

	delete results;

	results = new competitor[size];

	for (int i = 0; i < size; i++)
	{
		results[i] = buf[i];

		if (i == size - 1)
			results[i] = newCompetitor;
	}

	delete buf;
}

void result::ClearArray()
{
	delete results;
	size = 0;
	results = new competitor[size];
}

void result::ClearCString(char * cstring)
{
	int lenght = strlen(cstring);

	for (int i = 0; i < lenght; i++)
		cstring[i] = '\0';
}

competitor::categories result::CStringToEnum(const char * cstring)
{
	const char * names[] = {
		"MenOpen",
		"WomenOpen",
		"MenAmator",
		"WomenAmator",
		"MenJunior",
		"WomenJunior" };

	int which = 0;

	for (int i = 0; i < 6; i++)
	{
		if (strcmp(cstring, names[i]) == 0)
		{
			which = i;
			break;
		}
	}

	switch (which)
	{
	case competitor::categories::menOpen:
		return competitor::categories::menOpen;
		break;
	case competitor::categories::womenOpen:
		return competitor::categories::womenOpen;
		break;
	case competitor::categories::menAmator:
		return competitor::categories::menAmator;
		break;
	case competitor::categories::womenAmator:
		return competitor::categories::womenAmator;
		break;
	case competitor::categories::menJunior:
		return competitor::categories::menJunior;
		break;
	case competitor::categories::womenJunior:
		return competitor::categories::womenJunior;
		break;
	default:
		break;
	}
}

int result::CStringToInt(char * cstring)
{
	int lenght = strlen(cstring);
	int result = 0;

	for (int i = 0; i < lenght; i++)
	{
		int number = 0;
		number = cstring[i] - '0';
		number *= pow(10, lenght - (i + 1));
		result += number;
	}

	return result;
}

//empty
void result::Edit()
{
}

bool result::InList(int id)
{
	int competitorId = 0;

	for (int i = 0; i < size; i++)
	{
		competitorId = results[i].GetId();

		if (id == competitorId)
			return true;
	}
	return false;
}

void result::Remove(int id)
{
	int competitorId = 0;

	for (int i = 0; i < size; i++)
	{
		competitorId = results[i].GetId();

		if (id == competitorId)
			break;
	}

	competitor *buf = new competitor[size];

	for (int i = 0; i < size; i++)
		buf[i] = results[i];

	delete results;

	size--;

	results = new competitor[size];

	bool condition = false;

	for (int i = 0; i < size; i++)
	{
		if (id == buf[i].GetId())
			condition = true;

		if (!condition)
			results[i] = buf[i];
		else
			results[i] = buf[i + 1];
	}
	delete buf;
}

void result::Save(const char * fileName)
{
	for (int i = 0; i < size; i++)
		results[i].SaveToFile(fileName);
}

void result::Read(const char * fileName, competitor::categories category)
{
	ClearArray();

	fstream file;
	file.open(fileName, ios::in);

	if (file.good() == true)
	{
		const int max = 20;
		char phrase[max] = "";

		enum what {
			Id = 0, Place = 1, Name = 2, LastName = 3,
			Top = 4, Bonus = 5, Category = 6
		};
		int which = 0;

		int id = 0;
		int place = 0;
		char name[max] = "";
		char lastName[max] = "";
		int top = 0;
		int bonus = 0;
		competitor::categories readCateory;

		ClearCString(phrase);
		ClearCString(name);
		ClearCString(lastName);

		int i = 0;
		while (!file.eof())
		{
			file >> phrase[i];

			if (phrase[i] != ',')
			{
				i++;
			}
			else
			{
				phrase[i] = NULL;

				switch (which % 7)
				{
				case what::Id:
					id = CStringToInt(phrase);
					break;
				case what::Place:
					place = CStringToInt(phrase);
					break;
				case what::Name:
					strcpy_s(name, phrase);
					break;
				case what::LastName:
					strcpy_s(lastName, phrase);
					break;
				case what::Top:
					top = CStringToInt(phrase);
					break;
				case what::Bonus:
					bonus = CStringToInt(phrase);
					break;
				case what::Category:
					readCateory = CStringToEnum(phrase);
					break;
				default:
					break;
				}

				if (readCateory == category)
				{
					bool index = true;

					competitor newCompetitor(index);
					newCompetitor.Save(name, lastName, top, bonus, readCateory, id, place);

					Add(newCompetitor);

					id = 0;
					place = 0;
					top = 0;
					bonus = 0;
					ClearCString(name);
					ClearCString(lastName);
					readCateory = competitor::categories::default;
				}

				i = 0;
				which++;
				ClearCString(phrase);
			}
		}
		file.close();
	}
}

void result::SetPlace()
{
	int lastPlace = 1;

	for (int i = 0; i < size; i++)
	{
		if (i == 0)
		{
			results[i].SetPlace(lastPlace);
		}
		else
		{
			if (results[i].GetTop() == results[i - 1].GetTop() &&
				results[i].GetBonus() == results[i - 1].GetBonus())
			{
				results[i].SetPlace(lastPlace);
			}
			else
			{
				lastPlace = i + 1;
				results[i].SetPlace(lastPlace);
			}
		}
	}
}

void result::Show()
{
	for (int i = 0; i < size; i++)
		results[i].Show();
}

void result::Show(int id)
{
	for (int i = 0; i < size; i++)
		if (id == results[i].GetId())
		{
			results[i].Show();
			break;
		}
}

void result::Sort()
{
	for (int i = 0; i < size; i++)
		for (int j = 1; j < size - i; j++)
		{
			if (results[j - 1].GetTop() < results[j].GetTop())
			{
				competitor bufTop = results[j];
				results[j] = results[j - 1];
				results[j - 1] = bufTop;
			}
			if (results[j - 1].GetTop() == results[j].GetTop())
			{
				if (results[j - 1].GetBonus() < results[j].GetBonus())
				{
					competitor bufBonus = results[j];
					results[j] = results[j - 1];
					results[j - 1] = bufBonus;
				}
			}
		}
}