#include <iostream>
#include "Administration.h"
#include "Scheduling.h";
#include "Rates.h"
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
	int vOption = 0;
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
			while (vOption != 4) {
				cout << "Which type of vehicle would you like to add?\n"
					<< "1. Luxury Bus\n"
					<< "2. MiniBus\n"
					<< "3. Minivan\n"
					<< "4. None, finish adding vehicles\n\n";
				cin >> vOption;
				switch (vOption) {
				case 1: //add a luxury bus
					cout << "1 new luxury bus added!\n";
					Scheduling().addLuxuryBus();
					luxBusNum = Scheduling().getLuxuryBusTotal();
					cout << "Total luxury buses: " << luxBusNum << "\n\n";
					break;
				case 2: //add a MiniBus
					cout << "1 new minibus added!\n";
					Scheduling().addMiniBus();
					miniBusNum = Scheduling().getMiniBusTotal();
					cout << "Total mini-buses: " << miniBusNum << "\n\n";
					break;
				case 3: //add a Minivan
					cout << "1 new minivan added!\n";
					Scheduling().addMiniVan();
					miniVanNum = Scheduling().getMiniVanTotal();
					cout << "Total minivans: " << miniVanNum << "\n\n";
					break;
				case 4: //return to admin menu
					cout << "Returning to Administration Menu.\n\n";
					break;
				default:
					cout << "That is not a valid option.\n\n";
					break;
				}
			}
			vOption = 0;
			break;
		case 2: //view a reservation by vehicle and by date
			//ask for date and vehicle type
			//call a modified version of "FindReservation" from Reservation.cpp
			//print all reservations held by specified vehicle type on that date
			break;
		case 3: //edit a reservation (change name and charge)
			//ask for name, month, day, and what kind of reservation (seat or bus)
			//store in local variables
			//ask what they'd like to change (name, charge amnt, more?) and store
			//call Reservation().CancelReservation();
			//call method to add new registration with updated data (modified seat/busHire)
			break;
		case 4: //cancel reservations
			//ask type
			//call
			break;
		case 5: //change reservation charge prices
			while (vOption != 3) {
				cout << "Which would you like to change?\n"
					<< "1. Seat Reservation Charge\n"
					<< "2. Bus Hire Charge\n"
					<< "3. Return to Administration Menu\n";
				cin >> vOption;
				switch (vOption) {
				case 1: //change seat reservation charge
					cout << "Which vehicle would you like to change the seat charge for?\n"
						<< "1. Luxury Bus Seats\n"
						<< "2. MiniBus Seats\n"
						<< "3. MiniVan Seats\n"
						<< "4. Return to Administration Menu.\n";
					cin >> changeChoice;
					if (changeChoice == 1) {
						cout << "Please enter the new charge rate for window/aisle seats: \n";
						cin >> changeAmountWindow;
						cout << "Please enter the new charge rate for regular seats: \n";
						cin >> changeAmount;
						Rates().setLuxSeatRate(changeAmountWindow, changeAmount);
						cout << "New Luxury window/aisle seat rate: " << Rates().getLuxSeatRateWindow() << "\n"
							<< "New Luxury regular seat rate: " << Rates().getLuxSeatRate() << "\n\n";
					}
					else if (changeChoice == 2) {
						cout << "Please enter the new charge rate for MiniBus seats: \n";
						cin >> changeAmount;
						Rates().setMiniBusSeatRate(changeAmount);
						cout << "New MiniBus seat charge rate: " << Rates().getMiniBussSeatRate() << "\n\n";
					}
					else if (changeChoice == 3) {
						cout << "Please enter the new charge rate for MiniVan seats: \n";
						cin >> changeAmount;
						Rates().setMiniVanSeatRate(changeAmount);
						cout << "New MiniVan seat charge rate: " << Rates().getMiniVanSeatRate() << "\n\n";
					}
					else if (changeChoice == 4) {
						cout << "Returning to Administration Menu\n\n";
					}
					else {
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
					if (changeChoice == 1) {
						cout << "Please enter the new flat rental charge: \n";
						cin >> changeAmount;
						cout << "Please enter the new milage cost: \n";
						cin >> mileCost;
						cout << "Please enter the new security deposit cost: \n";
						cin >> secDeposit;
						Rates().setLuxBusRate(changeAmount, mileCost, secDeposit);
					}
					else if (changeChoice == 2) {
						cout << "Please enter the new flat rental charge: \n";
						cin >> changeAmount;
						cout << "Please enter the new milage cost: \n";
						cin >> mileCost;
						cout << "Please enter the new security deposit cost: \n";
						cin >> secDeposit;
						Rates().setMiniBusRate(changeAmount, mileCost, secDeposit);
					}
					else if (changeChoice == 3) {
						cout << "Please enter the new flat rental charge: \n";
						cin >> changeAmount;
						cout << "Please enter the new milage cost: \n";
						cin >> mileCost;
						cout << "Please enter the new security deposit cost: \n";
						cin >> secDeposit;
						Rates().setMiniVanRate(changeAmount, mileCost, secDeposit);
					}
					else if (changeChoice == 4) {
						cout << "Returning to Administration Menu\n\n";
					}
					else {
						cout << "Invalid selection! Returning to Administration Menu.\n\n";
					}
					break;
				case 3:
					cout << "Returning to Administration Menu\n";
					break;
				default:
					cout << "That is not a valid option.\n\n";
					break;
				}
			}
			vOption = 0;
			break;
		case 6: //view income by date and vehicle type
			//ask for date and vehicle type
			//call a modified version of "FindReservation" from Reservation.cpp
			//store all reservations held by specified vehicle type on that date
			//multiply reservations by their corrosponding rates
			//sum charges for specified vehicle and print
			break;
		case 7: //display weekly sales
			//Scheduling stores week of registration?
			break;
		case 8:
			cout << "Exiting the Administration Menu. Redirecting back to the Main Menu.\n\n";
			break;
		default:
			cout << "That is not a valid option.\n\n";
			break;
		}
	}
}
