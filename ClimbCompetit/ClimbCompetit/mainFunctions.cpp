#include <fstream>
#include <iomanip>
#include <iostream>

#include "competitor.h"
#include "main.h"
#include "result.h"

using namespace std;

char line[] = "[-------------------------------------------------------------------------]\n";
char edges[] = "[                                                                         ]\r[";

result menOpen, womenOpen, menAmator, womenAmator, menJunior, womenJunior;

void Add()
{
	bool setIndex = true;
	competitor newCompetitor(setIndex);
	char name[20];
	char lastName[20];
	int top = 0;
	int bonus = 0;
	int category = 0;

	result *pToResult = 0;

	cout << edges << "Imie: ";
	cin >> name;
	cout << edges << "Nazwisko: ";
	cin >> lastName;
	cout << edges << "Top: ";
	cin >> top;
	cout << edges << "Bonus: ";
	cin >> bonus;
	cout << edges << "Kategoria:\n" <<
		edges << "\t0 - Men Open\n" <<
		edges << "\t1 - Women Open\n" <<
		edges << "\t2 - Men Amator\n" <<
		edges << "\t3 - Women Amator\n" <<
		edges << "\t4 - Men Junior\n" <<
		edges << "\t5 - Women Junior\n" << edges;

	do
	{
		cin >> category;

		switch (category)
		{
		case competitor::categories::menOpen:
			newCompetitor.Save(name, lastName, top, bonus, competitor::categories::menOpen);
			pToResult = &menOpen;
			break;
		case competitor::categories::womenOpen:
			newCompetitor.Save(name, lastName, top, bonus, competitor::categories::womenOpen);
			pToResult = &womenOpen;
			break;
		case competitor::categories::menAmator:
			newCompetitor.Save(name, lastName, top, bonus, competitor::categories::menAmator);
			pToResult = &menAmator;
			break;
		case competitor::categories::womenAmator:
			newCompetitor.Save(name, lastName, top, bonus, competitor::categories::womenAmator);
			pToResult = &womenAmator;
			break;
		case competitor::categories::menJunior:
			newCompetitor.Save(name, lastName, top, bonus, competitor::categories::menJunior);
			pToResult = &menJunior;
			break;
		case competitor::categories::womenJunior:
			newCompetitor.Save(name, lastName, top, bonus, competitor::categories::womenJunior);
			pToResult = &womenAmator;
			break;
		default:
			cout << "Nie ma takiej opcji!\n";
			break;
		}
	} while (!CategoryCheck(category));

	(*pToResult).Add(newCompetitor);
	(*pToResult).Sort();
	(*pToResult).SetPlace();

	CleanScreen();
	Menu();

	cout << edges << "Dodano zawodnika!\n" << line;
	system("Pause");
	Menu();
}

bool CategoryCheck(int category)
{
	bool condition;

	switch (category)
	{
	case competitor::categories::menOpen:
		condition = true;
		break;
	case competitor::categories::womenOpen:
		condition = true;
		break;
	case competitor::categories::menAmator:
		condition = true;
		break;
	case competitor::categories::womenAmator:
		condition = true;
		break;
	case competitor::categories::menJunior:
		condition = true;
		break;
	case competitor::categories::womenJunior:
		condition = true;
		break;
	default:
		condition = false;
		break;
	}
	return condition;
}

void ChooseOption()
{
	enum option { add = 1, remove = 2, show = 3, edit = 4, find = 5, save = 6, open = 7, exit = 8 };
	int myOption;

	do
	{
		myOption = 0;
		cin >> myOption;

		CleanScreen();
		Menu();

		switch (myOption)
		{
		case add:
			Add();
			break;
		case remove:
			Remove();
			break;
		case show:
			Show();
			break;
		case edit:
			Edit();
			break;
		case find:
			Find();
			break;
		case save:
			Save();
			break;
		case open:
			Open();
			break;
		case exit:
			break;
		default:
			cout << "Nie ma takiej opcji!\n";
			break;
		}
	} while (myOption != exit);
}

void CleanScreen()
{
	system("cls");
}

//empty
void Edit()
{
	cout << "Wkrotce\n";
	system("Pause");
	Menu();
}

//empty
void Find()
{
	cout << "Wkrotce\n";
	system("Pause");
	Menu();
}

