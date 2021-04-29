#ifndef RESERVATION_H
#define RESERVATION_H
#include "Date.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Reservation
{
private:
	//Member variables 
	//Reservation  requires passenger’s biographical information  including name, address, contact  number, email  address, date  of  traveland how  many  tickets.
	string name;
	string address;
	string contactNumber;
	string email;
	Date dateOfTravel;
	string destination;
	string busType;
	long busID;
	int seats[52][2];
	int* tickets;
	bool isBusHire;
	struct tm tm;

public:
	string BusTypes[3] = { "Luxury Bus", "Mini Bus", "Minivan" };
	string Destinations[10] = { "Green Bay to Madison", "Green Bay to Milwakee", "Green Bay to Whitewater", "Green Bay to Oshkosh", "Green Bay to Eau Claire",
	"Madison to Green Bay", "Milwakee to Green Bay", "Whitewater to Green Bay", "Oshkosh to Green Bay", "Eau Claire to Green Bay"};
	char SeatTypes[5] = { 'A', 'B', 'E', 'D', 'C' };

	//Reasons for reservations
	string Reasons[4] = { "Standard Seat Reservations", "Bus Hire", "Cancel Reservation", "Company Authorized Cancellation" };

	string GetName();
	string getBusName();
	void SetDateOfTravel();
	Date GetDateOfTravel();
	int DateValidation(Date date);
	int GetDestination(string Destination);
	int GetBusType(string BusType);
	int* GetTickets();
	int GetSeatType(char Seat);
	bool IsBusHire();
	void CustomerMenu();
	void SetGeneralReservationInfo();
	void SeatReservation();
	void BusHire();
	void CancelReservation();
	void SaveReservation();
	bool FindReservation(string Name, Date Day);
	Reservation GetReservation(string Name, Date Day);
	void PrintReservation();
	void DeleteReservation(Reservation Reservation);
	void ViewReservationByBusAndDate(long BusID, Date date);
	void ViewIncomeByBusByDate(long BusID, Date date);
	void ChangeReservationName(string Name, Date date, string newName);
	void CancelReservationByBusByDate(long BusID, Date date);
	void CancelReservationByBusByDate(long BusID, string Destination, Date date);

	//Destructor
	~Reservation()
	{
		tickets = new int[5];
		for (int i = 0; i < 52; i++)
		{
			seats[i][0] = -1;
			seats[i][1] = -1;
		}
	}

	//Constructor
	Reservation()
	{
		for (int i = 0; i < 52; i++)
		{
			this->seats[i][0] = -1;
			this->seats[i][1] = -1;
		}
		tickets = new int[5];
		for (int i = 0; i < 5; i++)
		{
			tickets[i] = 0;
		}
	}

	//Overload = operator
	const Reservation& operator=(const Reservation& right)
	{
		if (this != &right)
		{
			delete[] tickets;
			this->name = right.name;
			this->address = right.address;
			this->contactNumber = right.contactNumber;
			this->email = right.email;
			this->dateOfTravel = right.dateOfTravel;
			this->destination = right.destination;
			this->busType = right.busType;
			this->busID = right.busID;
			for (int i = 0; i < 52; i++)
			{
				this->seats[i][0] = right.seats[i][0];
				this->seats[i][1] = right.seats[i][1];
			}
			this->tickets = right.tickets;
			this->isBusHire = right.isBusHire;
		}
		return *this;
	}
};
#endif
