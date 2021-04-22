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
	int* tickets;
	bool isBusHire;
	struct tm tm;

public:
	string BusTypes[3] = { "Luxury Bus", "Mini Bus", "Minivan" };
	string Destinations[5] = { "Madison", "Milwakee", "Whitewater", "Oshkosh", "Eau Claire" };
	char SeatTypes[5] = { 'A', 'B', 'C', 'D', 'E' };
	//Reasons for reservations
	string Reasons[4] = { "Standard Seat Reservations", "Bus Hire", "Cancel Reservation", "Company Authorized Cancellation" };

	string GetName();
	string getBusName();
	void SetDateOfTravel();
	Date GetDateOfTravel();
	int DateValidation(Date date);
	struct tm GetWeekNum();
	int GetDestination(string Destination);
	int GetBusType(string BusType);
	int* GetTickets();
	bool IsBusHire();
	void CustomerMenu();
	void SetGeneralReservationInfo();
	void SeatReservation();
	void BusHire();
	void CancelReservation();
	void SaveReservation();
	bool FindReservation(string Name, Date Day);
	Reservation GetReservation(string Name, Date Day);
	void PrintReservation(Reservation Reservation);
	void DeleteReservation(Reservation Reservation);

	//Destructor
	~Reservation()
	{
		tickets = new int[5];
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
			this->tickets = right.tickets;
			this->isBusHire = right.isBusHire;
		}
		return *this;
	}
};
#endif
