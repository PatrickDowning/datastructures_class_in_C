// Richard Herget, Brianna Cappo, Patrick Downing, Alexander Southerland, Evin Fisher
// This program simulates a purse of coins

#include <iostream>
using namespace std;

// Create an enumeration data type called Coin
enum class Coin { penny = 1, nickel = 5, dime = 10, quarter = 25 };

const int MAXSIZE = 15;
const int SENTINEL = 0;

// Takes user input (1, 2, 3, 4) and converts it to a Coin
Coin ConvertToCoin(int x);

// Prints a word to the screen stating what the coin is
void PrintCoin(Coin x);

int main()
{
	// Main program code here
	int value = 0;
	int purseCoins[MAXSIZE];
	int i = 0;

	//user instructions
	cout << "Deposit coins into purse.  Enter:\n";
	cout << "1 to deposit penny\n";
	cout << "2 to deposit nickel\n";
	cout << "3 to deposit dime\n";
	cout << "4 to deposit quarter\n";
	cout << "0 to stop\n";
	
	//gets user input + adds coin value to variable value
	for (i; i < MAXSIZE; i++) {
		int userIn;

		cout << " ? ";
		cin >> userIn;

		//if user enters the breakout code
		if (userIn == SENTINEL) {
			break;
		}
		//if it goes till maxsize, tell the user the purse is full
		if (i == MAXSIZE - 1) {
			cout << "Purse is full";
		}

		purseCoins[i] = userIn;
		
		//add coin value to value
		switch (ConvertToCoin(userIn)) {
		case Coin::penny:
			value += 1;
			break;
		case Coin::nickel:
			value += 5;
			break;
		case Coin::dime:
			value += 10;
			break;
		case Coin::quarter:
			value += 25;
			break;
		}

	}

	cout << "\nPurse contents:\n";
	cout << "{ ";

	//Prints all coin imputs from the user
	for (int j = 0; j < i; j++) {
		PrintCoin(ConvertToCoin(purseCoins[j]));
	}

	cout << "}\n";
	cout << "\nTotal purse value : $";
	
	//prints the final value of coins as dollars and cents
	int dollar = value / 100;
	int cents = value - (dollar * 100);
	cout << dollar << "." << cents;


	return 0;
}

//Only accepts values 1,2,3, or 4
Coin ConvertToCoin(int x)
{
	//takes integer passed through function and returns value as coin
	switch (x) {
	case 1:
		return Coin::penny;
		break;
	case 2:
		return Coin::nickel;
		break;
	case 3:
		return Coin::dime;	
		break;
	case 4:
		return Coin::quarter;
		break;
	}

	return Coin::penny;
}

void PrintCoin(Coin x)
{
	//prints the coin passed through the function into the console
	switch (x) {
	case Coin::penny:
		cout << "penny ";
		break;
	case Coin::nickel:
		cout << "nickel ";
		break;
	case Coin::dime:
		cout << "dime ";
		break;
	case Coin::quarter:
		cout << "quarter ";
		break;
	}

}