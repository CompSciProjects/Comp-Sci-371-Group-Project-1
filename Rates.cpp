#include "Rates.h"
#include <iostream>
#include <ctime>
#include "Reservation.h"
using namespace std;

/*The bus company has three different type vehicles: (1) luxury bus (2) mini bus, and (3) minivan. 
There are 3 luxury buses, 4 small buses and 4 minivans. The luxury bus has 52 seats (2x11 seats and 3x10 seats), 
the small bus has 36 seats (1x12 and 2x12) and the minivan has 12 seats (3x4).
In  luxury  bus,  the aisle  and  window  seat  costs   $0.95  per  mile,  and the other seat  costs  $0.75 per mile. 
In small bus, both the aisle seat and window seat costs 0.65. In case of the minivan, each seat cost $0.50 per  mile.  
In  case  of  bus  hire,  the  luxury  bus  cost  $1500 as rent with additional $0.25 for each  mile  of travel.  
The  small  bus  costs   $1300  as  rent  with  additional  $0.20  per  mile  whereas  the minivan  costs  $1000  
as  rent  with  additional  $0.15  per  mile.  
The  security  deposit  for  luxury  bus  is  $5000,   for  the  small  bus  $3000  and  for  the  minivan  it  is  $1500  
which  will  be  reimbursed  upon returning the  vehicle.  
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
Green Bay	Eau Claire		194.4 miles
For  each  ticket  and  bus  hire  is  subject  to  government  tax  of  10%  which  can  change  periodically.  
The  company  wants  to  profit  25%  on  all  ticket  sales  and  hire.  Remember  that the  security  deposit  is  not  taxable.  
Passengers’   refunds  are  also  taxable.  
All  sales  need  to  store  permanently in file(s) so that they can retrieve later for administration tasks.*/

double Rates::GetRate(int* Tickets, int BusType, bool IsBusHire) //Method totals up rates for all tickets purchased
{

    double ticketAmount = 0;
    switch (BusType)
    {
    case 0: //Case of Luxury Bus
        for (int i = 0; i < 5; i++)
        {
            if (i != 4 && IsBusHire) //If tickets are for aisle or window seat with Bus Hire
            {
                ticketAmount += (Tickets[i] * LUXURYAISLEANDWINDOW) + (Tickets[i] * LUXURYBH[1]);
            }
            else if (i == 4 && IsBusHire)
            {
                ticketAmount += (Tickets[i] * LUXURYOTHER) + (Tickets[i] * LUXURYBH[1]);
            }
            else if (i != 4) //If tickets are for aisle or window seat
            {
                ticketAmount += (Tickets[i] * LUXURYAISLEANDWINDOW);
            }
            else
            {
                ticketAmount += (Tickets[i] * LUXURYOTHER);
            }
        }
        break;
    case 1: //Case of Mini Bus
        for (int i = 0; i < 5; i++)
        {
            if (IsBusHire) //If tickets were purchased with bus hire
            {
                ticketAmount += (Tickets[i] * MINIBUSSEAT) + (Tickets[i] * MINIBUSBH[1]);
            }
            else           //If tickets were purchased without bus hire
            {
                ticketAmount += (Tickets[i] * MINIBUSSEAT);
            }
        }
        break;
    case 2: //Case of Minivan
        for (int i = 0; i < 5; i++)
        {
            if (IsBusHire) //If tickets were purchased with bus hire
            {
                ticketAmount += (Tickets[i] * MINIVANSEAT) + (Tickets[i] * MINIVANBH[1]);
            }
            else           //If tickets were purchased without bus hire
            {
                ticketAmount += (Tickets[i] * MINIVANSEAT);
            }
            
        }
        break;
    default: 
        break;
    }
    return ticketAmount;
}

double Rates::GetRentalFee(bool IsBusHire, int BusType) //Method finds the rental fee if applicable
{
    double fee = 0;
    if (IsBusHire)
    {
        switch (BusType)
        {
        case 0: //Case of Luxury Bus
            fee = LUXURYBH[0];
            break;
        case 1: //Case of Minibus
            fee = MINIBUSBH[0];
            break;
        case 2: //Case of Mini van
            fee = MINIVANBH[0];
            break;
        default:
            break;
        }
    }
    return fee;
}

