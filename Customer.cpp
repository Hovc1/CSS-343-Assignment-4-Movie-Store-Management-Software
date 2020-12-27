/* ----------------------     customer.cpp     ----------------------
// CSS 343: Christopher Hovsepian and Nick Naslund
// Started 11 August 2020
// Last Modified: 22 August 2020
//
// g++ *.cpp -g
// valgrind ./a.out
// valgrind --leak-check=full ./a.out
//
// Class Description: Implementation of functions used by Customer
//  class.
//
// ------------------------------------------------------------------*/

using namespace std;
#include "Transaction.h"
#include "Customer.h"

//Default constructor not used, not block commented
Customer::Customer()
{
	firstName = "";
	lastName = "";
	id = 0000;
	TransactionHead = NULL;
	nextCustomer = NULL;
}

/* -----------------------     constructor     -------------------------
// Description:     Creates a new Customer object
// precondition:    idNum is valid (between 0000 and 9999)
// postcondition:   New Customer object is created
// ------------------------------------------------------------------ */
Customer::Customer(int idNum, string first, string last)
{
	firstName = first;
	lastName = last;
	id = idNum;
	TransactionHead = NULL;
	nextCustomer = NULL;
}

/* ------------------------     destructor     -------------------------
// Description:     Deletes a Customer object
// precondition:    Called via Business destructor
// postcondition:   Customer is deleted, Transaction history is cleared
// ------------------------------------------------------------------ */
Customer::~Customer()
{
	//If transaction history exists
	if (TransactionHead != NULL)
	{
		//Pointers for current and next Transaction in history
		Transaction* deleteTransaction = TransactionHead;
		Transaction* nextDelete;
		//While there are still Transactions in history
		while (deleteTransaction != NULL)
		{
			//Set next pointer to next Transaction in history
			nextDelete = deleteTransaction->getNextTransaction();
			//Delete current Transaction
			delete deleteTransaction;
			//Move current pointer to next Transaction
			deleteTransaction = nextDelete;
		}
	}
	nextCustomer = NULL;
}

/* --------------------     getTransactionHead()    --------------------
// Description:     Returns pointer to start of Transaction history
// precondition:    none
// postcondition:   Pointer to start of Transaction history is returned
// ------------------------------------------------------------------ */
Transaction* Customer::getTransactionHead()
{
	return TransactionHead;
}

/* ---------------------     setNextCustomer     -----------------------
// Description:     Sets next Customer in list
// precondition:    Valid Customer for input
// postcondition:   Pointer set for next Customer in list
// ------------------------------------------------------------------ */
void Customer::setNextCustomer(Customer* newCustomer)
{
	nextCustomer = newCustomer;
}

/* ----------------------     getNextCustomer     ----------------------
// Description:     Returns pointer to next Customer in list
// precondition:    none
// postcondition:   Pointer to next Customer is returned
// ------------------------------------------------------------------ */
Customer* Customer::getNextCustomer()
{
	return nextCustomer;
}

/* ------------------------     getID     ------------------------------
// Description:     Returns Customer id
// precondition:    None
// postcondition:   id returned
// ------------------------------------------------------------------ */
int Customer::getID()
{
	return id;
}

/* ------------------------     getFirst     ---------------------------
// Description:     Returns actor firstName
// precondition:    None
// postcondition:   firstName returned
// ------------------------------------------------------------------ */
string Customer::getFirst()		///
{
	return firstName;
}

/* ------------------------     getLast     ----------------------------
// Description:     Returns actor lastName
// precondition:    None
// postcondition:   lastName returned
// ------------------------------------------------------------------ */
string Customer::getLast()		///
{
	return lastName;
}

/* ------------------------     printHistory     -----------------------
// Description:     Prints Customer's Transaction history
// precondition:    None
// postcondition:   Customer's history printed to screen
// ------------------------------------------------------------------ */
void Customer::printHistory()
{
	cout << "History of customer " << id << " " << firstName << " "
		<< lastName << endl;
	if (TransactionHead == NULL)
	{
		cout << "This customer hasn't made any transactions.\n" << endl;
		return;
	}
	//Traverses list, makes each Transaction print itself
	Transaction* ph = TransactionHead;
	while (ph != NULL)
	{
		ph->printSelf();
		ph = ph->getNextTransaction();
	}
	cout << endl;
}

/* --------------------     appendTransaction     ---------------------
// Description:     Adds Transaction to end of history
// precondition:    Valid Transaction object for input
// postcondition:   Transaction added to history at end of list
// ------------------------------------------------------------------ */
void Customer::appendTransaction(Transaction* newTransaction)
{
	//If no other transactions, add as head of list
	if (TransactionHead == NULL)
	{
		TransactionHead = newTransaction;
		return;
	}
	//Traverse list until pointing at last Transaction in list
	Transaction* at = TransactionHead;
	while (at->getNextTransaction() != NULL)
	{
		at = at->getNextTransaction();
	}
	//Makes last Transaction point at input Transaction
	at->setNextTransaction(newTransaction);
}