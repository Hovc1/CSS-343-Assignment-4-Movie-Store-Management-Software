/* ----------------------     business.cpp     ----------------------
// CSS 343: Christopher Hovsepian and Nick Naslund
// Started 11 August 2020
// Last Modified: 22 August 2020
//
// g++ *.cpp -g
// valgrind ./a.out
// valgrind --leak-check=full ./a.out
//
// Class Description: Implementation of functions used by business
//  class.
//
// ------------------------------------------------------------------*/
#include <iostream>
using namespace std;
#include "Business.h"

/* ---------------     constructor(Business)     -----------------------
// Description:     Makes a blank business object
// precondition:    None
// postcondition:   It creates a blank business object
// ------------------------------------------------------------------ */
Business::Business()
{
	//Initialize list headPtrs: classyHead, dramaHead, funnyHead == to null;
	funnyHead = NULL;
	dramaHead = NULL;
	classyHead = NULL;
	for (int i = 0; i < 10; i++)
		hashTable[i] = NULL;
}

/* ----------------     destructor(Business)     -----------------------
// Description:     This is the business destructor
// precondition:    None
// postcondition:   Business object and all allocated data are cleared
// ------------------------------------------------------------------ */
Business::~Business()
{
	//Removes all Movies from each list
	clearMovieList(funnyHead);
	clearMovieList(dramaHead);
	clearMovieList(classyHead);

	//Removes all Customers from hashTable
	Customer* deleteCustomer;
	Customer* nextDeleteCustomer;

	//Traverses list of customers in each bucket/index of hashTable
	for (int i = 0; i < 10; i++)
	{
		deleteCustomer = hashTable[i];
		//Traverses list in current bucket/index, deleting all Customers
		while (deleteCustomer != NULL)
		{
			nextDeleteCustomer = deleteCustomer->getNextCustomer();
			//Customer destructor removes all Transaction history 
				//for customer being deleted
			delete deleteCustomer;
			deleteCustomer = nextDeleteCustomer;
		}
		hashTable[i] = NULL;
	}
}

/* ----------------------     clearMovieList     -----------------------
// Description:     This is a helper function for the business destructor
// precondition:    You need a business object to destruct
// postcondition:   It helps the destructor clean up
// ------------------------------------------------------------------ */
void Business::clearMovieList(Movie* deleteStart)
{
	//If list is empty, do nothing
	if (deleteStart == NULL)
		return;
	//Traverses list
	Movie* movieDeleter = deleteStart;
	Movie* nextDelete = movieDeleter->getNextMovie();
	while (movieDeleter != NULL)
	{
		//Deletes Movie and moves to next Movie in list
		delete movieDeleter;
		movieDeleter = nextDelete;
		if (movieDeleter != NULL)
			nextDelete = movieDeleter->getNextMovie();
	}
	deleteStart = NULL;
}

/* ---------------------     processCustomers     ----------------------
// Description:     This reads the data4customer.txt file and feeds it
//					to the hash table
// precondition:    You need a .txt file to read from, Customer IDs are
//                   between 0000 and 9999
// postcondition:   Customers added to hashTable
// ------------------------------------------------------------------ */
void Business::processCustomers(ifstream& infile)  // data4customers.txt 
{
	//Containers for Customer values
	int gettingID;
	string firstNameInput;
	string LastNameInput;

	while (!infile.eof())
	{
		//Stores customer info from file
		infile >> gettingID;
		infile >> firstNameInput;
		//infile >> LastNameInput;
		getline(infile, LastNameInput);
		if (gettingID > 9999)
		{
			cout << "Customer ID is too large" << endl;
			continue;
		}
		//Last line in input file is an empty line that causes function
		// to run an extra time with ID 2000. This line catches that case.
		if (gettingID < 0)
		{
			break;
		}
		//Sorts Customer into correct place in hashTable
		hashAdd(gettingID, firstNameInput, LastNameInput);
		//Clears Customer data for next run
		gettingID = -1;
		firstNameInput = "";
		LastNameInput = "";
	}
}

