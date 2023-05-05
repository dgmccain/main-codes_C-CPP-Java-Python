#include <iostream>
#include <iomanip> //can be used for formatting in later program modding
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define LOWERBOUND 100 //sets lowest random number to 100...
#define UPPERBOUND 500 //sets highest random number to 500...

int getPin()
{
	int userInput = 0;
	int attempts = 3;
	int result = 0;

	cout << "Enter your pin: ";
	cin >> userInput;

	if (userInput < 1000 || userInput > 9999)
	{
		do
		{
			cout << "Invalid pin number. You have " << attempts << " attempts left.";
			cout << endl << "Enter your pin: ";
			cin >> userInput;
			attempts--;

			if (attempts == 0)
			{
				cout << endl << "You entered an invalid pin too many times." << endl;
				cout << "Contact your bank for assistance." << endl << endl;
				result = 0;
			}
		} while (attempts != 0 && userInput < 1000 || userInput > 9999);
	}

	if (userInput >= 1000 && userInput <= 9999)
	{
		result = userInput;
	}

	return result;
}

double generateRandomBalance()
{
	double result;

	result = LOWERBOUND + rand() % (UPPERBOUND - LOWERBOUND) +1;

	return result;
}

bool askReceipt()
{
	string userChar;

	cout << "Would you like a receipt? Enter Y for Yes: ";
	cin >> userChar;

	if (userChar == "y" || userChar == "Y")
	{
		return true;
	}

	else
	{
		return false;
	}
}

int displayMenu()
{
	int choice;

	cout << endl;
	cout << "============================" << endl;
	cout << "|What would you like to do?|" << endl;
	cout << "============================" << endl;
	cout << "|1 for Fast Cash           |" << endl;
	cout << "|2 to Make a Deposit       |" << endl;
	cout << "|3 to Withdraw Money       |" << endl;
	cout << "|4 to View Balance         |" << endl;
	cout << "|5 to Get Card Back        |" << endl;
	cout << "============================" << endl;

	cin >> choice;

	system("cls");

	return choice;
};

double fastCash(double newBalance)
{
	double result = newBalance;
	int choice;
	int withdrawAmount;

	cout << "Your current balance is $";
	cout << fixed << setprecision(2);
	cout << newBalance << endl << endl;

	cout << "=======================================" << endl;
	cout << "|How much would you like to withdraw?  |" << endl;
	cout << "=======================================" << endl;
	cout << "|1 for $20.00                          |" << endl;
	cout << "|2 for $40.00                          |" << endl;
	cout << "|3 for $80.00                          |" << endl;
	cout << "|4 for $100.00                         |" << endl;
	cout << "=======================================" << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
		withdrawAmount = 20;
		break;
	case 2:
		withdrawAmount = 40;
		break;
	case 3:
		withdrawAmount = 80;
		break;
	case 4:
		withdrawAmount = 100;
		break;
	default:
		cout << "Error" << endl;
		break;
	}

	if (newBalance > withdrawAmount)
	{
		system("cls");
		cout << "You received $" << withdrawAmount << endl;
		result = newBalance - withdrawAmount;
	}
	else
	{
		cout << "You do not have enough money" << endl;
	}

	return result;
}

double depositMoney(double newBalance)
{
	double result;
	double userInput;

	cout << "Your current balance is $";
	cout << fixed << setprecision(2);
	cout << newBalance << endl;

	cout << "Enter how much would you like to deposit: $";
	cin >> userInput;

	result = newBalance + userInput;

	cout << "Your new balance is $" << result << endl;

	return result;
}

double withdrawMoney(double newBalance)
{
	double result = newBalance;
	double userNum;
	char userChar;

	cout << "Your current balance is $";
	cout << fixed << setprecision(2);
	cout << newBalance << endl;

	cout << "Enter how much you would like to withdraw: $";
	cin >> userNum;

	if (userNum > newBalance)
	{
		cout << "You do not have enough money in your balance..." << endl;
		cout << "Would you like to continue withdrawing? Y to continue or N to cancel: ";
		cin >> userChar;

		if (userChar == 'y' || userChar == 'Y')
		{
			cout << "Enter how much you would like to withdraw: $";
			cin >> userNum;
		}
	}

	else if (userNum <= newBalance)
	{
		newBalance = newBalance - userNum;
		cout << "Your new balance is $" << newBalance << endl << endl;
	}

	result = newBalance;
	return result;
}

void main()
{
	int menuChoice;
	srand((unsigned)time(NULL));
	double originalBalance = generateRandomBalance();
	double newBalance = originalBalance;
	int pinNum;
	bool isRepeipt = false;

	pinNum = getPin();

	if (pinNum != 0)
	{
		isRepeipt = askReceipt();
		do
		{
			menuChoice = displayMenu();

			switch (menuChoice)
			{
			case 1:
				cout << "You chose Fast Cash" << endl;
				newBalance = fastCash(newBalance);
				break;
			case 2:
				cout << "You chose to Make a Deposit..." << endl << endl;
				newBalance = depositMoney(newBalance);
				cout << endl;
				break;
			case 3:
				cout << "You chose to Withdraw Money..." << endl << endl;
				newBalance = withdrawMoney(newBalance);
				break;
			case 4:
				cout << "You chose to View Balance..." << endl;
				cout << "Your current balance is $";
				cout << fixed << setprecision(2);
				cout << newBalance << endl;
				break;
			case 5:
				cout << "You took back your card..." << endl;
				cout << "Have a nice day!" << endl << endl;
				break;
			default:
				cout << endl << "INVALID INPUT" << endl;
				cout << "program closing..." << endl << endl;
				menuChoice = 5;
				break;
			}

		} while (menuChoice != 5);
	}

	if (isRepeipt)
	{
		cout << "Pin #" << pinNum << endl;
		cout << "Original Balance: $" << originalBalance << endl;
		cout << "New Balance: $" << newBalance << endl << endl;
	}

	system("pause");
}