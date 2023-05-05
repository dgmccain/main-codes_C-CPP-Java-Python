#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

class MovieInfo
{
public:
	string title;
	string rating;
	string genre;
	double score;
	int movieTime;
	double price;
};
class CustomerInfo
{
public:
	string name;
	string movieTitle;
	double moviePrice;
	int quantity;
	double totalCost;
};


void transferStringDataToVector(string movieString, vector<MovieInfo> movieList, string customerString, vector<CustomerInfo> customerList);
void sortMovies(int sortType, string searchInput);
//void (searchCustomers();
bool getCode();
int getMoviePreference();
int displayMenu();
int userEffects(int userChoice, int preferance, string searchInput, bool isValid, int adminChoice);
int adminMenu();
int adminEffects(int adminChoice, int userChoice, bool isValid);


int main(int argc, char *argv[])
{
	//standard variables...
	int userChoice = 0;
	int adminChoice = 0;
	bool isValid = false;
	int preferance = 0;
	string confirmation;
	char contKey;
	string searchInput;

	//variables for movies...
	ifstream moviesFile;
	string moviesTempString;
	string moviesString;
	vector<MovieInfo> movieList;

	//variables for customers...
	ifstream customersFile;
	string customersTempString;
	string customersString;
	vector<CustomerInfo> customerList;

	//open files and copy data to strings...
	moviesFile.open(argv[1]);  //movie data stored in argv[1] txt file...
	if (!moviesFile.is_open())
	{
		cout << "ERROR - could not open movies file..." << endl << endl;
	}
	else
	{
		while (moviesFile.good())
		{
			getline(moviesFile, moviesTempString);
			moviesString += moviesTempString;
			moviesString += "|";  //maybe change "|" to "\n"...
		}
	}
	moviesFile.close();
	
	customersFile.open(argv[2]);  //customer data stored in argv[2] txt file...
	if (!customersFile.is_open())
	{
		cout << "ERROR - could not open customers file..." << endl << endl;
	}
	else
	{
		while (customersFile.good())
		{	
		getline(customersFile, customersTempString);
			customersString += customersTempString;
			customersString += "|";  //maybe change "|" to "\n"...
		}
	}
	customersFile.close();

	transferStringDataToVector(moviesString, movieList, customersString, customerList);
	cout << endl << moviesString << endl << customersString << endl << endl;  //DELETE...

	do
	{

		userChoice = displayMenu();
		userEffects(userChoice, preferance, searchInput, isValid, adminChoice);

		system("pause");
		system("cls");

	} while (userChoice >=1 && userChoice <=3);

	return 0;
}

void transferStringDataToVector(string movieString, vector<MovieInfo> movieList, string customerString, vector<CustomerInfo> customerList)
{


	/*
	for (int i = 0; i < movieString.length(); i++)
	{
	movieList.at(i) = movieString.at(i);
	}

	for (int i = 0; i < customerString.length(); i++)
	{
	customerList.at(i) = customerString.at(i);
	}
	*/
}

//SEARCH MOVIES FUNCTION...
void sortMovies(int sortType, string searchInput)
{
	bool flag;
	do
	{
		flag = false;
		/*
		switch (sortType)
		{
		case 1: // sortMoviesByTitle()
		cout << MovieInfo.title << "    ";
		cout << rating << "    ";
		cout << genre << "    ";
		cout << score << "    ";
		cout << movieTime << "    ";
		cout << price << "    " << endl;
		break;
		case 2: // sortMoviesByGenre()
		cout << genre << "    ";
		cout << title << "    ";
		cout << rating << "    ";
		cout << score << "    ";
		cout << movieTime << "    ";
		cout << price << "    " << endl;
		break;

		case 3: // sortMoviesByPrice()
		cout << price << "    ";
		cout << title << "    ";
		cout << rating << "    ";
		cout << genre << "    ";
		cout << score << "    ";
		cout << movieTime << "    " << endl;
		break;
		case 4: // searchMovies()
		cout << "Enter the movie title: ";
		cin >> searchInput;
		for (int i = 0; i < NUMBEROFMOVIES; i++)
		{
		if (searchInput == MOVIESLIST.at(i))
		cout << searchInput << " found!" << endl;
		cout << MOVIEINFO from title - price data from txt file << endl;
		}
		default:
		cout << "ERROR - choose options 1-3";
		flag = true;
		}
		*/
	} while (flag == true);
}