/* ------------------------     hashAdd     -------------------------
// Description:     Takes the info from processCustomers function
//					and places it in the hash table
// precondition:    You need to get info from processCustomers
// postcondition:   A new Customer object is added to hashTable
// ------------------------------------------------------------------ */
void Business::hashAdd(int newID, string newFirst, string newLast)
{
	//Open hashing
	int hashLocation = newID / 1000;
	//If bucket is empty, add new Customer there
	if (hashTable[hashLocation] == NULL)
	{
		hashTable[hashLocation] = new Customer(newID, newFirst, newLast);
		return;
	}
	//Walk through list of Customers in bucket and add new Customer at end
	else
	{
		Customer* currentHash = hashTable[hashLocation];
		while (currentHash->getNextCustomer() != NULL)
		{
			//If ID taken, do not make new Customer
			if (currentHash->getID() == newID)
			{
				cout << "Customer ID: " << newID
					<< "  is taken, new Customer not made." << endl;
				return;
			}
			currentHash = currentHash->getNextCustomer();
		}
		//Checks if ID taken on last Customer in list
		if (currentHash->getID() == newID)
		{
			cout << "Customer ID: " << newID
				<< "  is taken, new Customer not made." << endl;
			return;
		}
		//Adds new Customer at end of list in bucket
		Customer* newCustomer = new Customer(newID, newFirst, newLast);
		currentHash->setNextCustomer(newCustomer);
	}
}

/* ----------------------     processMovies     -----------------------
// Description:     This reades the movies off the data4movies.txt file
//					and feeds it to factory movie after error checking
// precondition:    You need a .txt file to read
// postcondition:   If feeds movie info to factoryMovies
// ------------------------------------------------------------------ */
void Business::processMovies(ifstream& infile)  // data4movies.txt  
{
	string CDF;			// classic, drama, funny (commedy)
	char format = 'D';	// D = DVD(only format used)

	while (!infile.fail())
	{
		getline(infile, CDF, ',');

		//Converts to correct format of C, D, F (if close)
		if (CDF == "C" || CDF == "D" || CDF == "F" ||
			CDF == "\nC" || CDF == "\nD" || CDF == "\nF")
		{
			if (CDF == "\nC")
			{
				CDF = "C";
			}
			else if (CDF == "\nD")
			{
				CDF = "D";
			}
			else if (CDF == "\nF")
			{
				CDF = "F";
			}

			//Creates Movie
			Movie* newMovie = factoryMovie(infile, CDF);
			//Places Movie in appropriate list
			sortMovie(newMovie, CDF);
		}
		//Any movie type that is not C, D, or F
		else
		{
			cout <<  CDF << "  is an Invalid Movie Type" << endl;
			//cout << CDF << "  is an Invalid Movie Type" << endl;
			string bad;
			getline(infile, bad);
		}
	}// end while
}

/* ----------------------     factoryMovie     -----------------------
// Description:     This adds the movies to a linked list
// precondition:    You need processMovies to feed you info
// postcondition:   It places Movie objects in a linked list and sorts
// ------------------------------------------------------------------ */
Movie* Business::factoryMovie(ifstream& infile, string CDF)
{
	char format = 'D';	// D = DVD(only format used)
	while (!infile.eof())
	{
		//Making a Classic Movie
		if (CDF == "C")
		{
			int stock;			// number of DVD's in stock
			string director;	// director name
			string title;		// movie title
			int releaseYear;    // year it released

	  // C (Classic only)
			string majorActorFirst;
			string majorActorLast;
			int releaseMonth;

			//Converts string number to int value, stock value
			string stockString;
			getline(infile, stockString, ',');
			stock = stoi(stockString);

			//Gets remaining input values for Classic
			getline(infile, director, ',');
			getline(infile, title, ',');
			infile >> majorActorFirst;
			infile >> majorActorLast;
			infile >> releaseMonth;
			//infile >> releaseYear;

			getline(infile, stockString);
			releaseYear = stoi(stockString);

			//Creates a new classic
			Movie* newClassic = new Classic(format, stock, director,
				title, majorActorFirst, majorActorLast,
				releaseMonth, releaseYear);
			return newClassic; //Returns pointer to new Movie
		}
		else if (CDF == "F")
		{
			int stock;			// number of DVD's in stock
			string director;	// director name
			string title;		// movie title
			int releaseYear;    // year it released

			//Converts string number to int value, stock value
			string stockString;
			getline(infile, stockString, ',');
			stock = stoi(stockString);

			//Gets remaining input values for Comedy
			getline(infile, director, ',');
			getline(infile, title, ',');
			//infile >> releaseYear;

			getline(infile, stockString);
			releaseYear = stoi(stockString);

			//Creates a new Comedy
			Movie* newComedy = new Comedy(format, stock, director,
				title, releaseYear);
			return newComedy; //Returns pointer to new Movie
		}
		else if (CDF == "D")
		{
			int stock;			// number of DVD's in stock
			string director;	// director name
			string title;		// movie title
			int releaseYear;    // year it released

			//Converts string number to int value, stock value
			string stockString;
			getline(infile, stockString, ',');
			stock = stoi(stockString);

			//Gets remaining input values
			getline(infile, director, ',');
			getline(infile, title, ',');
			//infile >> releaseYear;

			getline(infile, stockString);
			releaseYear = stoi(stockString);

			//Makes new Drama
			Movie* newDrama = new Drama(format, stock, director,
				title, releaseYear);
			return newDrama;
		}
		else
		{
			//Bad movie format, gets remainder of input line to discard
			cout << "Bad movie format" << endl;
			string bad;
			getline(infile, bad);
		}
	}// end while
  //If Movie not made, returns pointer to a NULL movie
	Movie* broke = NULL;
	return broke;
}

