#include "Reservation.h"
#include "Rates.h"
#include "Date.h"
#include <iostream>
using namespace std;

/*Passengers  can  reserve  seats  2  weeks  in  advance.  
Reservation  requires passenger’s biographical information  including
name,  address,  contact  number,  email  address,  date  of  travel  and  how  many  tickets.  
Passengers  can  cancel  reservation  one  week  before  the  travel  however  any  cancellation  
shorter  than  a  week  will  require  30%  penalty.
If  a  passenger  wants  to  cancel  reservation  one  day  before the trave including one minute 
before the travel will forfeit the entire cost of the ticket. 
If the travel is cancelled by the company, passengers will get full refund. 
The company reserves the rights to  cancel  any  travel  with  prior  notice  at  2  days  ahead  of  the  journey.  
The  company  can  reject  any  travel  at  its  discretion.  All  kinds  of  reservation  need  to  store  in  
permanent  file(s)  so  that  they  can  retrieve later for administration tasks.*/

/*The inventory of buses is available for hire for recreational purpose.
Once a customer requests for a bus hire, your responsibility is to check the inventory
of the buses available from the location on the particular  date  requested.  Remember,
bus  hire  is  always  profitable  since  you  can  charge  for  the  all  seats  available  in  the  bus.
So  if  the  number  of  reservations  for  that  bus  is  not  half  full  on  that  particular date,
it is always better to allow for bus hire. The reserving customer hiring the bus should enter  the  same
biographical  information  as  for  normal  ticket  reservation.
All  kinds  of  information  regarding  the   hire   needs   to   store   permanently   in   file(s)
so   that   they   can   retrieve   later   for   administration tasks.*/

string Reservation::GetName()
{
	return this->name;
}

void Reservation::SetDateOfTravel(int Month, int Day, int Year)
{
	this->dateOfTravel.SetMonth(Month);
	this->dateOfTravel.SetDay(Day);
	this->dateOfTravel.SetYear(Year);
}

Date Reservation::GetDateOfTravel()
{
	return this->dateOfTravel;
}

int Reservation::GetDestination(string Destination)
{
	int DestinationNum;
	if (Destination.compare(Destinations[0]) == 0)
	{
		DestinationNum = 0;
	}
	else if (Destination.compare(Destinations[1]) == 0)
	{
		DestinationNum = 1;
	}
	else if (Destination.compare(Destinations[2]) == 0)
	{
		DestinationNum = 2;
	}
	else if (Destination.compare(Destinations[3]) == 0)
	{
		DestinationNum = 3;
	}
	else
	{
		DestinationNum = 4;
	}
	return DestinationNum;
}

int Reservation::GetBusType(string BusType)
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

int* Reservation::GetTickets()
{
	return this->tickets;
}

bool Reservation::IsBusHire()
{
	return this->isBusHire;
}

void Reservation::CustomerMenu()
{
	int option = 0;

	cout << "Customer Menu";

	//Allows the user to choose an Admin task or exit the Admin menu
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
			break;
		}
	}
}