//SEARCH CUSTOMERS FUNCTION...
/*
void (searchCustomers()
{
//code goes here...
//search history/database for matching customer name/user-entered results...
}
*/

bool getCode()
{
	string securityCode = "270448"; //adjustable code...
	string userCode;

	cout << "Please enter your 6-digit access code: ";
	cin >> userCode;
	if (userCode == securityCode)
	{
		return true;
	}
	else
	{
		cout << endl << "Invalid code" << endl;
		return false;
	}
}

int getMoviePreference()
{
	int choice;

	do
	{
		cout << "=======================================" << endl;
		cout << "|How would you like to sort the list? |" << endl;
		cout << "=======================================" << endl;
		cout << "|Type 1 to prioritize by title        |" << endl;
		cout << "|Type 2 to prioritize by genre        |" << endl;
		cout << "|Type 3 to prioritize by price        |" << endl;
		cout << "=======================================" << endl;
		cin >> choice;

		if (choice < 1 || choice > 3)
		{
			system("cls");
			cout << "INVALID INPUT" << endl << endl;
		}
	} while (choice < 1 || choice > 3);
	return choice;
}

int displayMenu()
{
	int choice;

	cout << "====================================" << endl;
	cout << "|What would you like to do?        |" << endl;
	cout << "====================================" << endl;
	cout << "|1 to view the movie list          |" << endl;
	cout << "|2 to buy a movie ticket           |" << endl;
	cout << "|3 to access admin options         |" << endl;
	cout << "|4 to quit the program             |" << endl;
	cout << "====================================" << endl;
	cin >> choice;

	return choice;
}

int userEffects(int userChoice, int preferance, string searchInput, bool isValid, int adminChoice)
{
	switch (userChoice)
	{
	case 1:
		cout << endl << "You chose to view the list of movies" << endl << endl;
		preferance = getMoviePreference();
		sortMovies(preferance, searchInput);
		cout << endl;
		break;
	case 2:
		cout << endl << "You chose to buy a movie ticket" << endl;
		//function goes here...
		cout << endl;
		break;
	case 3:
		cout << endl << "You chose to access admin options" << endl;
		isValid = getCode();
		do
		{
			if (isValid)
			{
				system("cls");
				cout << "Code accepted" << endl << endl;
				adminChoice = adminMenu();
				adminEffects(adminChoice, userChoice, isValid);
			}
		} while (adminChoice >= 1 && adminChoice <= 4);  //remain in admin mode until user chooses to exit...
		cout << endl;
		break;
	case 4:
		cout << endl << "You quit the program" << endl << endl;
		break;
	default:
		cout << endl << "INVALID INPUT" << endl;
		cout << "program closing..." << endl << endl;
		userChoice = 4;
		break;
	}
	return 0;
}

int adminMenu()
{
	int choice;

	cout << "====================================" << endl;
	cout << "|What would you like to do?        |" << endl;
	cout << "====================================" << endl;
	cout << "|1 to add a movie to the list      |" << endl;
	cout << "|2 to delete a movie from the list |" << endl;
	cout << "|3 to view purchase history        |" << endl;
	cout << "|4 to delete a customer's purchase |" << endl;
	cout << "|5 to quit the program             |" << endl;
	cout << "====================================" << endl;
	cin >> choice;

	return choice;
}

int adminEffects(int adminChoice, int userChoice, bool isValid)
{
	//access admin mode menu...
	if (userChoice == 3 && isValid)
	{
		switch (adminChoice)
		{
		case 1:
			//add movie to list...
			//re-open moviesList.txt file...
			break;
		case 2:
			//delete movie from list...
			//re-open moviesList.txt file...
			break;
		case 3:
			//view purchase history...
			//re-open customersList.txt file...
			break;
		case 4:
			//edit purchase history...
			//re-open customersList.txt file...
			break;
		case 5:
			//exit admin mode...
			cout << endl << "Exiting admin menu and returning to standard menu..." << endl;
			break;
		default:
			cout << endl << "INVALID OPTION - exiting admin mode" << endl;
		}
	}
	return 0;
}