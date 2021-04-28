#include <sstream>
#include <string>
#include "Date.h"
#include <iostream>

using namespace std;

void Date::SetDay(int Day)
{
	this->day = Day;
}
void Date::SetMonth(int Month)
{
	this->month = Month;
}
void Date::SetYear(int Year)
{
	this->year = Year;
}

int Date::GetDay()
{
	return this->day;
}

int Date::GetMonth()
{
	return this->month;
}

int Date::GetYear()
{
	return this->year;
}

Date::Date(unsigned int m, unsigned int d, unsigned int y) : month{ m }, day{ d }, year{ y }
{
	//Year validation
	if (y < 0)
	{
		this->year = 2021;
	}
	else
	{
		this->year = y;
	}

	//Month validation
	if (m < 1 || m > 12)
	{
		this->month = 1;
	}
	else
	{
		this->month = m;
	}

	//Day validation
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (d < 0 || d > 31)
		{
			this->day = 1;
		}
		else
		{
			this->day = d;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (d < 0 || d > 30)
		{
			this->day = 1;
		}
		else
		{
			this->day = d;
		}
		break;
	case 2:
		bool leapYear;
		if (y % 4 == 0)
		{
			leapYear = true;
		}
		else
		{
			leapYear = false;
		}

		if (d < 0 || ((leapYear) ? d > 29 : d > 28))
		{
			this->day = 1;
		}
		else
		{
			this->day = d;
		}
		break;
	}
}

// print Date in the format mm/dd/yyyy
string Date::toString() const
{
	ostringstream output;
	output << month << '/' << day << '/' << year;
	return output.str();
}

void Date::nextDay()
{
	int d = this->day + 1;
	int m = this->month;
	int y = this->year;
	switch (m)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (d > 31)
		{
			this->day = 1;
			if (m != 12)
			{
				this->month++;
			}
			else
			{
				this->month = 1;
				this->year++;
			}
		}
		else
		{
			this->day = d;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (d > 30)
		{
			this->day = 1;
			this->month++;
		}
		else
		{
			this->day = d;
		}
		break;
	case 2:
		bool leapYear;
		if (y % 4 == 0)
		{
			if (y % 100 == 0)
			{
				if (y % 400 == 0)
				{
					leapYear = true;
				}
				else
				{
					leapYear = false;
				}
			}
			else
			{
				leapYear = true;
			}
		}
		else
		{
			leapYear = false;
		}

		if ((leapYear) ? d > 29 : d > 28)
		{
			this->day = 1;
			this->month++;
		}
		else
		{
			this->day = d;
		}
		break;
	}
}