/* -----------------------     sortMovie     ------------------------
// Description:     This sorts the movies differently depending on
//					wheather it is a commidy, drama or classic
// precondition:    You need movies to be stuck into a linked list
// postcondition:   It places the movies in the correct position
//					in the linked list
// ------------------------------------------------------------------ */
void Business::sortMovie(Movie* unsortedMovie, string CDF)
{
	/*next is the Movie in list that input movie is being compared
	against. cur maintains a pointer to the Movie before next in case
	the input movie needs to be inserted between the two of them.*/
	Movie* cur = NULL; // previous
	Movie* next;
	//Sort classic movie
	if (CDF == "C")
	{
		// sort by:  year, month, last, first
		if (classyHead == NULL) //Movie goes at front of empty list
		{
			classyHead = unsortedMovie;
			return;
		}
		next = classyHead;
		while (next != NULL)
		{
			//Input movie comes before next based on release year      
			if (unsortedMovie->getReleaseYear() < next->getReleaseYear())
			{
				unsortedMovie->setNextMovie(next);
				break;
			}
			else if (unsortedMovie->getReleaseYear() == next->getReleaseYear())
			{
				//Input movie comes before next based on release month
				if (unsortedMovie->getReleaseMonth() < next->getReleaseMonth())
				{
					unsortedMovie->setNextMovie(next);
					break;
				}
				else if (unsortedMovie->getReleaseMonth() == next->getReleaseMonth())
				{
					//Input movie comes before next based on actor last name
					if (unsortedMovie->getActorLastName() < next->getActorLastName())
					{
						unsortedMovie->setNextMovie(next);
						break;
					}
					else if (unsortedMovie->getActorLastName() == next->getActorLastName())
					{
						//Input movie comes before next based on actor first name
						if (unsortedMovie->getActorFirstName() < next->getActorFirstName())
						{
							unsortedMovie->setNextMovie(next);
							break;
						}
						//Movies match based on all 4 sort criteria
						else if (unsortedMovie->getActorFirstName() == next->getActorFirstName())
						{
							//Update next stock to be sum of itself and input movie's stock
							next->setStock(next->getStock() + unsortedMovie->getStock());
							//Frees up memory from input movie
							delete unsortedMovie;
							return;
						}
					}
				}
			}
			//Input movie comes after next based on some criteria
			cur = next;
			next = next->getNextMovie();
		}// end while loop

		//Movie goes at front of non-empty list
		if (cur == NULL)
			classyHead = unsortedMovie;
		//Movie goes at end of list
		else
			cur->setNextMovie(unsortedMovie);
	}
	//Sort dramatic movie
	else if (CDF == "D")
	{
		// sort by: director, title
		//Movie goes at front of empty list
		if (dramaHead == NULL)
		{
			dramaHead = unsortedMovie;
			////////unsortedMovie;s
			return;
		}
		next = dramaHead;
		while (next != NULL)
		{
			//Input movie comes before next based on release year      
			if (unsortedMovie->getDirector() < next->getDirector())
			{
				unsortedMovie->setNextMovie(next);
				break;
			}
			else if (unsortedMovie->getDirector() == next->getDirector())
			{
				//Input movie comes before next based on release month
				if (unsortedMovie->getMovieTitle() < next->getMovieTitle())
				{
					unsortedMovie->setNextMovie(next);
					break;
				}
				else if (unsortedMovie->getMovieTitle() == next->getMovieTitle())
				{
					//Update next stock to be sum of itself and input movie's stock
					next->setStock(next->getStock() + unsortedMovie->getStock());
					//Frees up memory from input movie
					delete unsortedMovie;
					return;
				}
			}
			//Input movie comes after next based on some criteria
			else
			{
				//Walk up both pointers to next Movies in list
				cur = next;
				next = next->getNextMovie();
			}
		}// end while loop
		//Movie goes at front of non-empty list
		if (cur == NULL)
			dramaHead = unsortedMovie;
		//Movie goes at end of list
		else
			cur->setNextMovie(unsortedMovie);
	}
	//Sort comedy movie
	else if (CDF == "F")
	{
		// sort by: title, year
		//Movie goes at front of empty list
		if (funnyHead == NULL)
		{
			funnyHead = unsortedMovie;
			return;
		}
		next = funnyHead;
		while (next != NULL)
		{
			//Input movie comes before next based on release year      
			if (unsortedMovie->getMovieTitle() < next->getMovieTitle())
			{
				unsortedMovie->setNextMovie(next);
				break;
			}
			else if (unsortedMovie->getMovieTitle() == next->getMovieTitle())
			{
				//Input movie comes before next based on release month
				if (unsortedMovie->getReleaseYear() < next->getReleaseYear())
				{
					unsortedMovie->setNextMovie(next);
					break;
				}
				else if (unsortedMovie->getReleaseYear() == next->getReleaseYear())
				{
					//Update next stock to be sum of itself and input movie's stock
					next->setStock(next->getStock() + unsortedMovie->getStock());
					//Frees up memory from input movie
					delete unsortedMovie;
					return;
				}
			}
			//Input movie comes after next based on some criteria
			else
			{
				//Walk up both pointers to next Movies in list
				cur = next;
				next = next->getNextMovie();
			}
		}// end while loop

		//Movie goes at front of non-empty list
		if (cur == NULL)
		{
			funnyHead = unsortedMovie;
			return;
		}
		//Movie goes at end of list
		else
		{
			cur->setNextMovie(unsortedMovie);
			return;
		}
	}
	//Movie type is not C, D, or F
	else
	{
		cout << "Cannot sort this movie type." << endl;
		//Frees up memory from input movie
		delete unsortedMovie;
	}
}

