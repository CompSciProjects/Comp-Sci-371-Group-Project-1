#include "Reservation.h"
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

void Reservation::CustomerMenu()
{
	int option = 0;

	cout << "Customer Menu\n\n";

	//Allows the user to choose an Admin task or exit the Admin menu
	while (option != 4)
	{
		cout << "1. Reserve seat(s)\n"
			<< "2. Hire a bus\n"
			<< "3. Cancel Reservation\n"
			<< "4. Exit\n"
			<< "Please select an option 1 through 4:";
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
			cout << "Exiting the Customer Menu. Redirecting back to main menu.\n\n";
			break;
		default:
			cout << "That is not a valid option.\n\n";
			break;
		}
	}
}
