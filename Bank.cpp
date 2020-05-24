#include "SavingsAccount.h"

/**
 * Code for the ledger of a banking system.
 * Author: Steven P. Crain, steven.crain@plattsburgh.edu
 * Suitable for classroom use only.
 */

Bank::AccountBank::AccountBank():
    bank(),
    bad_not_found(new Account()),
    max_number(1000)
{
}

Bank::AccountBank::~AccountBank()
{
}

Bank::Account *Bank::AccountBank::lookup(Bank::Number acctno)
{
    if(!bank.count(acctno))
        return bad_not_found.get();
        
    return bank[acctno].get();
}

Bank::Number Bank::AccountBank::open(std::string name)
{
    Bank::Number ret=++max_number;
    bank[ret]=std::unique_ptr<Bank::Account>(new SavingsAccount(name));
    return ret;
}

void Bank::AccountBank::post()  
{
	//Withdraw_Count = 3;
    for(auto &i: bank)  
    {
        Account *acct=i.second.get();
        acct->balance=acct->available=acct->effective;
    }
}