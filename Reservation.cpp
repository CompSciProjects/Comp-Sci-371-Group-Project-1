#include "Administration.h"
#include "Reservation.h"
#include "Rates.h"
#include "Scheduling.h"
#include "Date.h"
#include <iostream>
#include <time.h>
using namespace std;

string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

string Reservation::GetName() //Returns reservation name
{
	return this->name;
}

string Reservation::getBusName() //Returns bus name
{
	return this->busType;
}

void Reservation::SetDateOfTravel() //sets reservation date
{
	int Month;
	int Day;
	int Year = 2021;
	time_t ttime = time(0);
	localtime_s(&tm, &ttime);
	Date CurrentDate(1 + tm.tm_mon, tm.tm_mday, 1900 + tm.tm_year);
	int CurrentMonth = tm.tm_mon + 1;

	int threeMonths = tm.tm_mon + 3;
	if ((CurrentMonth == 2 && tm.tm_mday > 14) || (CurrentMonth != 2 && tm.tm_mday > 16))
	{
		
		(CurrentMonth == 12)? CurrentMonth = 1 : CurrentMonth++;
		threeMonths++;
	}

	int year = tm.tm_year + 1900;
	cout << "\n";
	for (int i = CurrentMonth - 1; i < 12; i++)
	{
		if(i < threeMonths)
		{
			cout << i + 1 << ". " << months[i] << " " << year << "\n";
			if (i == 11 && threeMonths > 11)
			{
				for (int j = 0; j < threeMonths - 12; j++)
				{
					cout << j + 1 << ". " << months[j] << " " << year + 1 << "\n";
				}
			}
		}
		
	}
	cout << "\n";
	cout << "Please enter the month in which you want to travel corresponding to the numbers above: ";
	cin >> Month;
	if (Month != CurrentMonth && (Month != ((CurrentMonth == 11 || CurrentMonth == 12)? CurrentMonth - 10 : CurrentMonth + 2)) && (Month != ((CurrentMonth == 12)? CurrentMonth - 11 : CurrentMonth + 1 )))
	{
		while(Month != CurrentMonth && (Month != ((CurrentMonth == 11 || CurrentMonth == 12) ? CurrentMonth - 10 : CurrentMonth + 2)) && (Month != ((CurrentMonth == 12) ? CurrentMonth - 11 : CurrentMonth + 1)))
		{
			cout << "The month you entered is not valid.\n"
				<< "Please enter the month in which you want to travel corresponding to the numbers above: ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> Month;
		}
	}

	if (CurrentMonth > Month && threeMonths > 12)
	{
		year++;
	}

	cout << "Please enter the day you wish to travel in " << months[Month-1] << " (Must be at least 2 weeks out): ";
	cin >> Day;

	int DaysBefore = this->DateValidation(Date(Month, Day, year));
	switch (Month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (Day < 1 || Day > 31 || DaysBefore < 14)
		{
			while (Day < 1 || Day > 31 || DaysBefore < 14)
			{
				cout << "The day you entered is not valid.\n"
					<< "Please enter the day you wish to travel in " << months[Month-1] << ": ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> Day;

				DaysBefore = this->DateValidation(Date(Month, Day, year));
			}
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (Day < 1 || Day > 30 || DaysBefore < 14)
		{
			while (Day < 1 || Day > 30 || DaysBefore < 14)
			{
				cout << "The day you entered is not valid.\n"
					<< "Please enter the day you wish to travel in " << months[Month - 1] << ": ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> Day;

				DaysBefore = this->DateValidation(Date(Month, Day, year));
			}
		}
		break;
	case 2:
		bool leapYear;
		if (Year % 4 == 0)
		{
			leapYear = true;
		}
		else
		{
			leapYear = false;
		}

		if (Day < 1 || ((leapYear) ? Day > 29 : Day > 28) || DaysBefore < 14)
		{
			while (Day < 1 || ((leapYear) ? Day > 29 : Day > 28) || DaysBefore < 14)
			{
				cout << "The day you entered is not valid.\n"
					<< "Please enter the day you wish to travel in " << months[Month - 1] << ": ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> Day;

				DaysBefore = this->DateValidation(Date(Month, Day, year));
			}
		}
		break;
	default:
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	}

	this->dateOfTravel.SetMonth(Month);
	this->dateOfTravel.SetDay(Day);
	this->dateOfTravel.SetYear(year);

	int changeYear = year - 1900;

	tm.tm_mon = Month;
	tm.tm_mday = Day;
	tm.tm_year = changeYear;
}

Date Reservation::GetDateOfTravel() //returns date of travel
{
	return this->dateOfTravel;
}

int Reservation::DateValidation(Date date) //Validates if date is greater than two weeks out
{
	int DaysBefore;
	Date Current(1 + tm.tm_mon, tm.tm_mday, 1900 + tm.tm_year);

	//Checks if trip is within 14 days from now 
	for (DaysBefore = 0; DaysBefore < 14; DaysBefore++)
	{
		if (Current.toString().compare(date.toString()) == 0)
		{
			break;
		}
		Current.nextDay();
	}
	return DaysBefore;
}

int Reservation::GetDestination(string Destination) //Returns destination number, corresponding to distances array in rates
{
	int DestinationNum;
	if (Destination.compare(Destinations[0]) == 0 || Destination.compare(Destinations[5]) == 0)
	{
		DestinationNum = 0;
	}
	else if (Destination.compare(Destinations[1]) == 0 || Destination.compare(Destinations[6]) == 0)
	{
		DestinationNum = 1;
	}
	else if (Destination.compare(Destinations[2]) == 0 || Destination.compare(Destinations[7]) == 0)
	{
		DestinationNum = 2;
	}
	else if (Destination.compare(Destinations[3]) == 0 || Destination.compare(Destinations[8]) == 0)
	{
		DestinationNum = 3;
	}
	else
	{
		DestinationNum = 4;
	}
	return DestinationNum;
}

int Reservation::GetBusType(string BusType) //returns bus type corresponding to bustypes array 
{
	int BusTypeNum;
	if (BusType.compare(BusTypes[0]) == 0)
	{
		BusTypeNum = 0;
	}
	else if (BusType.compare(BusTypes[1]) == 0)
	{
		BusTypeNum = 1;
	}
	else
	{
		BusTypeNum = 2;
	}
	return BusTypeNum;
}

int* Reservation::GetTickets() //returns tickets
{
	return this->tickets;
}

int Reservation::GetSeatType(char Seat) //returns number correstponding to seat types array
{
	int SeatType;
	if (Seat == SeatTypes[0])
	{
		SeatType = 0;
	}
	else if (Seat == SeatTypes[1])
	{
		SeatType = 1;
	}
	else if (Seat == SeatTypes[2])
	{
		SeatType = 2;
	}
	else if (Seat == SeatTypes[3])
	{
		SeatType = 3;
	}
	else
	{
		SeatType = 4;
	}
	return SeatType;
}

bool Reservation::IsBusHire() //Returns bus hire status
{
	return this->isBusHire;
}

void Reservation::CustomerMenu() //Customer selection menu
{
	try
	{
		int option = 0;

		cout << "Customer Menu";

		//Allows the user to choose an Customer task or exit the Customer menu
		while (option != 4)
		{
			cout << "\n\n1. Reserve seat(s)\n"
				<< "2. Hire a bus\n"
				<< "3. Cancel Reservation\n"
				<< "4. Exit\n"
				<< "Please select an option 1 through 4:";
			cin >> option;
			cout << "\n";

			switch (option)
			{
			case 1:
				this->SeatReservation();
				break;
			case 2:
				this->BusHire();
				break;
			case 3:
				this->CancelReservation();
				break;
			case 4:
				cout << "Exiting the Customer Menu. Redirecting back to main menu.\n\n";
				break;
			default:
				cout << "That is not a valid option.\n\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
		}
	}
	catch (exception e)
	{
		cout << "Sorry, an unexpected error occured. Redirecting back to the main menu.\n\n";
	}
}

void Reservation::SetGeneralReservationInfo() //Sets generic info for both normal seat reservations and bus hires
{
	int Destination;
	int BusType;

	cout << "Please enter your full name: ";
	cin.ignore();
	getline(cin, this->name);

	cout << "Please enter your address: ";
	cin.ignore(0, EOF);
	getline(cin, this->address);

	cout << "Please enter your phone number: ";
	cin.ignore(0, EOF);
	getline(cin, this->contactNumber);

	cout << "Please enter your email address: ";
	cin.ignore(0, EOF);
	getline(cin, this->email);

	this->SetDateOfTravel();
	
	cout << "\n\n";

	for (int i = 0; i < 10; i++)
	{
		cout << i + 1 << ". " << Destinations[i] << "\n";
	}
	cout << "\nPlease enter which destination you would like to go to on " << this->dateOfTravel.toString() << ": ";
	cin >> Destination;
	while (Destination < 1 || Destination > 10)
	{
		cout << "\nThat is not a valid destination. Valid destinations are 1 through 10.\n"
			<< "Please enter which destination you would like to go to on " << this->dateOfTravel.toString() << ": ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> Destination;
	}
	Destination--;

	cout << "\n\n";
	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << ". " << BusTypes[i] << "\n";
	}
	cout << "\nPlease enter which bus type you would like to use: ";
	cin >> BusType;
	while (BusType < 1 || BusType > 3)
	{
		cout << "That is not a valid bus type. Valid bus types are 1 through 3.\n"
			<< "Please enter which bus type you would like to use: ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> BusType;
	}
	BusType--;

	this->destination = Destinations[Destination];
	this->busType = BusTypes[BusType];
}

void Reservation::SeatReservation() //Seat reservation section
{
	this->SetGeneralReservationInfo();

	int Destination = this->GetDestination(destination);

	int BusType = this->GetBusType(busType);

	int Tickets;
	cout << "\nPlease enter about how many tickets you want: ";
	cin >> Tickets;
	while (Tickets < 1 || Tickets > 12)
	{
		cout << "That is too many tickets for reservation.\n"
			<< "\nPlease enter about how many tickets you want: ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> Tickets;
	}

	Scheduling trip = Scheduling();
	if (trip.getTrip(destination, busType, dateOfTravel, Tickets))
	{
		this->busID = trip.getBusID();
		Tickets = 0;
		int Seats[] = { 0,0,0,0,0 }; 
		int input = -1;
		char input2;
		int row;
		int col;

		while (input != 0)
		{
			cout << "\n";
			trip.printSeatArray();
			cout << "0. Exit\n"
				<< "Please select which row you woud like a ticket in, or select 0 to exit selection: ";
			cin >> input;

			if (input == 0)
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			else if (input < 0 || (BusType == 0) ? input > 11 : (BusType == 1) ? input > 12 : input > 4)
			{
				while (input < 0 || (BusType == 0) ? input > 11 : (BusType == 1) ? input > 12 : input > 4)
				{
					cout << "That selection is not valid.\n"
						<< "Please select which row you woud like a ticket in, or select 0 to exit selection: ";
					cin >> input;
					if (input == 0)
					{
						break;
					}
				}
			}
			row = input;
			trip.printSeatRow(row);

			cout << "Open seats are marked by 'O' and taken seats are marked by 'X'\n";
			cout << "Please enter the letter corresponding to the seat you would like, or enter 0 to exit: ";
			cin >> input2;

			if (input2 != '0' && toupper(input2) != 'A' && toupper(input2) != 'B' && toupper(input2) != 'E' && toupper(input2) != 'D' && toupper(input2) != 'C')
			{
				cout << "That entry is not valid. Redirecting to the seat display menu.\n\n";
			}
			else if (input2 == '0')
			{
				cout << "\n\n";
				input = 0;
			}
			else
			{
				col = this->GetSeatType(toupper(input2));
				char seat = trip.getSeat(row, col);
				if (seat == 'O')
				{
					this->seats[Tickets][0] = row-1;
					this->seats[Tickets][1] = col;
					Tickets++;
					Seats[col]++;
					trip.setSeat(row, col);
				}
				else
				{
					cout << "That selection is not valid.\n\n";
				}
			}
		}

		this->tickets = new int[5];  
		for (int i = 0; i < 5; i++)	
		{
			this->tickets[i] = Seats[i];
		}							
		this->isBusHire = false;

		if (Tickets > 0)
		{
			cout << "\n\nPlease confirm you would like to make this reservation.\n"
				<< "1. Yes\n"
				<< "2. No\n";
			cin >> input;
			while (input != 1 && input != 2)
			{
				cout << "That is not a valid entry.\n\n"
					<< "Please confirm you would like to make this reservation.\n"
					<< "1. Yes\n"
					<< "2. No\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> input;
			}
		}

		if (input == 1 && Tickets > 0)
		{
			trip.saveTrip();
			this->SaveReservation();
		
			Rates().SaveTransaction(*this, Destination, BusType, Reasons[0]);

			cout << "Reservation has been confirmed. Redirecting to Customer menu.\n\n";
		}
		else
		{
			cout << "Reservation has been cancelled. Redirecting to the customer menu.\n\n";
		}
	}
	else
	{
		cout << "\n\nSorry, there are no buses available for your desired trip.\n\n";
	}
	
}

void Reservation::BusHire() //Bus hire section
{
	this->SetGeneralReservationInfo();

	int Destination = this->GetDestination(destination);

	int BusType = this->GetBusType(busType);

	int Tickets;
	if (BusType == 0)
	{
		Tickets = 27;
	}
	else if (BusType == 1)
	{
		Tickets = 19;
	}
	else
	{
		Tickets = 7;
	}

	Scheduling trip = Scheduling();
	if (trip.getTrip(destination, busType, dateOfTravel, Tickets))
	{
		this->busID = trip.getBusID();
		Tickets = 0;
		int Seats[] = { 0,0,0,0,0 }; 
		
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (trip.getSeat(i + 1, j) == 'O')
				{
					this->seats[Tickets][0] = i;
					this->seats[Tickets][1] = j;
					Tickets++;
					Seats[j]++;
					trip.setSeat(i + 1, j);
				}
			}
		}

		this->tickets = new int[5];
		for (int i = 0; i < 5; i++)	
		{
			this->tickets[i] = Seats[i];
		}							
		this->isBusHire = true;

		int input;
		cout << "\n\nPlease confirm you would like to make this reservation.\n"
			<< "1. Yes\n"
			<< "2. No\n";
		cin >> input;
		while (input != 1 && input != 2)
		{
			cout << "That is not a valid entry.\n\n"
				<< "Please confirm you would like to make this reservation.\n"
				<< "1. Yes\n"
				<< "2. No\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> input;
		}

		if (input == 1 && Tickets > 0)
		{
			trip.saveTrip();
			this->SaveReservation();

			Rates().SaveTransaction(*this, Destination, BusType, Reasons[1]);

			cout << "Reservation has been confirmed. Redirecting to Customer menu.\n\n";
		}
		else
		{
			cout << "Reservation has been cancelled. Redirecting to the customer menu.\n\n";
		}
	}
	else
	{
		cout << "\n\nSorry, there are no buses available for your desired trip.\n\n";
	}
}

