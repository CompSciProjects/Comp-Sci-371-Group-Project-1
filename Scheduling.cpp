#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Reservation.h"
#include "Scheduling.h"
#include "Date.h"
using namespace std;

string Destinations[10] = { "Green Bay to Madison", "Green Bay to Milwakee", "Green Bay to Whitewater", "Green Bay to Oshkosh", "Green Bay to Eau Claire",
	"Madison to Green Bay", "Milwakee to Green Bay", "Whitewater to Green Bay", "Oshkosk to Green Bay", "Eau Claire to Green Bay" };
string BusTypes[3] = { "Luxury Bus", "Mini Bus", "Minivan" };
char SeatTypes[5] = { 'A', 'B', 'E', 'D', 'C' };



int Scheduling::getBusCount(int BusType) //Gets total number of busses if given no arguments, or total number of specific bus type
{
	int count = 0;

	fstream output;

	//Opens file containing transactions
	output.open("./BusInventoryInput.txt", ios::in);

	long BusID;
	string BusType2;
	int Month;
	int Year;
	string Name;

	while (output >> BusID)
	{
		getline(output, BusType2);
		getline(output, BusType2);
		output >> Month;
		output >> Year;
		getline(output, Name);
		getline(output, Name);

		if ((BusType == -1) ? true : BusTypes[BusType].compare(BusType2) == 0)
		{
			count++;
		}
	}

	return count;
}

//mutator methods to add new vehicles of each type
void Scheduling::addVehicle(int BusType)
{
	fstream input;

	//Opens file containing transactions
	input.open("./BusInventoryInput.txt", ios::app);

	if (input.is_open()) //Only try to save to file if file opened properly
	{
		long BusID = getBusCount();

		struct tm tm;
		time_t ttime = time(0);
		localtime_s(&tm, &ttime);
		int Month = 1 + tm.tm_mon;
		int Year = 1900 + tm.tm_year;
		string Name;
		cout << "Please enter the name of the driver for this new vehicle: ";
		cin.ignore();
		getline(cin, Name);

		//writes the data gathered above into the file
		input << BusID << endl;
		input << BusTypes[BusType] << endl;
		input << Month << endl;
		input << Year << endl;
		input << Name << endl;

		//closes the file
		input.close();
	}
}

long Scheduling::isVehicleAvailable(string BusType, Date date) //Finds an available vehicle given the criteria, returns the busID
{
	long isAvailable = 0;
	fstream output;

	//Opens file containing transactions
	output.open("./BusInventoryInput.txt", ios::in);

	long BusID;
	string BusType2;
	int Month;
	int Year;
	string Name;

	while (output >> BusID)
	{
		getline(output, BusType2);
		getline(output, BusType2);
		output >> Month;
		output >> Year;
		getline(output, Name);
		getline(output, Name);

		if (BusType.compare(BusType2) == 0 && ((Year == date.GetYear()) ? Month < date.GetMonth() : true))
		{
			this->findTrip(BusID, date);
			if (this->busID == -1)
			{
				output.close();
				isAvailable = BusID;
				return isAvailable;
			}
		}
	}
	output.close();

	return isAvailable;
}

bool Scheduling::getTrip(string Destination, string BusType, Date date, int Tickets) //if trip is available or if trip can be created, return true, else return false
{
	//find trip, if trip exists, return the available seats
	//if trip does not exist, create one and return the available seats
	this->findTrip(Destination, BusType, date, Tickets);

	if (this->busID == -1)
	{
		long ID = isVehicleAvailable(BusType, date);
		if (ID != 0)
		{
			this->createTrip(ID, Destination, BusType, date);
		}
		else
		{
			return false;
		}
	}
	return true;

}

void Scheduling::findTrip(long BusID, Date date)
{
	fstream output;

	//Opens file containing trip schedule
	output.open("./TripScheduleInput.txt", ios::in);

	if (output.is_open())
	{
		Scheduling trip = Scheduling();
		string TripDate;

		while (output >> trip.busID)
		{
			getline(output, trip.busType);
			getline(output, trip.busType);
			getline(output, trip.destination);
			getline(output, TripDate);
			output >> trip.seatsAvailable;
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					output >> trip.seatArray[i][j];
				}
			}
			if (trip.busID == BusID && TripDate.compare(date.toString()) == 0)
			{
				trip.tripDate = date;
				*this = trip;
				break;
			}
			else
			{
				this->busID = -1;
			}
		}
		output.close();
	}
}

