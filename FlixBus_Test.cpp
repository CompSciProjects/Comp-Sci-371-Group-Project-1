#include "Administration.h"
#include "Reservation.h"
#include <iostream>
using namespace std;

/*A  local  bus  company  “FlixBus”  wants  to  hire  you  to  automate  their  processes.  
These  include  the  ticketing, reservation, routing, customer service, resource management and administration. 
The bus company has three different type vehicles: (1) luxury bus (2) mini bus, and (3) minivan. 
There are 3 luxury buses, 4 small buses and 4 minivans. The luxury bus has 52 seats (2x11 seats and 3x10 seats), 
the small bus has 36 seats (1x12 and 2x12) and the minivan has 12 seats (3x4). This means in case of the minivan, 
there are 3 seats in each of the 4 rows, in case of the small bus, there is a column of 1 seat  
and  a  column  of  two  seats  in  12  rows,  and  finally,  in  case  of  the  luxury  bus,  
there  are  10  rows  with 2  columns  of  seat.  One  column  has  2  seats  and  the  other  column  has  3  seats.  
The  rows  in  the  buses are alphabetically numbered. 
Thus, the A and C mark the window seats in all kinds of vehicles. 
However, the B and E are the aisle seats in the luxury bus, B and D are the aisle seats marked in the minibus 
whereas in the minivan, there is no aisle seat. The buses haul passengers to and from Green Bay  from/to  the  following  routes.  
The  buses  are  identified  by  unique  identifier  and  have  their  registration details stored including a list of drivers who drive them. 
A single driver can drive multiple buses. 

Source		Destination		Distance
Green Bay	Madison			135.6 miles
Green Bay	Milwaukee		118.7 miles
Green Bay	Whitewater		142.2 miles
Green Bay	Oshkosh			50.4 miles
Green Bay	Eau Claire		194.4 miles*/

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
			Admin admin;
			admin.AdminMenu();
			break;
		case 2:
			Reservation customer;
			customer.CustomerMenu();
			break;
		case 3:
			cout << "Thank you for using the FlixBus automated system! Goodbye!\n\n";
			break;
		default:
			cout << "That is not a valid option.\n\n";
			break;
		}
	}

	return 0;
}
