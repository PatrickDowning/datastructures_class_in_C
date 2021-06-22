// Program to implement a phone directory
//Patrick Downing, Brianna Cappo, Evin Fisher, Richard Herget, Alexander Southerland, Cris Zbavitel

#include <iostream>
using namespace std;

const int NAMESIZE = 20;	// Maximum size for a name
const int PHONESIZE = 13;	// Maximum size for a phone number
const int CAPACITY = 10;	// Maximum capacity for the directory

// Structure used to define a phone directory entry
struct PDEntry
{
	char name[NAMESIZE];
	char phone[PHONESIZE];
};

/*
* Prints out the entire directory to the screen
* dir = directory to be printed
* usedSize = number of entries in the directory
*/
void printDirectory(const PDEntry dir[], int usedSize);

/*
* Adds a new entry to the directory
* dir = directory in which the entry is to be added
* usedSize = number of entries in the directory
* nm = name to be added
* ph = phone number to be added
* Returns true if entry was able to be added, and false if there's no room in
* the directory to add any new entries. If the entry was added, usedSize will
* reflect the updated number of entries in the directory
*/
bool addEntry(PDEntry dir[], int& usedSize, const char nm[], const char ph[]);


/*
* Updates a single phone directory entry
* entry = the directory entry to be updated
* nm = name to change the entry to
* ph = phone number to change the entry to
* Upon completion, entry will be changed to the new phone number
*/
void updateEntry(PDEntry& entry, const char nm[], const char ph[]);


/*
* Gets a name and number from the user.  If the name already exists in the
* directory, the entry will be updated with the new number.  If the name is
* not already in the directory, a new entry will be added if there is room
* in the directory to add the name.
* dir = directory in which the entry is to be added/changed
* usedSize = number of entries in the directory
* If the entry was added, usedSize will
* reflect the updated number of entries in the directory
*/
void doAddChangeEntry(PDEntry dir[], int& usedSize);


/*
* Gets a name from the user.  If the name exists in the
* directory, the entry will deleted.
* dir = directory from which the entry should be removed
* usedSize = number of entries in the directory
* If the entry is deleted, usedSize will
* reflect the updated number of entries in the directory
*/
void removeEntry(PDEntry dir[], int& usedSize);



/*
* Searches a directory to try to find a specified name.
* dir = directory to be searched
* usedSize = number of entries in the directory
* nm = name to search for
* If the entry is found, the position number of where the name
* is stored in the directory will be returned.  If the entry is
* not found, the value -1 will be returned instead.
*/
int find(const PDEntry dir[], int usedSize, const char nm[]);


int main()
{
	PDEntry dir[CAPACITY];
	int choice, usedSize = 0;

	// Add a couple of starter entries for testing purposes
	addEntry(dir, usedSize, "John Doe", "252-555-1212");
	addEntry(dir, usedSize, "Jane Doe", "252-555-1313");

	do
	{
		cout << "1. Add/Change Entry\n";
		cout << "2. Print Directory\n";
		cout << "3. Remove Entry\n";
		cout << "4. Exit\n";
		cout << endl;
		cout << "Select: ";

		// Gets the numeric entry from the menu
		cin >> choice;

		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		cin.ignore();

		switch (choice)
		{
		case 1:
			doAddChangeEntry(dir, usedSize);
			break;
		case 2:
			printDirectory(dir, usedSize);
			break;
		case 3:
			removeEntry(dir, usedSize);
			break;
		}

	} while (choice != 4);

	return 0;
}

int find(const PDEntry dir[], int usedSize, const char nm[])
{
	
	for (int i = 0; i < usedSize; i++)
	{													//loops through array and looks for the desired name
		if (strcmp(dir[i].name, nm) == 0) 
		{
			return i;
		}
	}
	return -1;
}

void removeEntry(PDEntry dir[], int& usedSize)
{
	char removed[NAMESIZE];
	printf("What is the name of the entry you want to remove? ");
	cin.getline(removed, NAMESIZE);
	int removeIndex = find(dir, usedSize, removed);

	if (removeIndex == -1) 
	{
		printf("\nEntry was not found.");
	}															//asks user to define the name of the desired entry, then deletes the entry if found
	else 
	{
		for (removeIndex; removeIndex < usedSize; removeIndex++) 
		{
			snprintf(dir[removeIndex].name, NAMESIZE, dir[removeIndex+1].name);
			snprintf(dir[removeIndex].phone, PHONESIZE, dir[removeIndex + 1].phone);
		}
		printf("\nEntry was deleted.");
		usedSize--;
	}
	printf("\n\n");
}

void doAddChangeEntry(PDEntry dir[], int& usedSize)
{
	char name[NAMESIZE];
	printf("Enter name: ");
	cin.getline(name, NAMESIZE);

	char phone[PHONESIZE];											//This function allows the user to update/add entries to the directory
	printf("Enter number: ");										//Uses if statements and function calls to properly administer changes
	cin.getline(phone, PHONESIZE);
	printf("\n");

	int addChange = find(dir, usedSize, name);

	if (addChange != -1) 
	{
		updateEntry(dir[addChange], name, phone);
		printf("Entry was updated.");
	}
	else 
	{
		if (addEntry(dir, usedSize, name, phone)) 
		{
			printf("Entry was added.");
		}
		else 
		{
			printf("Directory is full.");
		}
	}
	printf("\n\n");
}

bool addEntry(PDEntry dir[], int& usedSize, const char nm[], const char ph[])
{
	if (usedSize < CAPACITY)
	{
		updateEntry(dir[usedSize], nm, ph);								//allows user to add entries to the directory
		usedSize++;														//updates usedSize for each entry
		return true;
	}
	else
	{
		return false;
	}
}

void updateEntry(PDEntry& entry, const char nm[], const char ph[])
{
	snprintf(entry.name, NAMESIZE, nm);
	snprintf(entry.phone, PHONESIZE, ph);													//updates entries when called
}

void printDirectory(const PDEntry dir[], int usedSize)
{
	printf("\nDirectory: \n\n");
	for (int i = 0; i < usedSize; i++) {
		printf("%20s", dir[i].name);									//prints name with 20 available spaces for name and
		printf("%15s", dir[i].phone);									//prints phone with 15 available spaces
		printf("\n");
	}
	printf("\n");
}