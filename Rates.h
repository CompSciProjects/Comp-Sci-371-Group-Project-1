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
	//Constant seat cost rates
	const double LUXURYAISLEANDWINDOW = 0.95; //In  luxury  bus, aisle  and  window  seat  costs   $0.95  per  mile
	const double LUXURYOTHER = 0.75;		  //the other seat  costs  $0.75 per mile
	const double MINIBUSSEAT = 0.65;		  //In small bus, both the aisle seat and window seat costs 0.65
	const double MINIVANSEAT = 0.5;				  //In case of the minivan, each seat cost $0.50 per  mile

	//Bus Hire rates
	double LUXURYBH[3] = { 1500, 0.25, 5000 };   //In  case  of  bus  hire,  the  luxury  bus  cost  $1500 as rent with additional $0.25 for each  mile  of travel. 
												//The  security  deposit  for  luxury  bus  is  $5000
	double MINIBUSBH[3] = { 1300, 0.2, 3000 };  //The  small  bus  costs   $1300  as  rent  with  additional  $0.20  per  mile
												//The  security  deposit for  the  small  bus  $3000 
	double MINIVANBH[3] = { 1000, 0.15, 1500 };	    //the minivan  costs  $1000  as  rent  with  additional  $0.15  per  mile
												//The security deposit for  the  minivan  it  is  $1500  

	//Trip Distances
	/*Source		Destination		Distance
	Green Bay	Madison			135.6 miles
	Green Bay	Milwaukee		118.7 miles
	Green Bay	Whitewater		142.2 miles
	Green Bay	Oshkosh			50.4 miles
	Green Bay	Eau Claire		194.4 miles*/
	double Distances[5] = { 135.6, 118.7, 142.2, 50.4, 194.4 };

	//Reasons for transactions
	string Reasons[3] = { "Standard Seat Reservations", "Bus Hire", "Cancel Reservation" };

	//Member Functions
	double GetRate(int* Tickets, int BusType, bool IsBusHire);
	double GetRentalFee(bool IsBusHire, int BusType);
	double GetDeposit(bool IsBusHire, int BusType);
	double GetPenalty(Date Day, string Reason);
	double GetAmount(Rates Rates, bool IsBusHire, int BusType);
	void SaveTransaction(Reservation Reservation, int Destination, int BusType, string Reason);
	bool FindTransaction(string Name, Date Day, string Reason);
	Rates GetTransaction(string Name, Date Day, string Reason);
	void PrintTransaction(Rates Transaction);

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
