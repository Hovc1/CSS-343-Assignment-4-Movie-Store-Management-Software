/* ----------------------     business.h     ----------------------
// CSS 343: Christopher Hovsepian and Nick Naslund
// Started 11 August 2020
// Last Modified: 22 August 2020
//
// g++ *.cpp -g
// valgrind ./a.out
// valgrind --leak-check=full ./a.out
//
// Class Description: Specification of data members and functions of
//  business class.
//
// ------------------------------------------------------------------*/

#ifndef BUSINESS_H                                   
#define BUSINESS_H   

using namespace std;
#include <iostream>
#include <string>
#include "Customer.h"
#include "Movie.h"

class Business
{
public:

	//Constructor/Destructor
	Business();
	~Business();
	//Destructor helper
	void clearMovieList(Movie*);

	//Functions for making Customer hashTable
	void processCustomers(ifstream&);
	void hashAdd(int, string, string);

	//Functions for making Movie lists
	void processMovies(ifstream&);
	Movie* factoryMovie(ifstream&, string);
	void sortMovie(Movie*, string);

	//Functions for performing commands
	void processCommands(ifstream&);
	void inventory();
	Customer* hashFind(int);
	void processFactory(ifstream&, string, int, string);

	//Borrow functions
	bool borrowFunny(string); // movie title
	bool borrowDrama(string); // movie title
	bool borrowClassic(string, string); // first name, last name

	//Return functions
	bool returnFunny(string); // after ID is checked
	bool returnDrama(string); // after ID is checked
	bool returnClassic(string, string);

private:
	//Hash table of customers, performs open hashing
	Customer* hashTable[10];

	Movie* funnyHead;//Head ptr to the comedy genre movie linked list
	Movie* dramaHead;//Head ptr to the drama genre movie linked list
	Movie* classyHead;//Head ptr to the classics genre movie linked list
};
#endif