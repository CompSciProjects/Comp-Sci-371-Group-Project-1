#include <iostream>
#include "Administration.h"
using namespace std;

/*Administrator is engaged in different administration tasks such as add a bus to the fleet, 
view weekly sales,  manage  reservations  including  view/edit  and  cancel  reservation  by  day  and  by  vehicle. 
Some of the administrator’s tasks are listed below:

•Add vehicle to the fleet

•View reservation by bus by date (current day or future days)

•Edit reservation (change passenger’s name, modify charge) 

•Change reservation charge, hire charge

•View income by date and by vehicle*/


void Admin::AdminMenu()
{
	int option = 0;
	cout << "Administration Menu\n\n";

	//Allows the user to choose an Admin task or exit the Admin menu
	while (option != 6)
	{
		cout << "1. Add vehicle to the fleet\n"
			<< "2. View reservation by bus by date (current day or future days)\n"
			<< "3. Edit reservation (change passenger’s name, modify charge)\n"
			<< "4. Change reservation charge or hire charge\n"
			<< "5. View income by date and by vehicle\n"
			<< "6. Exit\n"
			<< "Please select an option 1 through 6:";
		cin >> option;
		cout << "\n";

		switch (option)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			cout << "Exiting the Administration Menu. Redirecting back to main menu.\n\n";
			break;
		default:
			cout << "That is not a valid option.\n\n";
			break;
		}
	}
}
