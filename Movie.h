/* ----------------------     movie.h     ----------------------
// CSS 343: Christopher Hovsepian and Nick Naslund
// Started 11 August 2020
// Last Modified: 22 August 2020
//
// g++ *.cpp -g
// valgrind ./a.out
// valgrind --leak-check=full ./a.out
//
// Class Description: Specification of functions and data members used
//  by Movie class.
//
// ------------------------------------------------------------------*/
#ifndef MOVIE_H                                   
#define MOVIE_H  

using namespace std;
#include <fstream>
#include <string>

//MOVIE
class Movie
{
public:
	//Constructor/Destructor
	Movie();
	virtual ~Movie();

	// Pure virtual print function, overloaded by each subclass
	virtual void printMovie() = 0;

	//Setters and getters for data members
	char getFormat();
	void setStock(int stockCount);
	int getStock();
	string getDirector();
	string getMovieTitle();
	int getReleaseYear();
	void setNextMovie(Movie* nextMovie);
	Movie* getNextMovie();

	//virtual functions to allow Classic to work with our linked list structure
	virtual int getReleaseMonth();
	virtual string getActorFirstName();
	virtual string getActorLastName();

protected:
	char format;		// Denotes the format of the Movie
	int stock;			// How many copies of the movie the store has
	string director;	// The name of this movie's director
	string title;		// This movie's title
	int releaseYear;	// The year this movie was originally released
	Movie* nextMovie;	// Pointer to the next Movie in linked list
};

//COMEDY
class Comedy : public Movie
{
public:
	// arguments: format, stock, director name, movie title, release year
	Comedy(char, int, string, string, int);
	~Comedy();

	// Prints data members in Comedy format
	void printMovie();
};

//DRAMA
class Drama : public Movie
{
public:
	// Same arguments as Comedy constructor
	Drama(char, int, string, string, int);
	~Drama();

	// Prints data members in Drama format (same as Comedy)
	void printMovie();
};

//CLASSIC
class Classic : public Movie
{
public:
	// arguments: format, stock, director name, movie title,
	// actor first name, actor last name, release month, release year
	Classic(char, int, string, string, string, string, int, int);
	~Classic();

	// prints data members in Classic format
	void printMovie();

	//Getters for Classic data members
	int getReleaseMonth();
	string getActorFirstName();
	string getActorLastName();

private:
	//Data members exclusive to Classic
	int releaseMonth;	    //Integer for month of release (i.e. 2 = February)
	string actorFirstName;  //First name of major actor in this movie
	string actorLastName;   //Last name of major actor in this movie
};
#endif