void Reservation::CancelReservation() //Cancels reservation
{
	string Name;
	int Month;
	int Day;
	int Year = 2021;
	time_t ttime = time(0);
	localtime_s(&tm, &ttime);
	Year = 1900 + tm.tm_year;

	cout << "Please enter the name under the reservation: ";
	cin.ignore();
	getline(cin, Name);

	Date date = Admin().EnterDate();
	if (Reservation().FindReservation(Name, date) && (Rates().FindTransaction(Name, date, Reasons[0]) || Rates().FindTransaction(Name, date, Reasons[1])))
	{
		Reservation reservation = Reservation().GetReservation(Name, date);

		Scheduling trip = Scheduling();
		trip.findTrip(reservation.busID, reservation.destination, reservation.busType, reservation.dateOfTravel);

		for (int i = 0; i < 52; i++)
		{
			if (reservation.seats[i][0] != -1)
			{
				trip.resetSeat(reservation.seats[i][0] + 1, reservation.seats[i][1]);
			}
		}

		trip.saveTrip();

		Rates().SaveTransaction(reservation, reservation.GetDestination(reservation.destination), reservation.GetBusType(reservation.busType), Reasons[2]);

		this->DeleteReservation(reservation);
	}
	else
	{
		cout << "Sorry, your reservation was not found. Unable to cancel reservation";
	}

}

