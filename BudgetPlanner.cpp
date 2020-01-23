/*PROGRAM:		BudgetPlanner.cpp
Written by Trevor Evans
This program prompts the user for the amount of compinsation that
  they get for doing a job. It then prompts the user to enter how
  many hours they work in a day and how many days they are schedualed
  to work in that month. It gives the user the option to enter additional
  income (socialsecurity, inheritance, pentation, ect)
  It then prompts the user for their bill info
  (Type of bill and the monthly cost). The program then retrieves the 
  the number of days in that given month. It calculates the amount of
  money the user recives in the month, the amount left after the bills.
  It then calculates and displays the excess money left over distributed
  for each day of that month.
Last updated on october 27, 2016*/
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;



// Function prototypes
double getincome(char);
double getbills(const int, double[], string[]);
int getmonth(char);
double excessIncome(double, double, int);
void Display(double);

int main()
{
	//declare variables
	double moneyIn,		// Holds how much money is braught in
		totMoney = 0,		// Holds total of all money made
		nonworking,		// Holds any nonworking funds recived
		billPay,		// Holds total for all bills
		leftOver,		// Holds money that is left over
		excess;			// Holds calculated excess income
	int workDays,		// Holds the number work days in the month
		numJobs,		// Holds the entered number of jobs
		calanderDays;	// Holds how many days are in the month
	char sal_or_Hour;	// Holds entered salery or hourly pay
	char month;			// Holds the entered month
	const int NUM_PAY = 9;				// Holds size for bill array and billname array
	double bills[NUM_PAY];				// First part of paralell array used in getbills function
	char anykey;		// stalls the program so user can read information
	// Second part of paralell array used in getbills function
	string billname[NUM_PAY] = { "Phone: ", "Transportation: ", "Water & Garbage: ", "Electrical: ",
		"House/Rent: ", "Groceries: ", "gas (for house): ", "Repairs: ",
		"Others(credit card, debt, medical, ect): " };

	//Explain program to user
	cout << "Fallow the instructions and I will help get a daily budget.\n";

	//Prompt user to enter the number of jobs they would like to enter
	cout << "How many jobs are working?\n";
	cin >> numJobs;
	// Validate input
	while (numJobs < 0)
	{
		cout << numJobs << " is invalid you can't work a negative number of jobs.\n"
			<< "Please enter a posative value for number of jobs.\n";
		cin >> numJobs;
	}
	//use a for loop to call getincome function multiple times
	for (int index = 0; index < numJobs; index++)
	{
		cout << "Enter the information for job #" << index + 1 << endl;
		// Prompt user to find out if they get salary or hourly pay
		cout << "Do you earn salary or hourly pay?\n"
			// Explaine to the user the difference in pay type
			<< "Salary means you get paid a certain amount of money each year that is devided out\n"
			<< "into paychecks you receive at certain times each month.\n"
			<< "Hourly pay means you get paid at certain times of the month based on the amount of\n"
			<< "time you have worked.\n"
			<< "Enter S for salary or H for hourly\n";
		cin >> sal_or_Hour;

		// Validate users entery
		while (toupper(sal_or_Hour) != 'S' && toupper(sal_or_Hour) != 'H')
		{
			cout << sal_or_Hour << " is an invalid entery please enter a value from the fallowing list\n"
				<< "S: Salary\n"
				<< "H: Hourly\n";
			cin >> sal_or_Hour;
		}
		// Call the getincome function
		moneyIn = getincome(toupper(sal_or_Hour));
		totMoney += moneyIn;
	}
	cout << "What is the amount of nonworking pay you receive each month\n"
		<< "This includes social security, trust fund, ect...\n";
	cin >> nonworking;

	// Recalculate totalpay
	totMoney += nonworking;
			
	// Call the getbills function
	billPay = getbills(NUM_PAY, bills, billname);


	// Calculate what is left over
	leftOver = (totMoney - billPay);

	// Prompt userr to identify month
	cout << "Enter a value from the list to identify the current month:\n"
		<< "J: January\n"
		<< "F: February\n"
		<< "R: March\n"
		<< "A: April\n"
		<< "M: May\n"
		<< "U: June\n"
		<< "Y: july\n"
		<< "G: August\n"
		<< "S: september\n"
		<< "O: October\n"
		<< "N: November\n"
		<< "D: December\n";
	cin >> month;
	while (toupper(month) != 'J' && toupper(month) != 'F' && toupper(month) != 'R' &&
		toupper(month) != 'A' && toupper(month) != 'M' && toupper(month) != 'U' &&
		toupper(month) != 'Y' && toupper(month) != 'G' && toupper(month) != 'S' &&
		toupper(month) != 'O' && toupper(month) != 'N' && toupper(month) != 'D')
	{
		cout << month << " is an invalid responce please enter a letter from the list for the current month."
			 << "J: January\n"
			<<"F: February\n"
			<<"R: March\n"
			<<"A: April\n"
			<<"M: May\n"
			<<"U: June\n"
			<<"Y: july\n"
			<<"G: August\n"
			<<"S: september\n"
			<<"O: October\n"
			<<"N: November\n"
			<<"D: December\n";
		cin >> month;
	} 
	// Call the get month function
	calanderDays = getmonth(toupper(month));
	
	// Call excessIncome function
	excess = excessIncome(totMoney, billPay, calanderDays);
	
	// Call display function
	Display(excess);

	// Give the user time to read the results
	cout << "Press any key and then press enter when you are ready to end the program.";
	cin >> anykey;
	return 0;
}
//***************************************************************************
// Definition of the get getincome function. This function accepts          *
// a char varible representing the type of income of the user as an         *
// argument. It calculates the amount of money the user will bring in       *
// based on the type of income they have, the amount they get paid,         *
// the amount they work(if applicable). It then calculates and returns their*
// paid income.                                                             *
//***************************************************************************
double getincome(char payType)
{
	//Declair local variables
	double totalPay,	// Holds the total pay
		hourly,		// Holds hourly pay rate
		salery,			// Holds salary pay
		hours,		//Holds entered hours work in a day
		weekpay,		// Calculated weekly pay
		flatWithholds = 0.121,	// Holds flat taxs and withholdings
		// The fallowing hold the federal tax brackets
		// No students have dependents so we assume they claim zero
		bracket1 = 0.13,
		bracket2 = 0.18,
		bracket3 = 0.28,
		bracket4 = 0.31,
		bracket5 = 0.36,
		bracket6 = 0.38,
		bracket7 = 0.425,
		nonworking;		// Holds any nonworking funds recived
	int year = 52,	// Holds weeks in a year
		weeks,			// Holds entered weeks working this month
		days,		//How many days worked in a month
		daysnweek;	// How many days worked in a week


		// Use switch to determine how to calculate
	switch (payType)
	{
	case 'H':
	{
		cout << "How much do make per hour\n";
		cin >> hourly;
		//ensure hourly pay is valid
		while (hourly < 0)
		{
			cout << hourly << " is an invalid responce please enter a posative value for\n"
				<< "How much do you make per hour\n";
			cin >> hourly;
		}
		cout << "How many hours do you work per day?\n";
		cin >> hours;
		//ensure hours is valid
		while (hours < 0)
		{
			cout << hours << " is an invalid responce please enter a posative value for\n"
				<< "How many hours do you work per day?\n";
			cin >> hours;
		}
		cout << "How many days do you work in a week?\n";
		cin >> daysnweek;

		// Validate entery
		while (daysnweek < 0)
		{
			cout << daysnweek << " is an invalid enterr please enter a posative value for\n"
				<< "How many days do you work in a week?\n";
			cin >> daysnweek;
		}
		cout << "How many days will you work this month?\n";
		cin >> days;

		//ensure days is valid
		while (days < 0)
		{
			cout << days << " is an invalid responce please enter a posative value for\n"
				<< "How many days will you work this month?\n";
			cin >> days;
		}
		totalPay = (hourly * hours * days);

		// Calculate week pay
		weekpay = (hourly * hours * daysnweek);

		// Calculate according to tax bracket
		if ((weekpay * 52) > 0 && (weekpay * 52) < 9275)
			totalPay -= (totalPay * flatWithholds * bracket1);
		else if ((weekpay * 52) >= 9275 && (weekpay * 52) < 37650)
			totalPay -= (totalPay * flatWithholds * bracket2);
		else if ((weekpay * 52) >= 37650 && (weekpay * 52) < 91150)
			totalPay -= (totalPay * flatWithholds * bracket3);
		else if ((weekpay * 52) >= 91150 && (weekpay * 52) < 190150)
			totalPay -= (totalPay * flatWithholds * bracket4);
		else if ((weekpay * 52) >= 190150 && (weekpay * 52) < 413350)
			totalPay -= (totalPay * flatWithholds * bracket5);
		else if ((weekpay * 52) >= 413350 && (weekpay * 52) < 415050)
			totalPay -= (totalPay * flatWithholds * bracket6);
		else if ((weekpay * 52) >= 415050)
			totalPay -= (totalPay * flatWithholds * bracket7);
	}
	break;
	case 'S':
	{
		cout << "How much do you make a year?\n";
		cin >> salery;
		while (salery < 0)
		{
			cout << salery << " is an invalid responce, please enter a\n"
				<< "posative value for how much do you make a year?\n";
			cin >> salery;
		}
		cout << "How many weeks do you work this month?\n";
		cin >> weeks;
		while (weeks < 0)
		{
			cout << weeks << " is an invalid entery please enter a posative value for\n"
				<< "How many weeks do you work this month?\n";
			cin >> weeks;
		}
		// Apply federal and state withholdings
		// Students do not have dependents so we assume
		// they claimed zero on their w-5
		totalPay = ((salery / year) * weeks);
		if (salery >= 0 && salery < 9275)
			totalPay -= (totalPay * flatWithholds * bracket1);
		else if (salery >= 9275 && salery < 37650)
			totalPay -= (totalPay * flatWithholds * bracket2);
		else if (salery >= 37650 && salery < 91150)
			totalPay -= (totalPay * flatWithholds * bracket3);
		else if (salery >= 91150 && salery < 190150)
			totalPay -= (totalPay * flatWithholds * bracket4);
		else if (salery >= 190150 && salery < 413350)
			totalPay -= (totalPay * flatWithholds * bracket5);
		else if (salery >= 413350 && salery < 415050)
			totalPay -= (totalPay * flatWithholds * bracket6);
		else if (salery >= 415050)
			totalPay -= (totalPay * flatWithholds * bracket7);
	}
	break;
	}
	// send back to main
	return totalPay;
}
//**************************************************************************
// Definition of the getbills function: This function accepts two string   *
// (a parallel array) and an int representing their size as arguments. It  *
// displays each varaible of the name array and prompts the user enter to  *
// to enter the price of that bill in parallel variable of the bill array. *
// It calculates and returns the total of all the bills.                   *
//**************************************************************************
double getbills(const int size, double bill[], string name[])
{
	//Declare local variables
	double billCost = 0;		// Holds entered bill cost
	double totBills = 0;		//Holds the total bills
	int count = 0;				// Counter

	// inform the user of the use of the function
	cout << "For each bill displayed monthly cost of that bill:\n";

	for (count; count < size; count++)
	{
		cout << name[count];
		cin >> billCost;
		while (billCost < 0)
		{
			cout << billCost << " is invalid for your bill" << endl
				<< "Please enter a posative value payment amount for\n"
				<< name[count];
			cin >> billCost;
		}
		bill[count] = billCost;
		totBills += billCost;
	}

	return totBills;
}
//*****************************************************************
// Deffinition of the get month function: This function excepts a *
// char variable for it's parameters. It uses a switch to set the *
// number of days to the chosen month (sent in the perameter) if  *
// February is the selected month the user should be prompted to  *
// identify if it's a leap year. This function identifies and     *
// returns the number of days in the selected month.              *
//*****************************************************************
int getmonth(char month)
{
	//Declare local variables
	int days;		//Holds the number of days in the month
	char leapYear;	// Holds yes no response if its leap year
	// Use switch for chosen month
	switch (month)
	{
	case 'J':
		days = 31;
		break;
	case 'F':
	{
		// Prompt the user to enter wether it's a leap year or not
		cout << "Is it a leap year?\n"
			<< "Enter Y for yes or N if it's not a leap year.\n";
		cin >> leapYear;
		// Validate response
		while (toupper(leapYear) != 'Y' && toupper(leapYear) != 'N')
		{
			cout << leapYear << " is an invalid responce. It is a yes no question.\n"
				<< "Please enter Yes if it is a leap year or N if it is not a leap year.\n";
			cin >> leapYear;
		}
		if (toupper(leapYear) == 'Y')
			days = 29;
		else if (toupper(leapYear) == 'N')
			days = 28;
	}
	break;
	case 'R':
		days = 31;
		break;
	case 'A':
		days = 30;
		break;
	case 'M':
		days = 31;
		break;
	case 'U':
		days = 30;
		break;
	case 'Y':
		days = 31;
		break;
	case 'G':
		days = 31;
		break;
	case 'S':
		days = 30;
		break;
	case 'O':
		days = 31;
		break;
	case 'N':
		days = 30;
		break;
	case 'D':
		days = 31;
		break;
	}
	return days; 
}
//******************************************************************
// Definition of the excessIncome function. This function accepts  *
// two double values and an integer value as it's peramaters. It   *
// calculates a daily allowence by subtracting the bills from the  *
// total money and dividing it by the number of days in the month. *
// The function returns it's calculation.                          *
//******************************************************************
double excessIncome(double money, double bills, int days)
{
	// Declare local variable
	double excess;	// Holds daily left over money
	excess = ((money - bills) / days);
	return excess;
}
//**************************************************************
// Definition of the Display function. This function accepts a *
// double variable as it's perameters. It explains to the user *
// what the meaning of the double is and displays in a dollar  *
// format.                                                     *
//**************************************************************
void Display(double excess)
{
	// set output precision
	cout << setprecision(2) << fixed;
	// Explain output and display excess
	cout << "With all your income added together and your bills paid\n"
		<< " In order to maintain your budget:"
		<< "You have $" << excess << " to spend each day this month\n";
}