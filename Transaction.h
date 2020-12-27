/* ----------------------     Transaction.h     ----------------------
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

#ifndef TRANSACTION_H                                   
#define TRANSACTION_H  

using namespace std;
#include <iostream>

class Transaction
{
public:
	Transaction();
	virtual ~Transaction();
	virtual void printSelf() = 0;//overload for individual sub classes


	void setNextTransaction(Transaction*);
	Transaction* getNextTransaction(); //returns NextTransaction
	string getActionType();
	string getFormat();

protected:
	string actionType;  // B= borrow, R = return
	string format;      // only D for DVD
	Transaction* NextTransaction;//pointer to next transaction in history
};// end of Transactions


class ComedyTransaction : public Transaction
{
public:
	//action code (B,R), format(D), movie title, release year
	ComedyTransaction(string, string, string, int);
	~ComedyTransaction();
	virtual void printSelf();

	string getMovieTitle();
	int getReleaseYear();

private:
	string movieTitle;
	int releaseYear;
};

class DramaTransaction : public Transaction
{
public:
	//action (B, R), DVD (D), Director Name, Movie Title
	DramaTransaction(string, string, string, string);
	~DramaTransaction();
	virtual void printSelf();

	string getDirectorName();
	string getMovieTitle();

private:
	string directorName;
	string movieTitle;
};

class ClassicTransaction : public Transaction
{
public:
	//action code (B,R), format(D), release month, release year, 
		//actor first, actor last
	ClassicTransaction(string, string, int, int, string, string);
	~ClassicTransaction();
	virtual void printSelf();

	int getReleaseMonth();
	int getReleaseYear();
	string getActorFirst();
	string getActorLast();

private:
	int releaseMonth;
	int releaseYear;
	string actorFirst;
	string actorLast;
};
#endif