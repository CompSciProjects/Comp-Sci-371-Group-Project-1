#ifndef RATES_H
#define RATES_H
#include "Reservation.h"
#include "Date.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Rates
{
private:
	//Member Variables
	string name;
	Date day;
	double distance;
	double rate;
	int tickets;
	double rentalFee;
	double deposit;
	double penalty;
	double tax = 1.1;						  //For  each  ticket  and  bus  hire  is  subject  to  government  tax  of  10%  which  can  change  periodically
	double amount;
	string reason;
public:
	//Trip Distances
	/*Source		Destination		Distance
	Green Bay	Madison			135.6 miles
	Green Bay	Milwaukee		118.7 miles
	Green Bay	Whitewater		142.2 miles
	Green Bay	Oshkosh			50.4 miles
	Green Bay	Eau Claire		194.4 miles*/
	double Distances[5] = { 135.6, 118.7, 142.2, 50.4, 194.4 };

	//Reasons for transactions
	string Reasons[4] = { "Standard Seat Reservations", "Bus Hire", "Cancel Reservation", "Company Authorized Cancellation" };

	//Member Functions
	double GetRate(int* Tickets, int BusType, bool IsBusHire);
	void GetRate(int BusType, int Destination, bool IsBusHire);
	double GetRentalFee(bool IsBusHire, int BusType);
	double GetDeposit(bool IsBusHire, int BusType);
	double GetPenalty(Date Day, string Reason);
	double GetAmount(Rates Rates, bool IsBusHire, int BusType);
	double GetDistance();
	double GetAmount();
	double GetDeposit();
	void setLuxSeatRate(double changeAmountWindow, double changeAmountOther);
	void setMiniBusSeatRate(double changeAmount);
	void setMiniVanSeatRate(double changeAmount);
	void setLuxBusRate(double changeAmount, double mileCost, double secDeposit);
	void setMiniBusRate(double changeAmount, double mileCost, double secDeposit);
	void setMiniVanRate(double changeAmount, double mileCost, double secDeposit);
	double getLuxSeatRate();
	double getLuxSeatRateWindow();
	double getMiniBussSeatRate();
	double getMiniVanSeatRate();
	void SaveTransaction(Reservation Reservation, int Destination, int BusType, string Reason);
	bool FindTransaction(string Name, Date Day, string Reason);
	void GetTransaction(string Name, Date Day, string Reason);
	void PrintTransaction(Rates Transaction);
	void CheckWeeklySales(Date date);
	void ChangeTransactionName(Reservation Reservation, string NewName);
	void ChangeReservationCharge(Reservation Reservation, double Amount);

	//Overload = operator
	const Rates& operator=(const Rates& right)
	{
		if (this != &right)
		{
			this->name = right.name;
			this->day = right.day;
			this->distance = right.distance;
			this->rate = right.rate;
			this->tickets = right.tickets;
			this->rentalFee = right.rentalFee;
			this->deposit = right.deposit;
			this->penalty = right.penalty;
			this->amount = right.amount;
			this->reason = right.reason;
		}
		return *this;
	}

};

#endif