double Rates::GetDeposit(bool IsBusHire, int BusType)
{
    double deposit = 0;
    if (IsBusHire) 
    {
        switch (BusType)
        {
        case 0: //Case of Luxury Bus
            deposit = LUXURYBH[2];
            break;
        case 1: //Case of Minibus
            deposit = MINIBUSBH[2];
            break;
        case 2: //Case of Mini van
            deposit = MINIVANBH[2];
            break;
        default:
            break;
        }
    }
    return deposit;
}

double Rates::GetPenalty(Date Day, string Reason) //Method finds penalty if the transaction reason is a cancellation
{
    double penalty = 0;
    
    if (Reason.compare(Reasons[2]) == 0) //Checks if reason for transaction is cancellation
    {
        //Section gets current day and time, put into newtime
        struct tm newtime;
        time_t ttime = time(0);
        localtime_s(&newtime, &ttime);

        //Initializes the date in newtime to an object of Date, which can be used to compare date for the tickets
        Date CurrentDate(1900 + newtime.tm_year, 1 + newtime.tm_mon, newtime.tm_mday);
        int DaysBefore;

        //Checks if trip is within 7 of now 
        for (DaysBefore = 0; DaysBefore < 7; DaysBefore++)
        {
            if (CurrentDate.toString().compare(Day.toString()) == 0)
            {
                break;
            }
            CurrentDate.nextDay();
        }

        if (DaysBefore == 0) // cancel  reservation  one  day  before the trave including one minute before the travel will forfeit the entire cost of the ticket.
        {
            penalty = 1;
        }
        else if (DaysBefore == 7) //if DaysBefore is 7, the day of the trip is not within the timeframe for penalty
        {
            penalty = 0;
        }
        else //Cancellation  shorter  than  a  week  will  require  30%  penalty.
        {
            penalty = 0.3;
        }

    }
    return penalty;
}

double Rates::GetAmount(Rates Rates, bool IsBusHire, int BusType) //Method takes values from transaction to calculate total amount
{
    double amount = 0;
    
    if (Rates.reason.compare(Reasons[2]) == 0) //If reason for transaction is refund, 
    {
        //amount is negative due to giving money back to customer
        //penalty amount is taken out of deposit (if applicable)
        //takes rate times distance plus rental fee and takes out penalty (if applicable)
        //tax is subtracted from (rate times distance plus rental fee)  but not the deposit because deposit  is  not  taxable
        amount = -1 * ((Rates.deposit * (1 - Rates.penalty)) + ((((Rates.rate * Rates.distance) + Rates.rentalFee) ) * (1 - Rates.penalty)) - ((((Rates.rate * Rates.distance) + Rates.rentalFee)) * (1 - Rates.penalty) * (Rates.tax - 1)));
    }
    else //If reason besides refund,
    {
        //Add deposit
        //add (rate times distance plus rental fee times tax)
        //deposit is not multiplied by tax because deposit is not taxable 
        amount = Rates.deposit + (((Rates.rate * Rates.distance) + Rates.rentalFee) * Rates.tax);
    }
    return amount;
}