/* -----------------------     inventory     ------------------------
// Description:     This prints our the current inventory of movies
// precondition:    You need movies to print out
// postcondition:   It prints everything out
// ------------------------------------------------------------------ */
void Business::inventory()
{
	cout << "\n";
	//Prints all Comedies
	Movie* currentMovie = funnyHead;
	while (currentMovie != NULL)
	{
		currentMovie->printMovie();
		currentMovie = currentMovie->getNextMovie();
	}
	//Prints all Dramas
	currentMovie = dramaHead;
	while (currentMovie != NULL)
	{
		currentMovie->printMovie();
		currentMovie = currentMovie->getNextMovie();
	}
	//Prints all Classics
	currentMovie = classyHead;
	while (currentMovie != NULL)
	{
		currentMovie->printMovie();
		currentMovie = currentMovie->getNextMovie();
	}
	cout << "\n";
}

/* --------------------     processCommands     ---------------------
// Description:     Takes the commands from data4commands.txt and
//					executes them while error checking
// precondition:    You need a .txt file to read from
// postcondition:   All commands performed
// ------------------------------------------------------------------ */
void Business::processCommands(ifstream& infile)  // data4commands.txt 
{
	while (!infile.fail())
	{	// action type
		string IHBR;	//I=inventory, H=history, B=borrow, R=return  
		infile >> IHBR;
		//Cleans up format of I, H, B, and R commands, removes new line
		if (IHBR == "\nI" || IHBR == "\nH" || IHBR == "\nB" || IHBR == "\nR")
		{
			if (IHBR == "\nI")
			{
				IHBR = "I";
			}
			else if (IHBR == "\nH")
			{
				IHBR = "H";
			}
			else if (IHBR == "\nB")
			{
				IHBR = "B";
			}
			else if (IHBR == "\nR")
			{
				IHBR = "R";
			}
		}
		//Invalid command
		if (IHBR != "I" && IHBR != "H" && IHBR != "B" && IHBR != "R")
		{
			cout << IHBR << "  is not a valid command" << endl;
			//Removes rest of line of bad input
			string bad;
			getline(infile, bad, '\n');
			continue;
		}
		//Displays inventory
		if (IHBR == "I")
		{
			inventory();
			continue;
		}

		int customerID;
		infile.get(); // eats up a blank space
		infile >> customerID;  /////

		//string stockString;
		//getline(infile, stockString, ' ');
		//customerID = stoi(stockString);

		//Verifies Customer exists
		Customer* checkCustomer = hashFind(customerID);//gets customerID
		if (checkCustomer == NULL ||
			customerID != checkCustomer->getID())//checks customer ID
		{
			cout << customerID << "  is not a valid customerID" << endl;
			//Removes rest of line of bad input
			string bad;
			getline(infile, bad, '\n');
			continue;
		}
		//Displays history of Customer
		if (IHBR == "H")
		{
			checkCustomer->printHistory();
			continue;
		}

		infile.get(); // eats up a space /////////
		//Checks format
		string DVD;
		infile >> DVD;
		//Only allowable format presently is D for DVD
		if (DVD != "D")
		{
			cout << "Not a valid DVD" << endl;
			//Removes rest of line of bad input
			string bad;
			getline(infile, bad, '\n');
			continue;
		}
		infile.get();
		//Checks Movie type
		string CDF;
		infile >> CDF;
		//Invalid Movie type
		if (CDF != "C" && CDF != "D" && CDF != "F")
		{
			cout << CDF << " is not a valid Movie type." << endl;
			string bad;
			//Removes rest of line of bad input
			getline(infile, bad, '\n');
			continue;
		}
		//Borrow or return
		if (IHBR == "B" || IHBR == "R")
		{
			processFactory(infile, IHBR, customerID, CDF);
		}
	}// End of while loop //
}

