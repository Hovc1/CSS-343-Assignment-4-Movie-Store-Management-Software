/* ----------------------     Customer.h     ----------------------
// CSS 343: Christopher Hovsepian and Nick Naslund
// Started 11 August 2020
// Last Modified: 22 August 2020
//
// g++ *.cpp -g
// valgrind ./a.out
// valgrind --leak-check=full ./a.out
//
// Class Description: Specification of data members and functions of
//  Customer class.
//
// ------------------------------------------------------------------*/
#ifndef CUSTOMER_H                                   
#define CUSTOMER_H

using namespace std;
#include <iostream>
#include "Transaction.h"

class Customer
{
public:
	Customer(); // id = 0, firstName = "",  lastName = ""
	Customer(int, string, string);      //id, firstName, lastName
	~Customer();  //Clears out transaction history

	Transaction* getTransactionHead();  //Return start of transaction history

	void setNextCustomer(Customer*);  //Set pointer to next customer in list
	Customer* getNextCustomer();  //Returns a pointer to next Customer

	void printHistory();  //Prints transaction history

	void appendTransaction(Transaction*); //Adds Transaction to history

  //Getter functions
	int getID();
	string getFirst();
	string getLast();

private:
	int id;           //4 digit customer ID number
	string firstName; //Actor first name
	string lastName;  //Actor last name

  //Pointer to head of transaction history (LinkedList head)
	Transaction* TransactionHead;
	//Pointer to next customer (open hashing)
	Customer* nextCustomer;
};// end  class
#endif