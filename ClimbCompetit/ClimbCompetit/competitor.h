#ifndef COMPETITOR_H
#define COMPETITOR_H

class competitor
{
public:
	enum categories {
		menOpen = 0, womenOpen = 1, menAmator = 2,
		womenAmator = 3, menJunior = 4, womenJunior = 5,
		default
	};
	categories category;

	competitor();
	competitor(bool setIndex);
	int GetId();
	int GetTop();
	int GetBonus();
	void SetPlace(int newPlace);
	void Save(const char * newName, const char * newLastName,
		int newTop, int newBonus, categories newCategory,
		int newId = 999, int newPlace = 999);
	void SaveToFile(const char * fileName);
	void Show();
	void ReadFromFile(const char * fileName);
	

private:
	int id;
	char name[20];
	char lastName[20];
	int top;
	int bonus;
	int place;

	static int counter;

	const char * CategoryDescription();
};
#endif