/* -----------------------     hashFind     ------------------------
// Description:     Creats the correct hash number and finds the
//					customer
// precondition:    You need a hash table to look up customers
// postcondition:   Finds the customer, or returns NULL
// ------------------------------------------------------------------ */
Customer* Business::hashFind(int findID)
{
	if (findID > 9999)
	{
		cout << "Customer ID is too large." << endl;
		return NULL;
	}
	//Open hashing
	//Hash function to find bucket index (0 - 9, based on ID < 10000)
	int hashLocation = findID / 1000;
	//If bucket is empty, Customer ID cannot be found
	if (hashTable[hashLocation] == NULL)
	{
		cout << "Customer ID not found." << endl;
		return NULL;
	}
	//Walks list in bucket to try and locate Customer matching findID
	Customer* currentHash = hashTable[hashLocation];
	while (currentHash != NULL)
	{
		//If ID found, return pointer to Customer
		if (currentHash->getID() == findID)
			return currentHash;
		currentHash = currentHash->getNextCustomer();
	}
	cout << "Customer ID not found." << endl;
	return NULL;
}

/* ---------------------     processFactory     ----------------------
// Description:     This processes the borrow and return commands and
//					does error checking before adding them to the
//					customers history
// precondition:    You need to get the command
// postcondition:   It checks to make sure its valid, then places the
//					borrow or return object in the customers history
// ------------------------------------------------------------------ */
void Business::processFactory(ifstream& infile, string IHBR,
	int customerID, string CDF)
{
	if (IHBR == "B")  // borrow
	{
		if (CDF == "F") // title, year
		{
			int year;
			string movieTitle;
			getline(infile, movieTitle, ',');
			//Reads year value
			string stockString;
			getline(infile, stockString);
			year = stoi(stockString);

			if (borrowFunny(movieTitle))
			{	// this adds / appends to customer history
				Transaction* CT = new ComedyTransaction(IHBR, "D",
					movieTitle, year);
				Customer* cust = hashFind(customerID);
				cust->appendTransaction(CT);
			}
		}
		else if (CDF == "D") // director, Movie title
		{
			string director, title;
			getline(infile, director, ',');
			getline(infile, title, ',');

			if (borrowDrama(title))
			{
				//Adds transaction to 
				Transaction* DT = new DramaTransaction(IHBR, "D",
					director, title);
				Customer* cust = hashFind(customerID);
				cust->appendTransaction(DT);
			}
		}
		else if (CDF == "C") // year, month, last, first
		{
			int year, month;
			string last, first;

			infile >> month;
			infile.get();
			infile >> year;
			infile.get();
			infile >> first;
			infile.get();
			infile >> last;

			if (borrowClassic(first, last))
			{
				Transaction* CT = new ClassicTransaction(IHBR, "D",
					month, year, first, last);
				Customer* cust = hashFind(customerID);
				cust->appendTransaction(CT);
			}
		}
		else // not a valid input
		{
			cout << "ERROR: invalid input" << endl;
			string bad;
			getline(infile, bad, '\n');
		}

	}
	else if (IHBR == "R") // return
	{
		if (CDF == "F") // title, year
		{
			int year;
			string movieTitle;
			getline(infile, movieTitle, ',');
			string stockString;
			getline(infile, stockString);
			year = stoi(stockString);	// readYear	

			if (returnFunny(movieTitle))
			{
				Transaction* CT = new ComedyTransaction(IHBR, "D",
					movieTitle, year);
				Customer* cust = hashFind(customerID);
				cust->appendTransaction(CT);
			}
		}
		else if (CDF == "D") // director, Movie title
		{
			string director, title;
			getline(infile, director, ',');
			getline(infile, title, ',');

			if (returnDrama(title))
			{
				Transaction* DT = new DramaTransaction(IHBR, "D",
					director, title);
				Customer* cust = hashFind(customerID);
				cust->appendTransaction(DT);
			}
		}
		else if (CDF == "C") // year, month, last, first
		{
			int year, month;
			string last, first;

			infile >> month;
			infile.get();
			infile >> year;
			infile.get();
			infile >> first;
			infile.get();
			infile >> last;

			if (returnClassic(first, last))
			{
				Transaction* CT = new ClassicTransaction(IHBR, "D",
					month, year, first, last);
				Customer* cust = hashFind(customerID);
				cust->appendTransaction(CT);
			}
		}
		else // not a valid input
		{
			cout << "ERROR: invalid input" << endl;
			string bad;
			getline(infile, bad, '\n');
		}
	}
}// end process Factory


