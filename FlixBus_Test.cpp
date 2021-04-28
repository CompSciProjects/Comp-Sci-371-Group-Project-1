#include "Administration.h"
#include "Reservation.h"
#include <iostream>
using namespace std;

int main()
{
	int option = 0;

	cout << "Welcome to the FlixBus automated system!\n\n";
	
	//Allows user to choose a menu option or exit the system
	while(option != 3)
	{
		
		cout << "1. Administrator Menu\n"
			<< "2. Customer Menu\n"
			<< "3. Exit\n"
			<< "Please select an option 1, 2, or 3:";
		cin >> option;
		cout << "\n";

		switch (option)
		{
		case 1:
			Admin().AdminMenu();
			break;
		case 2:
			Reservation().CustomerMenu();
			break;
		case 3:
			cout << "Thank you for using the FlixBus automated system! Goodbye!\n\n";
			break;
		default:
			cout << "That is not a valid option.\n\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}

	return 0;
}