void Scheduling::findTrip(string Destination, string BusType, Date date, int Tickets) //loops through trips, if arguments match, return the trip, else set busID = -1
{
	fstream output;

	//Opens file containing trip schedule
	output.open("./TripScheduleInput.txt", ios::in);

	if (output.is_open())
	{
		Scheduling trip = Scheduling();
		string TripDate;

		while (output >> trip.busID)
		{
			getline(output, trip.busType);
			getline(output, trip.busType);
			getline(output, trip.destination);
			getline(output, TripDate);
			output >> trip.seatsAvailable;
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					output >> trip.seatArray[i][j];
				}
			}

			if (trip.destination.compare(Destination) == 0 && trip.busType.compare(BusType) == 0 && TripDate.compare(date.toString()) == 0 && trip.seatsAvailable >= Tickets)
			{
				trip.tripDate = date;
				*this = trip;
				break;
			}
			else
			{
				this->busID = -1;
			}
		}
		if (trip.busType.compare("") == 0)
		{
			this->busID = -1;
		}
		output.close();
	}
}

void Scheduling::findTrip(long BusID, string Destination, string BusType, Date date) //Althernate call for findTrip
{
	fstream output;

	//Opens file containing trip schedule
	output.open("./TripScheduleInput.txt", ios::in);

	if (output.is_open())
	{
		Scheduling trip = Scheduling();
		string TripDate;

		while (output >> trip.busID)
		{
			getline(output, trip.busType);
			getline(output, trip.busType);
			getline(output, trip.destination);
			getline(output, TripDate);
			output >> trip.seatsAvailable;
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					output >> trip.seatArray[i][j];
				}
			}


			if (trip.busID == BusID && trip.destination.compare(Destination) == 0 && trip.busType.compare(BusType) == 0 && TripDate.compare(date.toString()) == 0)
			{
				trip.tripDate = date;
				*this = trip;
				break;
			}
			else
			{
				this->busID = -1;
			}
		}
		output.close();
	}
}

void Scheduling::createTrip(long BusID, string Destination, string BusType, Date date) //Initializes empty trip and return trip
{
	this->busID = BusID;
	this->busType = BusType;
	this->destination = Destination;
	this->tripDate = date;

	if (BusType.compare(BusTypes[0]) == 0)
	{
		this->seatsAvailable = 52;

		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i < 10)
				{
					this->seatArray[i][j] = 'O';
				}
				else if (i == 10)
				{
					if (j < 2)
					{
						this->seatArray[i][j] = 'O';
					}
					else
					{
						this->seatArray[i][j] = '-';
					}
				}
				else
				{
					this->seatArray[i][j] = '-';
				}
			}
		}
	}
	else if (BusType.compare(BusTypes[1]) == 0)
	{
		this->seatsAvailable = 36;
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (j == 2 || j == 4)
				{
					this->seatArray[i][j] = '-';
				}
				else
				{
					this->seatArray[i][j] = 'O';
				}
			}
		}
	}
	else
	{
		this->seatsAvailable = 12;
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i < 4)
				{
					if (j == 0 || j == 1 || j == 4)
					{
						this->seatArray[i][j] = 'O';
					}
					else
					{
						this->seatArray[i][j] = '-';
					}

				}
				else
				{
					this->seatArray[i][j] = '-';
				}
			}
		}
	}

	//Creates and Saves a return trip
	int returnTripDestination = Reservation().GetDestination(Destination);
	this->destination = (Reservation().Destinations[returnTripDestination].compare(Destination) == 0) ? Reservation().Destinations[returnTripDestination + 5] : Reservation().Destinations[returnTripDestination];
	this->saveTrip();

	this->destination = Destination;
}