void Reservation::SaveReservation()
{
	fstream input;

	//Opens file containing transactions
	input.open("./ReservationInput.txt", ios::app);

	if (input.is_open()) //Only try to save to file if file opened properly
	{
		//writes the data gathered above into the file
		input << this->name << endl;
		input << this->address << endl;
		input << this->contactNumber << endl;
		input << this->email << endl;
		input << this->dateOfTravel.toString() << endl;
		input << this->destination << endl;
		input << this->busType << endl;
		input << this->busID << endl;
		for (int i = 0; i < 52; i++)
		{
			input << this->seats[i][0] << endl;
			input << this->seats[i][1] << endl;
		}
		for (int i = 0; i < 5; i++)		
		{
			input << this->tickets[i] << endl;
		}									
		input << this->isBusHire << endl;

		input.close();

		this->PrintReservation();
	}
	else
	{
		cout << "There has been an error saving the transaction. Please try again later.\n\n";
	}
}

bool Reservation::FindReservation(string Name, Date Day) //Finds reservation returns true if found, and false if found
{
	bool isFound = false;

	ifstream output;

	output.open("./ReservationInput.txt", ios::in);
	if (output.is_open()) 
	{
		Reservation reservation = Reservation();
		string DateOfTravel;

		while (getline(output, reservation.name))  
		{
			getline(output, reservation.address);
			getline(output, reservation.contactNumber);
			getline(output, reservation.email);
			getline(output, DateOfTravel);
			getline(output, reservation.destination);
			getline(output, reservation.busType);
			output >> reservation.busID;
			for (int i = 0; i < 52; i++)
			{
				output >> reservation.seats[i][0];
				output >> reservation.seats[i][1];
			}
			for (int i = 0; i < 5; i++)	
			{
				output >> reservation.tickets[i];
			}							
			output >> reservation.isBusHire;

			//If passed name, day, and reason for transaction are the same, the record is found
			if (reservation.name.compare(Name) == 0 && DateOfTravel.compare(Day.toString()) == 0)
			{
				isFound = true;
				break; //break when record is found
			}
			else
			{
				isFound = false;
			}

			getline(output, reservation.name);
		}

		output.close();
	}

	return isFound;

}