void Menu()
{
	CleanScreen();

	cout << line <<
		edges << "Climb Comp\n" << line <<
		edges << "1 - Dodaj zawodnika\n" <<
		edges << "2 - Usun zawodnika\n" <<
		edges << "3 - Wyswietl wyniki\n" <<
		edges << "4 - Edytuj zawodnika\n" <<
		edges << "5 - Znajdz zawodnika\n" <<
		edges << "6 - Zapisz\n" <<
		edges << "7 - Otworz\n" <<
		edges << "8 - Wyjscie\n" << line;
}

void Open()
{
	char fileName[20] = "";

	cout << edges << "Wprowadz nazwe pliku: ";
	cin >> fileName;

	strcat_s(fileName, ".txt");

	fstream file;
	file.open(fileName, ios::in);

	if (file.good() == true)
	{
		file.close();

		menOpen.Read(fileName, competitor::categories::menOpen);
		womenOpen.Read(fileName, competitor::categories::womenOpen);
		menAmator.Read(fileName, competitor::categories::menAmator);
		womenAmator.Read(fileName, competitor::categories::womenAmator);
		menJunior.Read(fileName, competitor::categories::menJunior);
		womenJunior.Read(fileName, competitor::categories::womenJunior);

		cout << edges << "Plik " << fileName << " zostal wczytany!\n";
	}
	else
		cout << edges << "Plik " << fileName << " nie istnieje!\n";

	cout << line;
	system("Pause");
	Menu();
}

void Remove()
{
	int id;

	cout << edges << "Id: ";
	cin >> id;
	cout << line << edges;

	result *pToResult = 0;

	//number of enum
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case competitor::categories::menOpen:
			pToResult = &menOpen;
			break;
		case competitor::categories::womenOpen:
			pToResult = &womenOpen;
			break;
		case competitor::categories::menAmator:
			pToResult = &menAmator;
			break;
		case competitor::categories::womenAmator:
			pToResult = &womenAmator;
			break;
		case competitor::categories::menJunior:
			pToResult = &menJunior;
			break;
		case competitor::categories::womenJunior:
			pToResult = &womenJunior;
			break;
		default:
			break;
		}

		if ((*pToResult).InList(id))
		{
			(*pToResult).Show(id);
			cout << line;

			(*pToResult).Remove(id);
			break;
		}
	}

	(*pToResult).Sort();
	(*pToResult).SetPlace();

	system("Pause");
	Menu();
}

void Save()
{
	char fileName[20] = "";

	cout << edges << "Wprowadz nazwe pliku: ";
	cin >> fileName;

	strcat_s(fileName, ".txt");

	fstream file;
	file.open(fileName, ios::out | ios::trunc);

	if (file.good() == true)
	{
		file.close();

		menOpen.Save(fileName);
		womenOpen.Save(fileName);
		menAmator.Save(fileName);
		womenAmator.Save(fileName);
		menJunior.Save(fileName);
		womenJunior.Save(fileName);

		cout << edges << "Wyniki zapisano w pliku " << fileName << "\n";
	}
	else
		cout << edges << "Plik " << fileName << " nie zosta³ zapisany!\n";

	cout << line;
	system("Pause");
	Menu();
}

void Show()
{
	int category;
	bool condition = false;

	do
	{
		Menu();
		cout << edges << "Kategoria:\n" <<
			edges << "\t0 - Men Open\n" <<
			edges << "\t1 - Women Open\n" <<
			edges << "\t2 - Men Amator\n" <<
			edges << "\t3 - Women Amator\n" <<
			edges << "\t4 - Men Junior\n" <<
			edges << "\t5 - Women Junior\n" << edges;

		cin >> category;

		CleanScreen();
		Menu();

		cout << edges <<
			setw(5) << "Id:" <<
			setw(10) << "Miejsce:" <<
			setw(10) << "Imie:" <<
			setw(15) << "Nazwisko:" <<
			setw(6) << "Top:" <<
			setw(8) << "Bonus:" <<
			setw(15) << "Kategoria:\n";

		switch (category)
		{
		case competitor::categories::menOpen:
			menOpen.Show();
			break;
		case competitor::categories::womenOpen:
			womenOpen.Show();
			break;
		case competitor::categories::menAmator:
			menAmator.Show();
			break;
		case competitor::categories::womenAmator:
			womenAmator.Show();
			break;
		case competitor::categories::menJunior:
			menJunior.Show();
			break;
		case competitor::categories::womenJunior:
			womenJunior.Show();
			break;
		default:
			cout << "Nie ma takiej opcji!\n";
			system("Pause");
			CleanScreen();
			break;
		}
	} while (!CategoryCheck(category));

	cout << line;
	system("Pause");
	Menu();
}