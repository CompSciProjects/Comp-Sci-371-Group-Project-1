#include "Rates.h"
#include <iostream>
#include <ctime>
#include "Reservation.h"
#include <iomanip>
using namespace std;

//seat cost rates
double LUXURYAISLEANDWINDOW = 0.95; //In  luxury  bus, aisle  and  window  seat  costs   $0.95  per  mile
double LUXURYOTHER = 0.75;		  //the other seat  costs  $0.75 per mile
double MINIBUSSEAT = 0.65;		  //In small bus, both the aisle seat and window seat costs 0.65
double MINIVANSEAT = 0.5;				  //In case of the minivan, each seat cost $0.50 per  mile

//Bus Hire rates
double LUXURYBH[3] = { 1500, 0.25, 5000 };   //In  case  of  bus  hire,  the  luxury  bus  cost  $1500 as rent with additional $0.25 for each  mile  of travel. 
                                            //The  security  deposit  for  luxury  bus  is  $5000
double MINIBUSBH[3] = { 1300, 0.2, 3000 };  //The  small  bus  costs   $1300  as  rent  with  additional  $0.20  per  mile
                                            //The  security  deposit for  the  small  bus  $3000 
double MINIVANBH[3] = { 1000, 0.15, 1500 };	    //the minivan  costs  $1000  as  rent  with  additional  $0.15  per  mile
                                            //The security deposit for  the  minivan  it  is  $1500  

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

double Rates::GetDeposit(bool IsBusHire, int BusType) //Method finds deposit amount, if applicable
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
        Date CurrentDate(1 + newtime.tm_mon, newtime.tm_mday, 1900 + newtime.tm_year);
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
    
    if ((Rates.reason.compare(Reasons[2]) == 0) || (Rates.reason.compare(Reasons[3]) == 0)) //If reason for transaction is refund, 
    {
        //amount is negative due to giving money back to customer
        //penalty amount is taken out of deposit (if applicable)
        //takes rate times distance plus rental fee and takes out penalty (if applicable)
        //tax is subtracted from (rate times distance plus rental fee)  but not the deposit because deposit  is  not  taxable
        amount = -1 * ((Rates.deposit * (1 - Rates.penalty)) + ((((Rates.rate * Rates.distance) + Rates.rentalFee) ) 
            * (1 - Rates.penalty)) - ((((Rates.rate * Rates.distance) + Rates.rentalFee)) * (1 - Rates.penalty) * (Rates.tax - 1)));
    }
    else //If reason besides refund or company authorized cancellation,
    {
        //Add deposit
        //add (rate times distance plus rental fee times tax)
        //deposit is not multiplied by tax because deposit is not taxable 
        amount = Rates.deposit + (((Rates.rate * Rates.distance) + Rates.rentalFee) * Rates.tax);
    }

    return amount;
}

double Rates::GetDistance() //Method returns distance
{
    return this->distance;
}

double Rates::GetAmount() //Method returns amount
{
    return this->amount;
}

void Rates::setLuxSeatRate(double changeAmountWindow, double changeAmount) //Method sets Luxury Bus seat rates
{
    LUXURYAISLEANDWINDOW = changeAmountWindow;
    LUXURYOTHER = changeAmount;
}

void Rates::setMiniBusSeatRate(double changeAmount) //Method sets MiniBus seat rates
{
    MINIBUSSEAT = changeAmount;
}

void Rates::setMiniVanSeatRate(double changeAmount) //Method sets Minivan seat rates
{
    MINIVANSEAT = changeAmount;
}

void Rates::setLuxBusRate(double changeAmount, double mileCost, double secDeposit) //Method sets Luxury bus hire rates
{
    LUXURYBH[0] = changeAmount;
    LUXURYBH[1] = mileCost;
    LUXURYBH[2] = secDeposit;

    cout << "New Luxury bus flat fee: " << LUXURYBH[0]
        << "\nNew milage fee: " << LUXURYBH[1]
        << "\nNew security deposit fee: " << LUXURYBH[2] << "\n\n";
}

void Rates::setMiniBusRate(double changeAmount, double mileCost, double secDeposit) //Method sets MiniBus bus hire rates
{
    MINIBUSBH[0] = changeAmount;
    MINIBUSBH[1] = mileCost;
    MINIBUSBH[2] = secDeposit;

    cout << "New MiniBus flat fee: " << MINIBUSBH[0]
        << "\nNew milage fee: " << MINIBUSBH[1]
        << "\nNew security deposit fee: " << MINIBUSBH[2] << "\n\n";
}