Reservation Reservation::GetReservation(string Name, Date Day) //
{
	ifstream output;

	output.open("./ReservationInput.txt", ios::in);
	if (output.is_open()) 
	{

		Reservation reservation = Reservation();
		string DateOfTravel;

		while (getline(output, reservation.name)) //Gets name on the transaction 
		{
			//Gets string objects from file using getline() and other objects directly through >> 
			//to prevent memory access violations sometimes caused by reading strings
			getline(output, reservation.address);
			getline(output, reservation.contactNumber);
			getline(output, reservation.email);
			getline(output, DateOfTravel);
			getline(output, reservation.destination);
			getline(output, reservation.busType);
			output >> reservation.busID;
			for (int i = 0; i < 52; i++)
			{
				output >> reservation.seats[i][0];
				output >> reservation.seats[i][1];
			}
			for (int i = 0; i < 5; i++) 
			{
				output >> reservation.tickets[i];
			}							
			output >> reservation.isBusHire;

			//If passed name, day, and reason for transaction are the same, the record is found
			if (reservation.name.compare(Name) == 0 && DateOfTravel.compare(Day.toString()) == 0)
			{
				reservation.dateOfTravel = Day;
				break; //break when record is found
			}

			getline(output, reservation.name);
		}

		//closes the file
		output.close();

		return reservation;
	}	
}

