/* ----------------------     Transaction.cpp     ----------------------
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
// -------------------------------------------------------------------*/

using namespace std;
#include "Transaction.h"

/* ------------------     constructor(Transaction)     -----------------
// Description:     Creats a blank transaction object
// precondition:    Abstract class, used by derived constructor
// postcondition:   A blank object is made
// ------------------------------------------------------------------ */
Transaction::Transaction()
{
	actionType = "x";
	format = "x";
	NextTransaction = NULL;
}

/* ---------------     destructor(Transaction)     ---------------------
// Description:     Transaction destructor
// precondition:    Called by derived class destructor
// postcondition:   You destroy the object
// ------------------------------------------------------------------ */
Transaction::~Transaction()
{
	//NextTransaction pointer handled by Customer destructor
}

/* --------------------     setNextTransaction     --------------------
// Description:     Sets pointer to next Transaction in list
// precondition:    newNextTransaction is a valid (derived) Transaction
// postcondition:   NextTransaction points to newNextTransaction
// ------------------------------------------------------------------ */
void Transaction::setNextTransaction(Transaction* newNextTransaction)
{
	NextTransaction = newNextTransaction;
}

/* --------------------     getNextTransaction     --------------------
// Description:     Returns pointer to next Transaction in list
// precondition:    None
// postcondition:   NextTransaction returned
// ------------------------------------------------------------------ */
Transaction* Transaction::getNextTransaction()
{
	return NextTransaction;
}

/* ---------------------     getActionType     -----------------------
// Description:     This returnes a string of the action type
// precondition:    None
// postcondition:   It returnes the action type
// ------------------------------------------------------------------ */
string Transaction::getActionType()    // action type (B, R)
{
	return actionType;
}

/* ------------------------     getFormat     ------------------------
// Description:     Returnes a string of the format type
// precondition:    None
// postcondition:   It returnes the format type
// ------------------------------------------------------------------ */
string Transaction::getFormat()       // format is D for DVD
{
	return format;
}

//Comedy
/* ------------     constructor(ComedyTransaction)     -----------------
// Description:     Makes a ComedyTransaction object
// precondition:    Calls base constructor first
// postcondition:   ComedyTransaction object created
// ------------------------------------------------------------------ */
ComedyTransaction::ComedyTransaction(string action, string DVD,
	string title, int year)
{
	//Sets data values
	actionType = action;
	format = DVD;
	movieTitle = title;
	releaseYear = year;
}
/* -------------     destructor(ComedyTransaction)     -----------------
// Description:     Deletes ComedyTransaction object
// precondition:    Called by Customer destructor
// postcondition:   ComedyTransaction object deleted
// ------------------------------------------------------------------ */
ComedyTransaction::~ComedyTransaction()
{
	//calls base destructor after completion
}

/* ----------     printSelf(ComedyTransaction)     ---------------------
// Description:     Prints Transaction in Comedy format
// precondition:    None
// postcondition:   ComedyTransaction printed
// ------------------------------------------------------------------ */
void ComedyTransaction::printSelf()
{
	//Comedy format, prints F for funny
	cout << actionType << " " << format << " F " << movieTitle
		<< ", " << releaseYear << endl;
}

/* ----------------------     getMovieTitle     ----------------------
// Description:     Returns a string of the movie title
// precondition:    None
// postcondition:   Returns the movie title
// ------------------------------------------------------------------ */
string ComedyTransaction::getMovieTitle()
{
	return movieTitle;
}
/* ----------------------     getReleaseYear     ----------------------
// Description:     Returnes an int of the release year
// precondition:    None
// postcondition:   Returnes release year
// ------------------------------------------------------------------ */
int ComedyTransaction::getReleaseYear()
{
	return releaseYear;
}

