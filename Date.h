#include <string>

#ifndef DATE_H
#define DATE_H


class Date
{
public:
	explicit Date(unsigned int = 1, unsigned int = 1, unsigned int = 2000);
	void SetDay(int Day);
	void SetMonth(int Month);
	void SetYear(int Year);
	int GetDay();
	int GetMonth();
	int GetYear();
	std::string toString() const;
	void nextDay();
private:
	unsigned int month;
	unsigned int day;
	unsigned int year;
};
#endif