void Reservation::PrintReservation() //Prints reservation
{
	cout << "\n\nReservation Details\n\n"
		<< "Name: " << this->name << "\n"
		<< "Address: " << this->address << "\n"
		<< "Contact Number: " << this->contactNumber << "\n"
		<< "Email: " << this->email << "\n"
		<< "Date of Travel: " << this->dateOfTravel.toString() << "\n"
		<< "Destination: " << this->destination << "\n"
		<< "Bus Type: " << this->busType << "\n"
		<< "Bus Number: " << this->busID << "\n"
		<< "Seats reserved: \n";
		for (int i = 0; i < 52; i++)
		{
			if (this->seats[i][0] != -1)
			{
				cout << this->seats[i][0] + 1 << "-" << SeatTypes[this->seats[i][1]] << "\n";
			}
			
		}
		
		int numTickets = 0;							
		for (int i = 0; i < 5; i++)
		{
			numTickets += this->tickets[i];
		}
		cout <<"Total tickets: " << numTickets << "\n";	
		cout << ((this->isBusHire)? "This Reservation is for a bus hire." : "This is a personal reservation" ) << "\n\n";
}

void Reservation::DeleteReservation(Reservation reservation)
{
	ifstream output;
	
	output.open("./ReservationInput.txt", ios::in);

	ofstream input;

	input.open("./ReservationTemp.txt", ios::out);

	if (output.is_open())
	{
		Reservation reservation2 = Reservation();
		string DateOfTravel;

		while (getline(output, reservation2.name)) //Gets name on the transaction 
		{
			//Gets string objects from file using getline() and other objects directly through >> 
			//to prevent memory access violations sometimes caused by reading strings
			getline(output, reservation2.address);
			getline(output, reservation2.contactNumber);
			getline(output, reservation2.email);
			getline(output, DateOfTravel);
			getline(output, reservation2.destination);
			getline(output, reservation2.busType);
			output >> reservation2.busID;
			for (int i = 0; i < 52; i++)
			{
				output >> reservation2.seats[i][0];
				output >> reservation2.seats[i][1];
			}
			for (int i = 0; i < 5; i++)
			{
				output >> reservation2.tickets[i];
			}
			output >> reservation2.isBusHire;


			if (reservation2.name.compare("") != 0 && !(reservation2.name.compare(reservation.name) == 0 && DateOfTravel.compare(reservation.dateOfTravel.toString()) == 0))
			{
				input << reservation2.name << endl;
				input << reservation2.address << endl;
				input << reservation2.contactNumber << endl;
				input << reservation2.email << endl;
				input << DateOfTravel << endl;
				input << reservation2.destination << endl;
				input << reservation2.busType << endl;
				input << reservation2.busID << endl;
				for (int i = 0; i < 52; i++)
				{
					input << reservation2.seats[i][0] << endl;
					input << reservation2.seats[i][1] << endl;
				}
				for (int i = 0; i < 5; i++)			
				{
					input << reservation2.tickets[i] << endl;
				}									
				input << reservation2.isBusHire << endl;
			}
			getline(output, reservation2.name);
		}
		cout << "Reservation successfully deleted.\n\n";
	}

	input.close();
	output.close();
	remove("./ReservationInput.txt");
	rename("./ReservationTemp.txt", "./ReservationInput.txt");
}