//Drama
/* ------------     constructor(DramaTransaction)     -----------------
// Description:     Makes a DramaTransaction object
// precondition:    Calls base constructor first
// postcondition:   DramaTransaction object created
// ------------------------------------------------------------------ */
DramaTransaction::DramaTransaction(string action, string DVD,
	string director, string title)
{
	//Sets data values
	actionType = action;
	format = DVD;
	directorName = director;
	movieTitle = title;
}

/* -------------     destructor(DramaTransaction)     -----------------
// Description:     Deletes DramaTransaction object
// precondition:    Called by Customer destructor
// postcondition:   DramaTransaction object deleted
// ------------------------------------------------------------------ */
DramaTransaction::~DramaTransaction()
{
	//Calls base destructor after completion
}

/* ----------     printSelf(DramaTransaction)     ---------------------
// Description:     Prints Transaction in Drama format
// precondition:    None
// postcondition:   DramaTransaction printed
// ------------------------------------------------------------------ */
void DramaTransaction::printSelf()
{
	//Drama format, D for drama
	cout << actionType << " " << format << " D " << directorName
		<< ", " << movieTitle << endl;
}

/* ---------------------     getDirectorName     ---------------------
// Description:     Returns a string of the directors name
// precondition:    None
// postcondition:   Returns the directors name
// ------------------------------------------------------------------ */
string DramaTransaction::getDirectorName()
{
	return directorName;
}
/* ---------------------     getMovieTitle     ----------------------
// Description:     Returns a string of the movie title
// precondition:    None
// postcondition:   Returns the movie title
// ------------------------------------------------------------------ */
string DramaTransaction::getMovieTitle()
{
	return movieTitle;
}

//Classic
/* ------------     constructor(ClassicTransaction)     ----------------
// Description:     Makes a ClassicTransaction object
// precondition:    Calls base constructor first
// postcondition:   ClassicTransaction object created
// ------------------------------------------------------------------ */
ClassicTransaction::ClassicTransaction(string action, string DVD,
	int month, int year, string first, string last)
{
	actionType = action;
	format = DVD;
	releaseMonth = month;
	releaseYear = year;
	actorFirst = first;
	actorLast = last;
}

/* -------------     destructor(ClassicTransaction)     -----------------
// Description:     Deletes ClassicTransaction object
// precondition:    Called by Customer destructor
// postcondition:   ClassicTransaction object deleted
// ------------------------------------------------------------------ */
ClassicTransaction::~ClassicTransaction()
{
	//Calls base destructor after completion
}

/* ----------     printSelf(ClassicTransaction)     ---------------------
// Description:     Prints Transaction in Classic format
// precondition:    None
// postcondition:   ClassicTransaction printed
// ------------------------------------------------------------------ */
void ClassicTransaction::printSelf()
{
	//Classic format, C for classic
	cout << actionType << " " << format << " C  " << releaseMonth
		<< " " << releaseYear << " " << actorFirst << " "
		<< actorLast << endl;
}

/* --------------------     getReleaseMonth     ----------------------
// Description:     Returnes an int of the release month of the movie
// precondition:    None
// postcondition:   Returnes the release month of the movie
// ------------------------------------------------------------------ */
int ClassicTransaction::getReleaseMonth()  // data members
{
	return releaseMonth;
}

/* ----------------------     getReleaseYear     ----------------------
// Description:     Returns an int of the release year of the movie
// precondition:    None
// postcondition:   Returns the release year of the movie
// ------------------------------------------------------------------ */
int ClassicTransaction::getReleaseYear()
{
	return releaseYear;
}

/* ----------------------     getActorFirst     -----------------------
// Description:     Returns a string of the actors first name
// precondition:    None
// postcondition:   Returns the actors first name
// ------------------------------------------------------------------ */
string ClassicTransaction::getActorFirst()
{
	return actorFirst;
}

/* -----------------------     getActorLast     -----------------------
// Description:     Returns a string of the actors last name
// precondition:    None
// postcondition:   Returns the actors last name
// ------------------------------------------------------------------ */
string ClassicTransaction::getActorLast()
{
	return actorLast;
}