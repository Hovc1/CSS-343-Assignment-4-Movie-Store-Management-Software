/* ----------------------     Movie.cpp     ----------------------
// CSS 343: Christopher Hovsepian and Nick Naslund
// Started 11 August 2020
// Last Modified: 22 August 2020
//
// g++ *.cpp -g
// valgrind ./a.out
// valgrind --leak-check=full ./a.out
//
// Class Description: Implementation of functions used by Movie class.
//
// ------------------------------------------------------------------*/

using namespace std;
#include <iostream>
#include "Movie.h"

/* ---------------------     constructor(Movie)     --------------------
// Description:     Creates a new Movie object for derived class
// precondition:    Abstract class, cannot create a Movie object, used
//                   to create Movie portion of derived classes
// postcondition:   Movie portion of derived class created
// ------------------------------------------------------------------ */
Movie::Movie()
{
	//Abstract class, initializes variables to non-useful values to be
	//overwritten in derived class constructors.
	format = 'x';
	stock = 0;
	director = "";
	title = "";
	releaseYear = 0;
	nextMovie = NULL;
}

/* ----------------------     destructor(Movie)     --------------------
// Description:     Deletes Movie class data members
// precondition:    No Movie class objects, only used to delete Movie
//                   portion of derived objects by derived destructors
// postcondition:   Movie data members deleted
// ------------------------------------------------------------------ */
Movie::~Movie()
{
}

/* ------------------------     getFormat     --------------------------
// Description:     Returns Movie format
// precondition:    None
// postcondition:   format returned
// ------------------------------------------------------------------ */
char Movie::getFormat()
{
	return format;
}

/* ------------------------     setStock     ---------------------------
// Description:     Sets stock value of Movie
// precondition:    stockCount must be a non-negative value
// postcondition:   stock value has been updated
// ------------------------------------------------------------------ */
void Movie::setStock(int stockCount)
{
	stock = stockCount;
}

/* ------------------------     getStock     --------------------------
// Description:     Returns value of stock in Movie
// precondition:    None
// postcondition:   stock value is returned
// ------------------------------------------------------------------ */
int Movie::getStock()
{
	return stock;
}

/* ------------------------     getDirector     ------------------------
// Description:     Returns name of Movie director
// precondition:    None
// postcondition:   director is returned
// ------------------------------------------------------------------ */
string Movie::getDirector()
{
	return director;
}

/* ----------------------     getMovieTitle     ------------------------
// Description:     Returns title of Movie
// precondition:    None
// postcondition:   title is returned
// ------------------------------------------------------------------ */
string Movie::getMovieTitle()
{
	return title;
}

/* -----------------------     getReleaseYear     ----------------------
// Description:     Returns releaseYear of Movie
// precondition:    None
// postcondition:   releaseYear is returned
// ------------------------------------------------------------------ */
int Movie::getReleaseYear()
{
	return releaseYear;
}

/* ------------------------     setNextMovie     -----------------------
// Description:     Sets pointer to next Movie in list
// precondition:    newMovie is a valid Classic, Drama, or Comedy
// postcondition:   nextMovie pointer is set to newMovie
// ------------------------------------------------------------------ */
void Movie::setNextMovie(Movie* newMovie)
{
	nextMovie = newMovie;
}

/* ----------------------     getNextMovie     -------------------------
// Description:     Returns next Movie in list
// precondition:    None
// postcondition:   Pointer to next Movie (Classic, Drama, or Comedy)
//  in list is returned
// ------------------------------------------------------------------ */
Movie* Movie::getNextMovie()
{
	return nextMovie;
}

//Virtual functions to allow Classic to work properly in linked list.
//  Comedy and Drama can call these functions, but they provide no
//  meaningful output and we don't call them from Comedy or Drama
//  anywhere in our program. Block comments in Classic class that
//  actually uses these functions.
int Movie::getReleaseMonth()
{
	return 0;
}
string Movie::getActorFirstName()
{
	return "";
}
string Movie::getActorLastName()
{
	return "";
}

//COMEDY
/* ------------------     Constructor(Comedy)     ----------------------
// Description:     Creates a new Comedy object, derived from Movie
// precondition:    None
// postcondition:   New Comedy object is created
// ------------------------------------------------------------------ */
Comedy::Comedy(char newFormat, int newStock, string newDirector,
	string newTitle, int newRelYear)
{
	//Sets Movie values to actual input values
	format = newFormat;
	stock = newStock;
	director = newDirector;
	title = newTitle;
	releaseYear = newRelYear;
}