void Reservation::ViewReservationByBusAndDate(long BusID, Date date)
{
	bool reservations = false;
	ifstream output;

	output.open("./ReservationInput.txt", ios::in);
	if (output.is_open()) 
	{

		Reservation reservation = Reservation();
		string DateOfTravel;

		while (getline(output, reservation.name)) //Gets name on the transaction 
		{
			//Gets string objects from file using getline() and other objects directly through >> 
			//to prevent memory access violations sometimes caused by reading strings
			getline(output, reservation.address);
			getline(output, reservation.contactNumber);
			getline(output, reservation.email);
			getline(output, DateOfTravel);
			getline(output, reservation.destination);
			getline(output, reservation.busType);
			output >> reservation.busID;
			for (int i = 0; i < 52; i++)
			{
				output >> reservation.seats[i][0];
				output >> reservation.seats[i][1];
			}
			for (int i = 0; i < 5; i++)
			{
				output >> reservation.tickets[i];
			}
			output >> reservation.isBusHire;

			//If passed name, day, and reason for transaction are the same, the record is found
			if (BusID == reservation.busID && DateOfTravel.compare(date.toString()) == 0)
			{
				reservation.dateOfTravel = date;
				reservation.PrintReservation();
				reservations = true;
			}
			getline(output, reservation.name);
		}

		//closes the file
		output.close();

		if (!reservations)
		{
			cout << "Sorry, there were no reservations found for that bus and day.\n\n";
		}
	}
}