void Reservation::SetGeneralReservationInfo()
{
	string Name;
	string Address;
	string ContactNumber;
	string Email;
	int Month;
	int Day;
	int Year = 2021;
	int Destination;
	int BusType;

	cout << "Please enter your full name: ";
	cin.ignore();
	getline(cin, Name);

	cout << "Please enter your address: ";
	cin.ignore();
	getline(cin, Address);

	cout << "Please enter your phone number: ";
	cin.ignore();
	getline(cin, ContactNumber);

	cout << "Please enter your email address: ";
	cin.ignore();
	getline(cin, Email);

	//THIS SECTION IS ONLY TO TEMPORARILY FILL THE TRIP DETAIL VARIABLES
	//ONCE THE SCHEDULING SECTION IS COMPLETE, THE FUNCTIONS FROM SCHEDULING WILL
	//BE USED TO DETERMINE AVAILABILITY
	cout << "\n\n1. January\n"
		<< "2. February\n"
		<< "3. March\n"
		<< "4. April\n"
		<< "5. May\n"
		<< "6. June\n"
		<< "7. July\n"
		<< "8. August\n"
		<< "9. September\n"
		<< "10. October\n"
		<< "11. November\n"
		<< "12. December\n\n";
	cout << "Please enter the month in which you want to travel corresponding to the numbers above: ";
	cin >> Month;
	if (Month < 1 || Month > 12)
	{
		while (Month < 1 || Month > 12)
		{
			cout << "The month you entered is not valid.\n"
				<< "Please enter the month in which you want to travel corresponding to the numbers above: ";
			cin >> Month;
		}
	}

	cout << "Please enter the day you wish to travel in month " << Month << ": ";
	cin >> Day;
	switch (Month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (Day < 1 || Day > 31)
		{
			while (Day < 1 || Day > 31)
			{
				cout << "The day you entered is not valid for month " << Month << ".\n"
					<< "Please enter the day you wish to travel in month " << Month << " (Days are between 1 and 31): ";
				cin >> Day;
			}
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (Day < 1 || Day > 30)
		{
			while (Day < 1 || Day > 30)
			{
				cout << "The day you entered is not valid for month " << Month << ".\n"
					<< "Please enter the day you wish to travel in month " << Month << " (Days are between 1 and 30): ";
				cin >> Day;
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

		if (Day < 0 || (leapYear) ? Day > 29 : Day > 28)
		{
			while (Day < 0 || (leapYear) ? Day > 29 : Day > 28)
			{
				cout << "The day you entered is not valid for month " << Month << ".\n"
					<< "Please enter the day you wish to travel in month " << Month
					<< " (Days are between 1 and " << ((leapYear) ? 29 : 28) << ": ";
				cin >> Day;
			}
		}
		break;
	}
	

	
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ". " << Destinations[i] << "\n";
	}
	cout << "Please enter which destination you would like to go to on " << Month << "/" << Day << "/" << Year << ": ";
	cin >> Destination;
	while (Destination < 1 || Destination > 5)
	{
		cout << "That is not a valid destination. Valid destinations are 1 through 5.\n"
			<< "Please enter which destination you would like to go to on " << Month << "/" << Day << "/" << Year << ": ";
		cin >> Destination;
	}
	Destination--;

	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << ". " << BusTypes[i] << "\n";
	}
	cout << "Please enter which bus type you would like to use: ";
	cin >> BusType;
	while (BusType < 1 || BusType > 3)
	{
		cout << "That is not a valid bus type. Valid bus types are 1 through 3.\n"
			<< "Please enter which bus type you would like to use: ";
		cin >> BusType;
	}
	BusType--;
	//END SECTION

	this->name = Name;
	this->address = Address;
	this->contactNumber = ContactNumber;
	this->email = Email;
	this->SetDateOfTravel(Month, Day, Year);
	this->destination = Destinations[Destination];
	this->busType = BusTypes[BusType];
}

void Reservation::SeatReservation()
{
	this->SetGeneralReservationInfo();

	int Destination = this->GetDestination(destination);

	int BusType = this->GetBusType(busType);

	int seats[] = { 3,0,4,0,0 }; //THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION

	this->tickets = new int[5];  //THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION
	for (int i = 0; i < 5; i++)	
	{
		this->tickets[i] = seats[i];
	}							//END SECTION
	this->isBusHire = false;

	this->SaveReservation();

	Rates().SaveTransaction(*this, Destination, BusType, Reasons[0]);
}

void Reservation::BusHire()
{
	this->SetGeneralReservationInfo();

	int Destination = this->GetDestination(destination);

	int BusType = this->GetBusType(busType);


	int seats[] = { 3,0,4,0,0 }; //THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION

	this->tickets = new int[5];
	for (int i = 0; i < 5; i++)	//THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION
	{
		this->tickets[i] = seats[i];
	}							//END SECTION
	this->isBusHire = true;

	this->SaveReservation();

	Rates().SaveTransaction(*this, Destination, BusType, Reasons[1]);

}

void Reservation::CancelReservation()
{
	string Name;
	int Month;
	int Day;
	int Year = 2021;

	cout << "Please enter the name under the reservation: ";
	cin.ignore();
	getline(cin, Name);

	cout << "Please enter the month of the reservation as a number (Ex. If April, you enter: 4)";
	cin >> Month;

	cout << "Please enter the day of the reservation: ";
	cin >> Day;
	Date date = Date(Month, Day, Year);
	if (Reservation().FindReservation(Name, date) && (Rates().FindTransaction(Name, date, Reasons[0]) || Rates().FindTransaction(Name, date, Reasons[1])))
	{
		Reservation reservation = Reservation().GetReservation(Name, date);

		Rates().SaveTransaction(reservation, reservation.GetDestination(reservation.destination), reservation.GetBusType(reservation.busType), Reasons[2]);
	}



	//Implementation Needed to delete initial reservation record from file
	

}

void Reservation::SaveReservation()
{
	try
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
			for (int i = 0; i < 5; i++)			//THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION
			{
				input << this->tickets[i] << endl;
			}									//END SECTION
			input << this->isBusHire << endl;

			//closes the file
			input.close();

			this->PrintReservation(*this);
		}
		else
		{
			cout << "There has been an error saving the transaction. Please try again later.\n\n";
		}
	}
	catch (exception e)
	{
		cout << "There has been an error saving the transaction. Please try again later.\n\n";
	}
}

