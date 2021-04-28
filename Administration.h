#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H
#include "Date.h"
using namespace std;

class Admin
{
private:
	int luxBusNum = 0;
	int miniBusNum = 0;
	int miniVanNum = 0;
	int changeChoice = 0;
	double secDeposit = 0;
	double mileCost = 0;
	double changeAmount = 0; //rent rate
	double changeAmountWindow = 0;
public:
	//reference to all methods from Administration.cpp
	void AdminMenu();
	void AddVehicles();
	void EditReservation(Date date);
	void ChangeReservationCharge();
	Date EnterDate();
};
#endif