void Reservation::ViewIncomeByBusByDate(long BusID, Date date)
{
	double amount = 0;
	ifstream output;

	output.open("./ReservationInput.txt", ios::in);
	if (output.is_open())
	{

		Reservation reservation = Reservation();
		string DateOfTravel;

		while (getline(output, reservation.name)) //Gets name on the transaction 
		{
			//Gets string objects from file using getline() and other objects directly through >> 
			//to prevent memory access violations sometimes caused by reading strings
			getline(output, reservation.address);
			getline(output, reservation.contactNumber);
			getline(output, reservation.email);
			getline(output, DateOfTravel);
			getline(output, reservation.destination);
			getline(output, reservation.busType);
			output >> reservation.busID;
			for (int i = 0; i < 52; i++)
			{
				output >> reservation.seats[i][0];
				output >> reservation.seats[i][1];
			}
			for (int i = 0; i < 5; i++)
			{
				output >> reservation.tickets[i];
			}
			output >> reservation.isBusHire;

			//If passed name, day, and reason for transaction are the same, the record is found
			if (BusID == reservation.busID && DateOfTravel.compare(date.toString()) == 0)
			{
				reservation.dateOfTravel = date;
				Rates transaction = Rates();
				transaction.GetTransaction(reservation.name, date, Reasons[0]);
				if (transaction.GetDistance() == -1)
				{
					transaction.GetTransaction(reservation.name, date, Reasons[1]);
				}
				else if (transaction.GetDistance() == -1)
				{
					transaction.GetTransaction(reservation.name, date, Reasons[2]);
				}
				else
				{
					transaction.GetTransaction(reservation.name, date, Reasons[3]);
				}
				amount += transaction.GetAmount();

			}
			getline(output, reservation.name);
		}

		output.close();
		cout << "The total revenue for bus number " << BusID << " on " << date.toString() << ": $" << amount << "\n";
	}
}

void Reservation::ChangeReservationName(string Name, Date date, string newName)
{
	ifstream output;

	output.open("./ReservationInput.txt", ios::in);

	ofstream input;

	input.open("./ReservationTemp.txt", ios::out);

	if (output.is_open())
	{
		Reservation reservation = Reservation();
		string DateOfTravel;

		while (getline(output, reservation.name)) 
		{
			//Gets string objects from file using getline() and other objects directly through >> 
			//to prevent memory access violations sometimes caused by reading strings
			getline(output, reservation.address);
			getline(output, reservation.contactNumber);
			getline(output, reservation.email);
			getline(output, DateOfTravel);
			getline(output, reservation.destination);
			getline(output, reservation.busType);
			output >> reservation.busID;
			for (int i = 0; i < 52; i++)
			{
				output >> reservation.seats[i][0];
				output >> reservation.seats[i][1];
			}
			for (int i = 0; i < 5; i++)
			{
				output >> reservation.tickets[i];
			}
			output >> reservation.isBusHire;

			if (reservation.name.compare("") != 0 && !(reservation.name.compare(Name) == 0 && DateOfTravel.compare(date.toString()) == 0))
			{
				input << reservation.name << endl;
				input << reservation.address << endl;
				input << reservation.contactNumber << endl;
				input << reservation.email << endl;
				input << DateOfTravel << endl;
				input << reservation.destination << endl;
				input << reservation.busType << endl;
				input << reservation.busID << endl;
				for (int i = 0; i < 52; i++)
				{
					input << reservation.seats[i][0] << endl;
					input << reservation.seats[i][1] << endl;
				}
				for (int i = 0; i < 5; i++)			
				{
					input << reservation.tickets[i] << endl;
				}									
				input << reservation.isBusHire << endl;
			}
			else
			{
				input << newName << endl;
				input << reservation.address << endl;
				input << reservation.contactNumber << endl;
				input << reservation.email << endl;
				input << DateOfTravel << endl;
				input << reservation.destination << endl;
				input << reservation.busType << endl;
				input << reservation.busID << endl;
				for (int i = 0; i < 52; i++)
				{
					input << reservation.seats[i][0] << endl;
					input << reservation.seats[i][1] << endl;
				}
				for (int i = 0; i < 5; i++)
				{
					input << reservation.tickets[i] << endl;
				}
				input << reservation.isBusHire << endl;
			}
			getline(output, reservation.name);
		}
	}

	input.close();
	output.close();
	remove("./ReservationInput.txt");
	rename("./ReservationTemp.txt", "./ReservationInput.txt");

}

