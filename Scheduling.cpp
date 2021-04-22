#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Reservation.h"
#include "Scheduling.h"
using namespace std;

/*To  any  destination,  the  company  intends  to  operate  at  least  3  services   a  week
to  and  from  any  destination. However, depending on the demand, the company can operate extra
service providing that there is a bus available.
The demand should meet at least 50% of particular bus type.
When you schedule  one  bus  for  a  particular  destination,  make  sure  you  have  an  available
bus  at  that  depot.  You  have  11  buses  and  6  destinations.  Therefore,  depending  on  the  passengers¡¯  reservation,
there  must be one bus available to complete the travel.
You may consider keeping an inventory of vehicles located in different depots. */

/*
Source		Destination		Distance
Green Bay	Madison			135.6 miles
Green Bay	Milwaukee		118.7 miles
Green Bay	Whitewater		142.2 miles
Green Bay	Oshkosh			50.4 miles
Green Bay	Eau Claire		194.4 miles
*/

/*
Scheduling
-------------
Demand
activeBus line
-------------
weekCheck        - To  any  destination,  the  company  intends  to  operate  at  least  3  services   a  week to  and  from  any  destination.
MinimumCheck     - The demand should meet at least 50% of particular bus type.
DemandCheck      - depending on the demand, the company can operate extra service providing that there is a bus available.
reservationCheck - Therefore,  depending  on  the  passengers¡¯  reservation, there  must be one bus available to complete the travel.
busListCheck     - You may consider keeping an inventory of vehicles located in different depots.
*/

// Constructor
Scheduling::Scheduling()
{
	activeTotalBus = 0;
	activeLuxuryBus = 0;
	activeMiniBus = 0;
	activeMiniVan = 0;

	for (int i = 0; i < 54; i++)
	{
		activeServiceWeekend[i] = 0;
	}
}

Scheduling::Scheduling(int activeLuxuryBusInput, int activeMiniBusInput,
	int activeMiniVanInput, int activeTotalBusInput)
{
	activeTotalBus = activeTotalBusInput;
	activeLuxuryBus = activeLuxuryBusInput;
	activeMiniBus = activeMiniBusInput;
	activeMiniVan = activeMiniVanInput;

	for (int i = 0; i < 54; i++)
	{
		activeServiceWeekend[i] = 0;
	}
}

int Scheduling::getActiveLuxuryBus()
{
	return activeLuxuryBus;
}

int Scheduling::getActiveMiniBus()
{
	return activeMiniBus;
}

int Scheduling::getActiveMiniVan()
{
	return activeMiniVan;
}

int luxuryBusTotal = 3;
int miniBusTotal = 4;
int miniVanTotal = 4;
int totalBuses = 0;

//mutator methods to add new vehicles of each type
int Scheduling::addLuxuryBus() {
	luxuryBusTotal += 1;
	return luxuryBusTotal;
}

int Scheduling::addMiniBus() {
	miniBusTotal += 1;
	return miniBusTotal;
}

int Scheduling::addMiniVan() {
	miniVanTotal += 1;
	return miniVanTotal;
}

//getters to return the amount of each vehicle type
int Scheduling::getLuxuryBusTotal() {
	return luxuryBusTotal;
}

int Scheduling::getMiniBusTotal() {
	return miniBusTotal;
}

int Scheduling::getMiniVanTotal() {
	return miniVanTotal;
}

int Scheduling::weekNumberCheck(Reservation Reservation)
{
	// Calculate weekend
	char timebuf[80];
	tm weekNumber;
	memset(&weekNumber, 0, sizeof weekNumber);

	weekNumber = Reservation.GetWeekNum();
	mktime(&weekNumber);

	if (strftime(timebuf, sizeof timebuf, "%W", &weekNumber) != 0) {
		printf("Week number is: %s\n", timebuf);
	}

	// Change Char to integer.
	stringstream str;
	str << timebuf;
	int x;
	str >> x;

	return x;
}

// To  any  destination,  the  company  intends  to  operate  at  least  3  services   a  week
void Scheduling::weekCheck(Reservation Reservation)
{
	// If reservation date is 04/20/2021 then 20 weekend
	// Also activeServiceWeekend[20] values < 3 then No schedule
	if (activeServiceWeekend[weekNumberCheck(Reservation)] < 3)
	{
		cout << "We have No Schedule" << endl;
	}
	else
	{
		cout << "We have " << activeTotalBus << " Schedule" << endl;
	}
}

// The demand should meet at least 50% of particular bus type.
// depending on the demand, the company can operate extra service providing that there is a bus available.
void Scheduling::demandCheck(Reservation Reservation)
{
	int reserveBusType = Reservation.GetBusType(Reservation.getBusName());

	int* reserveTickets = Reservation.GetTickets();

	int numTickets = 0;							//THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION
	for (int i = 0; i < 5; i++)
	{
		numTickets += reserveTickets[i];
	}

	if (reserveBusType == 0 && Reservation.IsBusHire() == true)
	{
		if (numTickets >= 26)
		{
			if (activeLuxuryBus > luxuryBusTotal)
			{
				cout << "Already Full hired" << endl;
			}
			else
			{
				activeLuxuryBus++;
				activeTotalBus++;
				activeServiceWeekend[weekNumberCheck(Reservation)] = activeTotalBus;
			}
		}
	}
	else if (reserveBusType == 1 && Reservation.IsBusHire() == true)
	{
		if (numTickets >= 18)
		{
			if (activeMiniBus > miniBusTotal)
			{
				cout << "Already Full hired" << endl;
			}
			else
			{
				activeMiniBus++;
				activeTotalBus++;
				activeServiceWeekend[weekNumberCheck(Reservation)] = activeTotalBus;
			}
		}
	}
	else if (reserveBusType == 2 && Reservation.IsBusHire() == true)
	{
		if (numTickets >= 6)
		{
			if (activeMiniVan > miniVanTotal)
			{
				cout << "Already Full hired" << endl;
			}
			else
			{
				activeMiniVan++;
				activeTotalBus++;
				activeServiceWeekend[weekNumberCheck(Reservation)] = activeTotalBus;
			}
		}
	}
}

void Scheduling::setActiveLuxuryBus(int newActiveLuxuryBus)
{
	activeLuxuryBus = newActiveLuxuryBus;
}

void Scheduling::setActiveMiniBus(int newActiveMiniBus)
{
	activeMiniBus = newActiveMiniBus;
}

void Scheduling::setActiveMiniVan(int newActiveMiniVan)
{
	activeMiniVan = newActiveMiniVan;
}

// You may consider keeping an inventory of vehicles located in different depots.
void Scheduling::busListCheck(Reservation Reservation)
{
	totalBuses = (luxuryBusTotal + miniBusTotal + miniVanTotal);
	cout << "\t Bus List View\t" << endl;
	cout << weekNumberCheck(Reservation) << " Weekend" << endl;
	cout << "Bus Total: " << totalBuses << endl;
	cout << endl;

	cout << "Current Bus List" << endl;
	cout << endl;

	cout << "Luxury Bus" << endl;
	cout << "Active: " << activeLuxuryBus;
	cout << ", Remain: " << (luxuryBusTotal - activeLuxuryBus) << endl;
	cout << endl;

	cout << "Mini Bus" << endl;
	cout << "Active: " << activeMiniBus;
	cout << ", Remain: " << (miniBusTotal - activeMiniBus) << endl;
	cout << endl;

	cout << "Mini Van" << endl;
	cout << "Active: " << activeMiniVan;
	cout << ", Remain: " << (miniVanTotal - activeMiniVan) << endl;
	cout << endl;
}