/* ----------------------     borrowFunny     ------------------------
// Description:     Borrows a comedy
// precondition:    You need movie objects to borrow
// postcondition:   Changes stock by - 1 or says that the movie is
//					out of stock
// ------------------------------------------------------------------ */
bool Business::borrowFunny(string line)  // movie title  for commedy
{	//after ID is checked
	Movie* cur = funnyHead;
	while (cur != NULL)
	{
		string title = cur->getMovieTitle();
		if (title == line)
		{
			int stock = cur->getStock(); // findes the stock
			if (stock > 0)
			{
				cur->setStock(stock - 1);//changes stock if it's not 0
				//cout << "Current Stock for  " << cur->getMovieTitle() 
				//<< "  is: " << cur->getStock() << "  -1" << endl; 
				return true;
			}
			else
			{
				cout << cur->getMovieTitle() <<
					"  is out of stock" << endl;
			}
		}
		cur = cur->getNextMovie();
	}// end while loop
	return false;
}

/* ----------------------     borrowDrama     -----------------------
// Description:     Borrows a drama
// precondition:    You need movie objects to borrow
// postcondition:   Changes stock by - 1 or says that the movie is
//					out of stock
// ------------------------------------------------------------------ */
bool Business::borrowDrama(string line)  // movie title
{
	Movie* cur = dramaHead;
	while (cur != NULL)
	{
		string title = cur->getMovieTitle();
		if (title == line)
		{
			int stock = cur->getStock();
			if (stock > 0)
			{
				cur->setStock(stock - 1);
				//cout << "Current Stock for  " << cur->getMovieTitle() 
				//	<< "  is: " << cur->getStock() << "  -1" << endl;
				return true;
			}
			else
			{
				cout << cur->getMovieTitle() << " is out of stock" << endl;
			}
		}
		cur = cur->getNextMovie();
	}// end while loop
	return false;
}///
/* ---------------------     borrowClassic     -----------------------
// Description:     Borrows a classic
// precondition:    You need movie objects to borrow
// postcondition:   Changes stock by - 1 or says that the movie is
//					out of stock
// ------------------------------------------------------------------ */
bool Business::borrowClassic(string first, string last)
{	// year, month, last, first
	Movie* cur = classyHead;
	while (cur != NULL)
	{
		string firstName = cur->getActorFirstName();
		string lastName = cur->getActorLastName();
		if (firstName == first && lastName == last)
		{
			int stock = cur->getStock();
			if (stock > 0)
			{
				cur->setStock(stock - 1);
				//cout << "Current Stock for  " << cur->getMovieTitle() 
				//	<< "  is: " << cur->getStock() << "  -1" << endl;
				return true;
			}
			else
			{
				cout << cur->getMovieTitle() << " is out of stock"
					<< endl;
			}
		}
		cur = cur->getNextMovie();
	}// end while loop
	return false;
}