void Reservation::CancelReservationByBusByDate(long BusID, Date date)
{
	ifstream output;

	output.open("./ReservationInput.txt", ios::in);


	ofstream input;

	input.open("./ReservationTemp.txt", ios::out);
	if (output.is_open()) 
	{

		Reservation reservation = Reservation();
		string DateOfTravel;

		while (getline(output, reservation.name))
		{
			//Gets string objects from file using getline() and other objects directly through >> 
			//to prevent memory access violations sometimes caused by reading strings
			getline(output, reservation.address);
			getline(output, reservation.contactNumber);
			getline(output, reservation.email);
			getline(output, DateOfTravel);
			getline(output, reservation.destination);
			getline(output, reservation.busType);
			output >> reservation.busID;
			for (int i = 0; i < 52; i++)
			{
				output >> reservation.seats[i][0];
				output >> reservation.seats[i][1];
			}
			for (int i = 0; i < 5; i++)
			{
				output >> reservation.tickets[i];
			}
			output >> reservation.isBusHire;

			//If passed name, day, and reason for transaction are the same, the record is found
			if (BusID == reservation.busID && DateOfTravel.compare(date.toString()) == 0)
			{
				reservation.dateOfTravel = date;
				
				Scheduling trip = Scheduling();
				trip.findTrip(reservation.busID, reservation.destination, reservation.busType, reservation.dateOfTravel);
				if (trip.getBusID() != -1)
				{
					for (int i = 0; i < 52; i++)
					{
						if (reservation.seats[i][0] != -1)
						{
							trip.resetSeat(reservation.seats[i][0] + 1, reservation.seats[i][1]);
						}
					}

					trip.saveTrip();

					Rates().SaveTransaction(reservation, reservation.GetDestination(reservation.destination), reservation.GetBusType(reservation.busType), Reasons[3]);

				}
				else
				{
					cout << "Sorry, unable to cancel reservations.\n";
				}
				
			}
			else
			{
				input << reservation.name << endl;
				input << reservation.address << endl;
				input << reservation.contactNumber << endl;
				input << reservation.email << endl;
				input << DateOfTravel << endl;
				input << reservation.destination << endl;
				input << reservation.busType << endl;
				input << reservation.busID << endl;
				for (int i = 0; i < 52; i++)
				{
					input << reservation.seats[i][0] << endl;
					input << reservation.seats[i][1] << endl;
				}
				for (int i = 0; i < 5; i++)
				{
					input << reservation.tickets[i] << endl;
				}
				input << reservation.isBusHire << endl;
			}
			getline(output, reservation.name);
		}

		input.close();
		output.close();
		remove("./ReservationInput.txt");
		rename("./ReservationTemp.txt", "./ReservationInput.txt");
		Scheduling().CancelReservationByBusByDate(BusID, date);
	}
}
