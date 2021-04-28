#ifndef SCHEDULING_H
#define SCHEDULING_H
#include "Reservation.h"
using namespace std;

class Scheduling
{
private:
	long busID;
	string busType;
	string destination;
	Date tripDate;
	int seatsAvailable;
	char seatArray[12][5];
public:
	int getBusCount(int BusType = -1);
	void addVehicle(int BusType);
	long isVehicleAvailable(string BusType, Date date);
	bool getTrip(string Destination, string BusType, Date date, int Tickets);
	void findTrip(long BusID, Date date);
	void findTrip(string Destination, string BusType, Date date, int Tickets);
	void findTrip(long BusID, string Destination, string BusType, Date date);
	void createTrip(long BusID, string Destination, string BusType, Date date);
	void deleteTrip(long BusID, string Destination, string BusType, Date date);
	void saveTrip();
	long getBusID();
	void printSeatArray();
	void printSeatRow(int row);
	char getSeat(int row, int col);
	void setSeat(int row, int col);
	void resetSeat(int row, int col);
	double checkCapacity();
	void CancelUnderCapacityTrips();
	void CancelReservationByBusByDate(long BusID, Date date);
	long getBusIDList();

	const Scheduling operator=(const Scheduling& right)
	{
		if (this != &right)
		{
			this->busID = right.busID;
			this->busType = right.busType;
			this->tripDate = right.tripDate;
			this->seatsAvailable = right.seatsAvailable;

			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					this->seatArray[i][j] = right.seatArray[i][j];
				}
			}
		}


		return *this;
	}

};
#endif