void Scheduling::deleteTrip(long BusID, string Destination, string BusType, Date date) //deletes trip
{
	ifstream output;

	output.open("./TripScheduleInput.txt", ios::in);

	ofstream input;

	input.open("./TripScheduleTemp.txt", ios::out);

	if (output.is_open())
	{
		Scheduling trip = Scheduling();
		string TripDate;

		while (output >> trip.busID)
		{
			getline(output, trip.busType);
			getline(output, trip.busType);
			getline(output, trip.destination);
			getline(output, TripDate);
			output >> trip.seatsAvailable;
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					output >> trip.seatArray[i][j];
				}
			}

			if (trip.busType.compare("") != 0 && !(trip.busID == BusID && trip.destination.compare(Destination) == 0 && trip.busType.compare(BusType) == 0 && TripDate.compare(date.toString()) == 0))
			{
				input << trip.busID << endl;
				input << trip.busType << endl;
				input << trip.destination << endl;
				input << TripDate << endl;
				input << trip.seatsAvailable << endl;
				for (int i = 0; i < 12; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						input << trip.seatArray[i][j] << endl;
					}
				}
			}
		}
	}

	input.close();
	output.close();
	remove("./TripScheduleInput.txt");
	rename("./TripScheduleTemp.txt", "./TripScheduleInput.txt");

}

void Scheduling::saveTrip() //saves trip
{
	this->deleteTrip(busID, destination, busType, tripDate);

	fstream input;

	//Opens file containing trip schedule
	input.open("./TripScheduleInput.txt", ios::app);

	if (input.is_open())
	{
		input << this->busID << endl;
		input << this->busType << endl;
		input << this->destination << endl;
		input << this->tripDate.toString() << endl;
		input << this->seatsAvailable << endl;
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				input << this->seatArray[i][j] << endl;
			}
		}
		input.close();
	}
}

long Scheduling::getBusID() //returns busID
{
	return busID;
}

void Scheduling::printSeatArray() //Prints the seat layout
{
	for (int i = 0; i < 12; i++)
	{
		if (seatArray[i][1] != '-')
		{
			cout << i + 1 << ". ";
		}
		for (int j = 0; j < 5; j++)
		{
			if (seatArray[i][j] != '-')
			{
				cout << seatArray[i][j] << "\t";
			}
		}
		if (seatArray[i][1] != '-')
		{
			cout << "\n\n";
		}
	}
}

void Scheduling::printSeatRow(int row) //prints the seat layout for specific row
{
	cout << row << ". ";
	for (int j = 0; j < 5; j++)
	{
		if (seatArray[row - 1][j] != '-')
		{
			cout << seatArray[row - 1][j] << "\t";
		}
	}
	cout << "\n   ";
	for (int j = 0; j < 5; j++)
	{
		if (seatArray[row - 1][j] != '-')
		{
			cout << SeatTypes[j] << "\t";
		}
	}
	cout << "\n\n";
}

char Scheduling::getSeat(int row, int col) //returns seat
{
	return seatArray[row - 1][col];
}

void Scheduling::setSeat(int row, int col) //sets seat
{
	this->seatArray[row - 1][col] = 'X';
	this->seatsAvailable--;
}

void Scheduling::resetSeat(int row, int col) //sets seat back to available
{
	this->seatArray[row - 1][col] = 'O';
	this->seatsAvailable++;
}

double Scheduling::checkCapacity() //returns capacity amount
{
	double capacity;
	if (this->busType.compare(BusTypes[0]) == 0)
	{
		capacity = (double)this->seatsAvailable / 52.0;
	}
	else if (this->busType.compare(BusTypes[1]) == 0)
	{
		capacity = (double)this->seatsAvailable / 36.0;
	}
	else
	{
		capacity = (double)this->seatsAvailable / 12.0;
	}

	return capacity;
}