/* ----------------------     returnFunny     -----------------------
// Description:     Returnes a comedy
// precondition:    must have borrowed the comedy first
// postcondition:   Changes stock by + 1 or sends an error message
// ------------------------------------------------------------------ */
bool Business::returnFunny(string line)
{ // after ID is checked
	Movie* cur = funnyHead;
	while (cur != NULL)
	{
		string title = cur->getMovieTitle();

		if (title == line)
		{
			int stock = cur->getStock();
			if (stock >= 0)
			{
				cur->setStock(stock + 1);
				//cout << "Current Stock for  " << cur->getMovieTitle() 
				//<< "  is: " << cur->getStock() << "  +1" << endl; 
				return true;
			}
			else
			{
				cout << "Something went wrong with a Comedy Return"
					<< endl;
			}
		}
		cur = cur->getNextMovie();
	}// end while loop
	return false;
}
/* ----------------------     returnDrama     -----------------------
// Description:     Returnes a drama
// precondition:    must have borrowed the comedy first
// postcondition:   Changes stock by + 1 or sends an error message
// ------------------------------------------------------------------ */
bool Business::returnDrama(string line)
{
	Movie* cur = dramaHead;
	while (cur != NULL)
	{
		string title = cur->getMovieTitle();
		if (title == line)
		{
			int stock = cur->getStock();
			if (stock >= 0)
			{
				cur->setStock(stock + 1);
				//cout << "Current Stock for  " << cur->getMovieTitle() 
				//<< "  is: " << cur->getStock() << "  +1" << endl;
				return true;
			}
			else
			{
				cout << "Something went wrong with a Drama Return"
					<< endl;
			}
		}
		cur = cur->getNextMovie();
	}// end while loop
	return false;
}
/* ---------------------     returnClassic     ----------------------
// Description:     Returnes a classic
// precondition:    must have borrowed the comedy first
// postcondition:   Changes stock by + 1 or sends an error message
// ------------------------------------------------------------------ */
bool Business::returnClassic(string first, string last)
{ // after ID is checked
	Movie* cur = dramaHead;
	while (cur != NULL)
	{
		string firstName = cur->getActorFirstName();
		string lastName = cur->getActorLastName();
		if (firstName == first && lastName == last)
		{
			int stock = cur->getStock();
			if (stock >= 0)
			{
				cur->setStock(stock + 1);
				//cout << "Current Stock for  " << cur->getMovieTitle() 
				//<< "  is: " << cur->getStock() << "  +1" << endl;
				return true;
			}
			else
			{
				cout << "Something went wrong with a Classic Return"
					<< endl;
			}
		}
		cur = cur->getNextMovie();
	}// end while loop
	return false;
}
