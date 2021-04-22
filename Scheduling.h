#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H
#include "Reservation.h"
using namespace std;

class Scheduling
{
private:
	int activeLuxuryBus = 0;
	int activeMiniBus = 0;
	int activeMiniVan = 0;
	int activeTotalBus = 0;
	int activeServiceWeekend[54];
public:
	Scheduling();
	Scheduling(int, int, int, int);
	int getActiveLuxuryBus();
	int getActiveMiniBus();
	int getActiveMiniVan();
	int addLuxuryBus();
	int addMiniBus();
	int addMiniVan();
	int getLuxuryBusTotal();
	int getMiniBusTotal();
	int getMiniVanTotal();
	void setActiveLuxuryBus(int);
	void setActiveMiniBus(int);
	void setActiveMiniVan(int);
	int weekNumberCheck(Reservation Reservation);
	void weekCheck(Reservation Reservation);
	void demandCheck(Reservation Reservation);
	void busListCheck(Reservation Reservation);
};
#endif