void Scheduling::CancelUnderCapacityTrips() //cancel trips under 50% capacity
{
	struct tm newtime;
	time_t ttime = time(0);
	localtime_s(&newtime, &ttime);
	Date TwoDaysAway = Date(newtime.tm_mon + 1, newtime.tm_mday, newtime.tm_year + 1900);
	TwoDaysAway.nextDay();
	TwoDaysAway.nextDay();
	ifstream output;

	output.open("./TripScheduleInput.txt", ios::in);

	ofstream input;

	input.open("./TripScheduleTemp.txt", ios::out);

	if (output.is_open())
	{
		Scheduling trip = Scheduling();
		string date;

		while (output >> trip.busType)
		{
			getline(output, trip.busType);
			getline(output, trip.busType);
			getline(output, trip.destination);
			getline(output, date);
			output >> trip.seatsAvailable;
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					output >> trip.seatArray[i][j];
				}
			}

			Scheduling returnTrip = Scheduling();
			int returnTripDestination = Reservation().GetDestination(trip.destination);
			returnTrip.destination = (Reservation().Destinations[returnTripDestination].compare(trip.destination) == 0) ? Reservation().Destinations[returnTripDestination + 5] : Reservation().Destinations[returnTripDestination];
			returnTrip.findTrip(trip.busID, returnTrip.destination, trip.busType, TwoDaysAway);

			if (date.compare(TwoDaysAway.toString()) != 0 || (returnTrip.busID != -1 && (trip.checkCapacity() > .5 || returnTrip.checkCapacity() > .5)))
			{
				input << trip.busID << endl;
				input << trip.busType << endl;
				input << trip.destination << endl;
				input << date << endl;
				input << trip.seatsAvailable << endl;
				for (int i = 0; i < 12; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						input << trip.seatArray[i][j] << endl;
					}
				}
			}
			else
			{
				Reservation tripReservation = Reservation();
				tripReservation.CancelReservationByBusByDate(trip.busID, TwoDaysAway);

			}
		}


		input.close();
		output.close();
		remove("./TripScheduleInput.txt");
		rename("./TripScheduleTemp.txt", "./TripScheduleInput.txt");
	}
}

void Scheduling::CancelReservationByBusByDate(long BusID, Date date) //cancels trip based on arguments
{
	ifstream output;

	output.open("./TripScheduleInput.txt", ios::in);

	ofstream input;

	input.open("./TripScheduleTemp.txt", ios::out);

	if (output.is_open())
	{
		Scheduling trip = Scheduling();
		string TripDate;

		while (output >> trip.busID)
		{
			getline(output, trip.busType);
			getline(output, trip.busType);
			getline(output, trip.destination);
			getline(output, TripDate);
			output >> trip.seatsAvailable;
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					output >> trip.seatArray[i][j];
				}
			}

			if (trip.busType.compare("") != 0 && !(trip.busID == BusID && TripDate.compare(date.toString()) == 0))
			{
				input << trip.busID << endl;
				input << trip.busType << endl;
				input << trip.destination << endl;
				input << TripDate << endl;
				input << trip.seatsAvailable << endl;
				for (int i = 0; i < 12; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						input << trip.seatArray[i][j] << endl;
					}
				}
			}
		}

		input.close();
		output.close();
		remove("./TripScheduleInput.txt");
		rename("./TripScheduleTemp.txt", "./TripScheduleInput.txt");
	}

}

long Scheduling::getBusIDList() //prints out list of busses, asks for bus number selection, returns selection
{
	int count = 0;
	fstream output;

	//Opens file containing transactions
	output.open("./BusInventoryInput.txt", ios::in);

	long BusID;
	string BusType2;
	int Month;
	int Year;
	string Name;

	while (output >> BusID)
	{
		getline(output, BusType2);
		getline(output, BusType2);
		output >> Month;
		output >> Year;
		getline(output, Name);
		getline(output, Name);

		cout << "Bus Number: " << BusID << "\tBus Type: " << BusType2 << "\tBus Driver: " << Name << "\n";
		count++;

	}
	long selection;
	cout << "\nPlease enter the bus number of the bus you wish to select: ";
	cin >> selection;
	while (selection < 0 || selection > count)
	{
		cout << "That selection is not valid.\n"
			<< "\nPlease enter the bus number of the bus you wish to select: ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> selection;
	}
	return selection;
}