void Rates::setMiniVanRate(double changeAmount, double mileCost, double secDeposit) //Method sets Mini van bus hire rates
{
    MINIVANBH[0] = changeAmount;
    MINIVANBH[1] = mileCost;
    MINIVANBH[2] = secDeposit;

    cout << "New MiniVan flat fee: " << MINIVANBH[0]
        << "\nNew milage fee: " << MINIVANBH[1]
        << "\nNew security deposit fee: " << MINIVANBH[2] << "\n\n";
}

double Rates::getLuxSeatRate() //Method returns Luxury bus "Other" seat  rate
{
    return LUXURYOTHER;
}

double Rates::getLuxSeatRateWindow() //Method returns Luxury bus window and aisle seat rate 
{
    return LUXURYAISLEANDWINDOW;
}

double Rates::getMiniBussSeatRate() //Method returns Minibus seat rate
{
    return MINIBUSSEAT;
}

double Rates::getMiniVanSeatRate() //Method returns Mini van seat rate
{
    return MINIVANSEAT;
}

void Rates::SaveTransaction(Reservation Reservation, int Destination, int BusType, string Reason) //Writes transaction information to file
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
        throw exception("There has been an issue trying to open RatesInput.txt");
    }
}

bool Rates::FindTransaction(string Name, Date Day, string Reason) //Method finds transaction using arguments, if found, return true, else return false
{
    bool isFound = false;

    ifstream output;

    //Opens file containing transactions
    output.open("./RatesInput.txt", ios::in);

    if (output.is_open()) 
    {
        Rates transaction = Rates();
        string Day2;

        while (getline(output, transaction.name)) 
        {
            getline(output, Day2);
            output >> transaction.distance >> transaction.rate >> transaction.tickets >> transaction.rentalFee 
                >> transaction.deposit >> transaction.penalty >> transaction.amount;
            getline(output, transaction.reason);
            getline(output, transaction.reason);

            if (transaction.name.compare(Name) == 0 && Day2.compare(Day.toString()) == 0 && transaction.reason.compare(Reason) == 0)
            {
                isFound = true;
                break; 
            }
            else
            {
                isFound = false;
            }
        }

        output.close();
    }
    else
    {
        isFound = false;
    }

    return isFound;
}

void Rates::GetTransaction(string Name, Date Day, string Reason) //Method reads the transaction information from a file and stores it in current object
{
    ifstream output;
    
    output.open("./RatesInput.txt", ios::in);

    if (output.is_open()) 
    {
        Rates transaction = Rates();
        string Day2;
        transaction.distance = -1; //Sets distance to -1 for error checking
    
        while (getline(output, transaction.name)) 
        {
            getline(output, Day2);
            output >> transaction.distance >> transaction.rate >> transaction.tickets >> transaction.rentalFee 
                >> transaction.deposit >> transaction.penalty >> transaction.amount;
            getline(output, transaction.reason); 
            getline(output, transaction.reason); 
    
            if (transaction.name.compare(Name) == 0 && Day2.compare(Day.toString()) == 0 && transaction.reason.compare(Reason) == 0)
            {
                transaction.day = Day;
                *this = transaction;
                break;
            }
        }
    
        output.close();
    }
    else
    {
        throw exception("There has been an issue trying to open RatesInput.txt");
    }
}

void Rates::PrintTransaction(Rates Transaction) //Prints the transaction
{
    cout << "\n\nTransaction Details\n\n"
        << "Name: " << Transaction.name << "\n"
        << "Day: " << Transaction.day.toString() << "\n"
        << "Distance: " << Transaction.distance << "\n"
        << "Rate: $" << Transaction.rate << " per mile (When totaling all tickets)\n"
        << "Rental Fee: $" << Transaction.rentalFee << "\n"
        << "Deposit: $" << Transaction.deposit << "\n"
        << "Penalty: " << (int)(Transaction.penalty * 100) << "%\n"
        << "Tax: " << (int)((Transaction.tax - 1) * 100) << "%\n"
        << "Amount: $" << fixed << setprecision(2) << Transaction.amount << "\n"
        << "Reason: " << Transaction.reason << "\n\n";
}