/* --------------------     destructor(Comedy)     ---------------------
// Description:     Deletes Comedy object (Movie portion implicitly)
// precondition:    Called by Business destructor
// postcondition:   Comedy object deleted, Movie destructor called
// ------------------------------------------------------------------ */
Comedy::~Comedy()
{
}

/* --------------------     printMovie(Comedy)     ---------------------
// Description:     Prints Movie contents in Comedy format
// precondition:    None
// postcondition:   Comedy format printed to screen
// ------------------------------------------------------------------ */
void Comedy::printMovie()
{
	//Manually prints F for funny, since this is the Comedy print
	cout << "F " << format << " " << stock << " " << director << " " <<
		title << " " << releaseYear << endl;
}

//DRAMA
/* ------------------     Constructor(Drama)     ----------------------
// Description:     Creates a new Drama object, derived from Movie
// precondition:    None
// postcondition:   New Drama object is created
// ------------------------------------------------------------------ */
Drama::Drama(char newFormat, int newStock, string newDirector,
	string newTitle, int newRelYear)
{
	//Sets Movie values to actual input values
	stock = newStock;
	director = newDirector;
	title = newTitle;
	releaseYear = newRelYear;
	format = newFormat;
}

/* --------------------     destructor(Drama)     ---------------------
// Description:     Deletes Drama object (Movie portion implicitly)
// precondition:    Called by Business destructor
// postcondition:   Drama object deleted, Movie destructor called
// ------------------------------------------------------------------ */
Drama::~Drama()
{
}

/* --------------------     printMovie(Drama)     ----------------------
// Description:     Prints Movie contents in Drama format
// precondition:    None
// postcondition:   Drama format printed to screen
// ------------------------------------------------------------------ */
void Drama::printMovie()
{
	//Manually prints D for drama, since this is the Drama print
	cout << "D " << format << " " << stock << " " << director << " " <<
		title << " " << releaseYear << endl;
}

//CLASSIC
/* ------------------     Constructor(Classic)     ---------------------
// Description:     Creates a new Classic object, derived from Movie
// precondition:    None
// postcondition:   New Classic object is created
// ------------------------------------------------------------------ */
Classic::Classic(char newFormat, int newStock, string newDirector,
	string newTitle, string newFirstName, string newLastName,
	int newRelMonth, int newRelYear)
{
	//Sets Movie values to actual input values
	format = newFormat;
	stock = newStock;
	director = newDirector;
	title = newTitle;
	releaseYear = newRelYear;
	//Sets unique Classic data members
	releaseMonth = newRelMonth;
	actorFirstName = newFirstName;
	actorLastName = newLastName;
}

/* --------------------     destructor(Comedy)     ---------------------
// Description:     Deletes Classic object (Movie portion implicitly)
// precondition:    Called by Business destructor
// postcondition:   Classic object deleted, Movie destructor called
// ------------------------------------------------------------------ */
Classic::~Classic()
{
}

/* --------------------     printMovie(Classic)     --------------------
// Description:     Prints Movie contents in Classic format
// precondition:    None
// postcondition:   Classic format printed to screen
// ------------------------------------------------------------------ */
void Classic::printMovie()
{
	//Manually prints C for classic, since this is the Classic print
	cout << "C " << format << " " << stock << " " << director << " " <<
		title << " " << actorFirstName << " " << actorLastName << " " <<
		releaseMonth << " " << releaseYear << endl;
}

/* ---------------------     getReleaseMonth     -----------------------
// Description:     Returns releaseMonth of Movie
// precondition:    None
// postcondition:   releaseMonth returned
// ------------------------------------------------------------------ */
int Classic::getReleaseMonth()
{
	return releaseMonth;
}

/* ---------------------     getActorFirstName     ---------------------
// Description:     Returns firstName of actor
// precondition:    None
// postcondition:   Actor's firstName returned
// ------------------------------------------------------------------ */
string Classic::getActorFirstName()
{
	return actorFirstName;
}

/* ---------------------     getActorLastName     ----------------------
// Description:     Returns lastName of actor
// precondition:    None
// postcondition:   Actor's lastName returned
// ------------------------------------------------------------------ */
string Classic::getActorLastName()
{
	return actorLastName;
}