#ifndef RESULT_H
#define RESULT_H

#include "competitor.h"

class result
{
public:
	result();
	void Add(competitor &newCompetitor);
	void Edit();
	bool InList(int id);
	void Read(const char * fileName, competitor::categories category);
	void Remove(int id);
	void Save(const char * fileName);
	void SetPlace();
	void Show();
	void Show(int id);
	void Sort();



private:
	int size;
	competitor *results;

	void ClearArray();
	int CStringToInt(char * cstring);
	competitor::categories CStringToEnum(const char * cstring);
	void ClearCString(char * cstring);
};
#endif