void Rates::CheckWeeklySales(Date date) //Prints total weekly sales
{
    cout << "Total Sales During Week of " << date.toString() << "\n\n";

    double refunds = 0;
    double purchases = 0;

    ifstream output;

    output.open("./RatesInput.txt", ios::in);

    for (int i = 0; i < 6; i++)
    {
        if (output.is_open()) 
        {
            Rates transaction = Rates();
            string Day2;

            while (getline(output, transaction.name)) 
            {
                getline(output, Day2);
                output >> transaction.distance >> transaction.rate >> transaction.tickets >> transaction.rentalFee
                    >> transaction.deposit >> transaction.penalty >> transaction.amount;
                getline(output, transaction.reason); 
                getline(output, transaction.reason); 

                if (Day2.compare(date.toString()) == 0)
                {
                    (transaction.amount > 0) ? purchases += (transaction.amount - transaction.deposit) : refunds += transaction.amount;
                }
            }
        }
        else
        {
            throw exception("There has been an issue trying to open RatesInput.txt");
        }

        date.nextDay();
    }
    
    output.close();

    cout << "Total Purchases: " << fixed << setprecision(2) << purchases << "\n"
        << "Total Refunds: " << refunds << "\n"
        << "Net Total: " << purchases + refunds << "\n\n";
}

void Rates::ChangeTransactionName(Reservation Reservation, string NewName) //Overwrites transaction with new name
{
    ifstream output;
    
    output.open("./RatesInput.txt", ios::in);
    
    ofstream input;
    
    input.open("./RatesTemp.txt", ios::out);
    
    if (output.is_open())
    {
        Rates transaction = Rates();
        string Day2;
        transaction.distance = -1; 
    
        while (getline(output, transaction.name)) 
        {
            getline(output, Day2);
            output >> transaction.distance >> transaction.rate >> transaction.tickets >> transaction.rentalFee
                >> transaction.deposit >> transaction.penalty >> transaction.amount;
            getline(output, transaction.reason);
            getline(output, transaction.reason);
    
            if (transaction.name.compare("") != 0 && !(transaction.name.compare(Reservation.GetName()) == 0 && Day2.compare(Reservation.GetDateOfTravel().toString()) == 0))
            {
                input << transaction.name << endl;
                input << Day2 << endl;
                input << transaction.distance << endl;
                input << transaction.rate << endl;
                input << transaction.tickets << endl;
                input << transaction.rentalFee << endl;
                input << transaction.deposit << endl;
                input << transaction.penalty << endl;
                input << transaction.amount << endl;
                input << transaction.reason << endl;
            }
            else
            {
                input << NewName << endl;
                input << Day2 << endl;
                input << transaction.distance << endl;
                input << transaction.rate << endl;
                input << transaction.tickets << endl;
                input << transaction.rentalFee << endl;
                input << transaction.deposit << endl;
                input << transaction.penalty << endl;
                input << transaction.amount << endl;
                input << transaction.reason << endl;
            }
        }
    }
    else
    {
        throw exception("There has been an issue trying to open RatesInput.txt");
    }
    
    input.close();
    output.close();
    remove("./RatesInput.txt");
    rename("./RatesTemp.txt", "./RatesInput.txt");
}

void Rates::ChangeReservationCharge(Reservation Reservation, double Amount) //Overwrites transaction with new amount
{
    ifstream output;

    output.open("./RatesInput.txt", ios::in);

    ofstream input;

    input.open("./RatesTemp.txt", ios::out);

    if (output.is_open())
    {
        Rates transaction = Rates();
        string Day2;
        transaction.distance = -1; 

        while (getline(output, transaction.name)) 
        {
            getline(output, Day2);
            output >> transaction.distance >> transaction.rate >> transaction.tickets >> transaction.rentalFee
                >> transaction.deposit >> transaction.penalty >> transaction.amount;
            getline(output, transaction.reason); 
            getline(output, transaction.reason); 

            if (transaction.name.compare("") != 0 && !(transaction.name.compare(Reservation.GetName()) == 0 && Day2.compare(Reservation.GetDateOfTravel().toString()) == 0))
            {
                input << transaction.name << endl;
                input << Day2 << endl;
                input << transaction.distance << endl;
                input << transaction.rate << endl;
                input << transaction.tickets << endl;
                input << transaction.rentalFee << endl;
                input << transaction.deposit << endl;
                input << transaction.penalty << endl;
                input << transaction.amount << endl;
                input << transaction.reason << endl;
            }
            else
            {
                input << transaction.name << endl;
                input << Day2 << endl;
                input << transaction.distance << endl;
                input << transaction.rate << endl;
                input << transaction.tickets << endl;
                input << transaction.rentalFee << endl;
                input << transaction.deposit << endl;
                input << transaction.penalty << endl;
                input << Amount << endl;
                input << transaction.reason << endl;
            }
        }
    }
    else
    {
        throw exception("There has been an issue trying to open RatesInput.txt");
    }

    input.close();
    output.close();
    remove("./RatesInput.txt");
    rename("./RatesTemp.txt", "./RatesInput.txt");
}