bool Reservation::FindReservation(string Name, Date Day)
{
	bool isFound = false;

	ifstream output;

	//Opens file containing transactions
	output.open("./ReservationInput.txt", ios::in);
	if (output.is_open()) //Only try to read from file if file opened properly
	{
		//variables section for temporarily storing the data read from the file
		string Name2;
		string Address;
		string ContactNumber;
		string Email;
		string DateOfTravel;
		string Destination;
		string BusType;
		int* Tickets = new int[5]; //THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION
		bool IsBusHire;

		while (getline(output, Name2)) //Gets name on the transaction 
		{
			//Gets string objects from file using getline() and other objects directly through >> 
			//to prevent memory access violations sometimes caused by reading strings
			getline(output, Address);
			getline(output, ContactNumber);
			getline(output, Email);
			getline(output, DateOfTravel);
			getline(output, Destination);
			getline(output, BusType);
			for (int i = 0; i < 5; i++)	//THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION
			{
				output >> Tickets[i];
			}							//END SECTION
			output >> IsBusHire;

			//If passed name, day, and reason for transaction are the same, the record is found
			if (Name2.compare(Name) == 0 && DateOfTravel.compare(Day.toString()) == 0)
			{
				isFound = true;
				break; //break when record is found
			}
			else
			{
				isFound = false;
			}
		}

		//closes the file
		output.close();
	}
	else
	{
		cout << "There has been an issue trying to access the file with the records. Please try again later\n\n";
		isFound = false;
	}

	return isFound;

}

Reservation Reservation::GetReservation(string Name, Date Day)
{
	try
	{
		ifstream output;

		//Opens file containing transactions
		output.open("./ReservationInput.txt", ios::in);
		if (output.is_open()) //Only try to read from file if file opened properly
		{

			Reservation reservation = Reservation();
			//variables section for temporarily storing the data read from the file
			string Name2;
			string Address;
			string ContactNumber;
			string Email;
			string DateOfTravel;
			string Destination;
			string BusType;
			int* Tickets = new int[5]; //THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION
			bool IsBusHire;

			while (getline(output, Name2)) //Gets name on the transaction 
			{
				//Gets string objects from file using getline() and other objects directly through >> 
				//to prevent memory access violations sometimes caused by reading strings
				getline(output, Address);
				getline(output, ContactNumber);
				getline(output, Email);
				getline(output, DateOfTravel);
				getline(output, Destination);
				getline(output, BusType);
				for (int i = 0; i < 5; i++) //THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION
				{
					output >> Tickets[i];
				}							//END SECTION
				output >> IsBusHire;

				//If passed name, day, and reason for transaction are the same, the record is found
				if (Name2.compare(Name) == 0 && DateOfTravel.compare(Day.toString()) == 0)
				{
					reservation.name = Name2;
					reservation.address = Address;
					reservation.contactNumber = ContactNumber;
					reservation.email = Email;
					reservation.dateOfTravel = Day;
					reservation.destination = Destination;
					reservation.busType = BusType;
					reservation.tickets = Tickets;
					reservation.isBusHire = IsBusHire;
					break; //break when record is found
				}
			}

			//closes the file
			output.close();

			return reservation;
		}
		else
		{
			cout << "There has been an issue trying to access the file with the records. Please try again later\n\n";
		}
	}
	catch (exception e)
	{
		cout << "Sorry, there has been an issue accessing the file with your records. Please try again later.\n\n";
	}
	
}

void Reservation::PrintReservation(Reservation Reservation)
{
	cout << "Reservation Details\n\n"
		<< "Name: " << this->name << "\n"
		<< "Address: " << this->address << "\n"
		<< "Contact Number: " << this->contactNumber << "\n"
		<< "Email: " << this->email << "\n"
		<< "Date of Travel: " << this->dateOfTravel.toString() << "\n"
		<< "Destination: " << this->destination << "\n"
		<< "Bus Type: " << this->busType << "\n";
		int numTickets = 0;							//THIS SECTION WILL NEED TO CHANGE WITH NEW SCHEDULING IMPLEMENTATION
		for (int i = 0; i < 5; i++)
		{
			numTickets += this->tickets[i];
		}
		cout <<"Tickets: " << numTickets << "\n";	//END SECTION
		cout << ((this->isBusHire)? "This Reservation is for a bus hire." : "This is a personal reservation" ) << "\n\n";
}
