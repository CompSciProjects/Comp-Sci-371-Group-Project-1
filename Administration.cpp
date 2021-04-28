#include <iostream>
#include "Administration.h"
#include "Scheduling.h";
#include "Rates.h"
#include "Date.h"
#include <time.h>
using namespace std;

double inputValidation(double num)
{
	if (num < 0)
	{
		while (num < 0)
		{
			cout << "That is not a valid entry.\n"
				<< "Please enter a number greater than 0: ";

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> num;
		}
	}
	return num;
}

void Admin::AdminMenu()
{
	try
	{
		int option = 0;
		Date date;
		long id;
		string resName = "";
		cout << "Administration Menu\n\n";

		//Allows the user to choose an Admin task or exit the Admin menu
		while (option != 8)
		{
			cout << "Please select an option 1 through 6:\n"
				<< "1. Add vehicle to the fleet\n"
				<< "2. View reservation by bus by date (current day or future days)\n"
				<< "3. Edit reservation (change passenger's name, modify charge)\n"
				<< "4. Cancel reservations\n"
				<< "5. Change reservation charge or hire charge\n"
				<< "6. View income by date and by vehicle\n"
				<< "7. Check weekly sales\n"
				<< "8. Exit\n";
			cin >> option;
			cout << "\n";

			switch (option)
			{
			case 1: //adds a new vehicle to the fleet
				AddVehicles();
				break;
			case 2: //view a reservation by vehicle and by date
				date = EnterDate();
				id = Scheduling().getBusIDList();
				Reservation().ViewReservationByBusAndDate(id, date);
				break;
			case 3: //edit a reservation (change name and charge)
				cout << "Enter the date of the specific trip you would like to edit.\n";
				date = EnterDate();
				EditReservation(date);
				break;
			case 4: //cancel reservations
				date = EnterDate();
				id = Scheduling().getBusIDList();
				Reservation().CancelReservationByBusByDate(id, date);
				break;
			case 5: //change reservation charge prices
				ChangeReservationCharge();
				break;
			case 6: //view income by date and vehicle type
				date = EnterDate();
				id = Scheduling().getBusIDList();
				Reservation().ViewIncomeByBusByDate(id, date);
				break;
			case 7: //display weekly sales
				date = EnterDate();
				Rates().CheckWeeklySales(date);
				break;
			case 8:
				cout << "Exiting the Administration Menu. Redirecting back to the Main Menu.\n\n";
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

void Admin::AddVehicles()
{

	int vOption = 0;
	while (vOption != 4)
	{
		cout << "Which type of vehicle would you like to add?\n"
			<< "1. Luxury Bus\n"
			<< "2. MiniBus\n"
			<< "3. Minivan\n"
			<< "4. None, finish adding vehicles\n\n";
		cin >> vOption;
		switch (vOption) {
		case 1: //add a luxury bus
			cout << "1 new luxury bus added!\n";
			Scheduling().addVehicle(vOption - 1);
			cout << "Total luxury buses: " << Scheduling().getBusCount(vOption - 1) << "\n\n";
			break;
		case 2: //add a MiniBus
			cout << "1 new minibus added!\n";
			Scheduling().addVehicle(vOption - 1);
			cout << "Total mini-buses: " << Scheduling().getBusCount(vOption - 1) << "\n\n";
			break;
		case 3: //add a Minivan
			cout << "1 new minivan added!\n";
			Scheduling().addVehicle(vOption - 1);
			cout << "Total minivans: " << Scheduling().getBusCount(vOption - 1) << "\n\n";
			break;
		case 4: //return to admin menu
			cout << "Returning to Administration Menu.\n\n";
			break;
		default:
			cout << "That is not a valid option.\n\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
	vOption = 0;
}

void Admin::EditReservation(Date date)
{
	cout << "What would you like to edit?\n"
		<< "1. Name\n"
		<< "2. Charge\n";
	int num;
	cin >> num;

	if (num == 1)
	{
		cout << "Enter name the reservation you would like to edit is under.\n";
		string name;
		cin.ignore();
		getline(cin, name);

		cout << "Enter the new name you would like on the reservation.\n";
		string newName;
		cin.ignore(0, EOF);
		getline(cin, newName);
		Reservation reservation = Reservation();
		reservation = Reservation().GetReservation(name, date);
		if (reservation.GetName().compare("") != 0)
		{
			Rates().ChangeTransactionName(reservation, newName);
			reservation.ChangeReservationName(name, date, newName);
		}
		else
		{
			cout << "Sorry, the reservation was not found with the given name and date.\n\n";
		}
	}
	else if (num == 2)
	{
		cout << "Enter name the reservation you would like to edit is under.\n";

		string name;
		cin.ignore();
		getline(cin, name);
		double amount;
		cout << "Enter the new charge you would like on the reservation.\n";
		cin >> amount;
		amount = inputValidation(amount);
		Reservation reservation = Reservation().GetReservation(name, date);
		if (reservation.GetName().compare("") != 0)
		{
			Rates().ChangeReservationCharge(reservation, amount);
		}
		else
		{
			cout << "Sorry, the reservation was not found with the given name and date.\n\n";
		}
		
	}
	else
	{
		cout << "That is not a valid selection.\n";
	}
}

void Admin::ChangeReservationCharge()
{
	int vOption = 0;
	while (vOption != 3) 
	{
		cout << "Which would you like to change?\n"
			<< "1. Seat Reservation Charge\n"
			<< "2. Bus Hire Charge\n"
			<< "3. Return to Administration Menu\n";
		cin >> vOption;
		switch (vOption) 
		{
		case 1: //change seat reservation charge
			cout << "Which vehicle would you like to change the seat charge for?\n"
				<< "1. Luxury Bus Seats\n"
				<< "2. MiniBus Seats\n"
				<< "3. MiniVan Seats\n"
				<< "4. Return to Administration Menu.\n";
			cin >> changeChoice;
			if (changeChoice == 1) 
			{
				cout << "Please enter the new charge rate for window/aisle seats: \n";
				cin >> changeAmountWindow;
				cout << "Please enter the new charge rate for regular seats: \n";
				cin >> changeAmount;
				Rates().setLuxSeatRate(changeAmountWindow, changeAmount);
				cout << "New Luxury window/aisle seat rate: " << Rates().getLuxSeatRateWindow() << "\n"
					<< "New Luxury regular seat rate: " << Rates().getLuxSeatRate() << "\n\n";
			}
			else if (changeChoice == 2) 
			{
				cout << "Please enter the new charge rate for MiniBus seats: \n";
				cin >> changeAmount;
				Rates().setMiniBusSeatRate(changeAmount);
				cout << "New MiniBus seat charge rate: " << Rates().getMiniBussSeatRate() << "\n\n";
			}
			else if (changeChoice == 3) 
			{
				cout << "Please enter the new charge rate for MiniVan seats: \n";
				cin >> changeAmount;
				Rates().setMiniVanSeatRate(changeAmount);
				cout << "New MiniVan seat charge rate: " << Rates().getMiniVanSeatRate() << "\n\n";
			}
			else if (changeChoice == 4) 
			{
				cout << "Returning to Administration Menu\n\n";
			}
			else 
			{
				cout << "Invalid selection! Returning to Administration Menu.\n\n";
			}
			break;
		case 2: //change bus hire charge
			cout << "For which vehicle would you like to change the Bus rental prices?\n"
				<< "1. Luxury Bus\n"
				<< "2. MiniBus\n"
				<< "3. MiniVan\n"
				<< "4. Return to Administration Menu.\n";
			cin >> changeChoice;
			if (changeChoice == 1) 
			{
				cout << "Please enter the new flat rental charge: \n";
				cin >> changeAmount;
				changeAmount = inputValidation(changeAmount);
				cout << "Please enter the new milage cost: \n";
				cin >> mileCost;
				mileCost = inputValidation(mileCost);
				cout << "Please enter the new security deposit cost: \n";
				cin >> secDeposit;
				secDeposit = inputValidation(secDeposit);
				Rates().setLuxBusRate(changeAmount, mileCost, secDeposit);
			}
			else if (changeChoice == 2) 
			{
				cout << "Please enter the new flat rental charge: \n";
				cin >> changeAmount;
				changeAmount = inputValidation(changeAmount);
				cout << "Please enter the new milage cost: \n";
				cin >> mileCost;
				mileCost = inputValidation(mileCost);
				cout << "Please enter the new security deposit cost: \n";
				cin >> secDeposit;
				secDeposit = inputValidation(secDeposit);
				Rates().setMiniBusRate(changeAmount, mileCost, secDeposit);
			}
			else if (changeChoice == 3) 
			{
				cout << "Please enter the new flat rental charge: \n";
				cin >> changeAmount;
				changeAmount = inputValidation(changeAmount);
				cout << "Please enter the new milage cost: \n";
				cin >> mileCost;
				mileCost = inputValidation(mileCost);
				cout << "Please enter the new security deposit cost: \n";
				cin >> secDeposit;
				secDeposit = inputValidation(secDeposit);
				Rates().setMiniVanRate(changeAmount, mileCost, secDeposit);
			}
			else if (changeChoice == 4) 
			{
				cout << "Returning to Administration Menu\n\n";
			}
			else 
			{
				cout << "Invalid selection! Returning to Administration Menu.\n\n";
			}
			break;
		case 3:
			cout << "Returning to Administration Menu\n";
			break;
		default:
			cout << "That is not a valid option.\n\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
	vOption = 0;
}

Date Admin::EnterDate()
{
	struct tm newtime;
	time_t ttime = time(0);
	localtime_s(&newtime, &ttime);
	int CurrentYear = newtime.tm_year + 1900;
	int Month;
	int Day;
	cout << "Please enter the month number: ";
	cin >> Month;
	while (Month < 1 || Month > 12)
	{
		cout << "That Month is not valid. \n"
			<< "Please enter the month number: ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> Month;
	}
	cout << "Please enter the day: ";
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
				cout << "The day you entered is not valid.\n";
				cout << "Please enter the day: ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
				cout << "The day you entered is not valid.\n";
				cout << "Please enter the day: ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> Day;
			}
		}
		break;
	case 2:
		bool leapYear;
		if (CurrentYear % 4 == 0)
		{
			leapYear = true;
		}
		else
		{
			leapYear = false;
		}

		if (Day < 1 || ((leapYear) ? Day > 29 : Day > 28))
		{
			while (Day < 1 || ((leapYear) ? Day > 29 : Day > 28))
			{
				cout << "The day you entered is not valid.\n";
				cout << "Please enter the day: ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> Day;
			}
		}
		break;
	}

	return Date(Month, Day, CurrentYear);
}