void Rates::SaveTransaction(Reservation Reservation, int Destination, int BusType, string Reason) //Writes transaction information to file
{
    try
    {
        fstream input;

        //Opens file containing transactions
        input.open("./RatesInput.txt", ios::app);

        if (input.is_open()) //Only try to save to file if file opened properly
        {
            //Region calculates and stores necessary information into object transaction
            Rates transaction = Rates();
            transaction.name = Reservation.GetName();
            transaction.day = Reservation.GetDateOfTravel();
            transaction.distance = Distances[Destination];

            int* seats = Reservation.GetTickets();
            int seatTickets = 0;
            transaction.rate = this->GetRate(seats, BusType, Reservation.IsBusHire());
            for (int i = 0; i < 5; i++)
            {
                seatTickets += seats[i];
            }
            transaction.tickets = seatTickets;
            transaction.rentalFee = this->GetRentalFee(Reservation.IsBusHire(), BusType);
            transaction.deposit = this->GetDeposit(Reservation.IsBusHire(), BusType);
            transaction.penalty = this->GetPenalty(Reservation.GetDateOfTravel(), Reason);
            transaction.reason = Reason;
            transaction.amount = this->GetAmount(transaction, Reservation.IsBusHire(), BusType);
            //End region for calculating and saving necessary information into object transaction

            //writes the data gathered above into the file
            input << transaction.name << endl;
            input << transaction.day.toString() << endl;
            input << transaction.distance << endl;
            input << transaction.rate << endl;
            input << transaction.tickets << endl;
            input << transaction.rentalFee << endl;
            input << transaction.deposit << endl;
            input << transaction.penalty << endl;
            input << transaction.amount << endl;
            input << transaction.reason << endl;

            //closes the file
            input.close();

            this->PrintTransaction(transaction);
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

bool Rates::FindTransaction(string Name, Date Day, string Reason)
{
    bool isFound = false;

    ifstream output;

    //Opens file containing transactions
    output.open("./RatesInput.txt", ios::in);
    if (output.is_open()) //Only try to read from file if file opened properly
    {
        //variables section for temporarily storing the data read from the file
        string Name2;
        string Day2;
        double Distance;
        double Rate;
        int Tickets;
        double RentalFee;
        double Deposit;
        double Penalty;
        double Amount;
        string Reason2;

        while (getline(output, Name2)) //Gets name on the transaction 
        {
            //Gets string objects from file using getline() and other objects directly through >> 
            //to prevent memory access violations sometimes caused by reading strings
            getline(output, Day2);
            output >> Distance >> Rate >> Tickets >> RentalFee >> Deposit >> Penalty >> Amount;
            getline(output, Reason2);
            getline(output, Reason2);

            //If passed name, day, and reason for transaction are the same, the record is found
            if (Name2.compare(Name) == 0 && Day2.compare(Day.toString()) == 0 && Reason2.compare(Reason) == 0)
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

Rates Rates::GetTransaction(string Name, Date Day, string Reason) //Reads the transaction information from a file
{
    try
    {
        ifstream output;

        //Opens file containing transactions
        output.open("./RatesInput.txt", ios::in);
        if (output.is_open()) //Only try to read from file if file opened properly
        {
            Rates transaction = Rates();

            //variables section for temporarily storing the data read from the file
            string Name2;
            string Day2;
            double Distance = -1;   //Set to -1 as a check for if the transaction is not found
            double Rate;
            int Tickets;
            double RentalFee;
            double Deposit;
            double Penalty;
            double Amount;
            string Reason2;

            while (getline(output, Name2)) //Gets name on the transaction 
            {
                //Gets string objects from file using getline() and other objects directly through >> 
                //to prevent memory access violations sometimes caused by reading strings
                getline(output, Day2);
                output >> Distance >> Rate >> Tickets >> RentalFee >> Deposit >> Penalty >> Amount;
                getline(output, Reason2); //getline buffer because switching between getting a number and a string adds a blank line when reading from file
                getline(output, Reason2);

                //If passed name, day, and reason for transaction are the same, the record is found and print the record
                if (Name2.compare(Name) == 0 && Day2.compare(Day.toString()) == 0 && Reason2.compare(Reason) == 0)
                {
                    transaction.name = Name;
                    transaction.day = Day;
                    transaction.distance = Distance;
                    transaction.rate = Rate;
                    transaction.tickets = Tickets;
                    transaction.rentalFee = RentalFee;
                    transaction.deposit = Deposit;
                    transaction.penalty = Penalty;
                    transaction.amount = Amount;
                    transaction.reason = Reason;
                    break; //break when record is found
                }
            }

            //closes the file
            output.close();

            return transaction;
        }
    }
    catch(exception e)
    {
        cout << "Sorry, there has been an issue accessing the file with your records. Please try again later.\n\n";
    }
}

void Rates::PrintTransaction(Rates Transaction)
{
    cout << "Transaction Details\n\n"
        << "Name: " << Transaction.name << "\n"
        << "Day: " << Transaction.day.toString() << "\n"
        << "Distance: " << Transaction.distance << "\n"
        << "Rate: $" << Transaction.rate << " per mile (When totaling all tickets)\n"
        << "Rental Fee: $" << Transaction.rentalFee << "\n"
        << "Deposit: $" << Transaction.deposit << "\n"
        << "Penalty: " << (int)(Transaction.penalty * 100) << "%\n"
        << "Tax: " << (int)((Transaction.tax - 1) * 100) << "%\n"
        << "Amount: $" << Transaction.amount << "\n"
        << "Reason: " << Transaction.reason << "\n\n";
}
