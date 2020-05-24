#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H
/**
 * API for savings account data structure for a banking system.
 * Author: Steven P. Crain, steven.crain@plattsburgh.edu
 * Suitable for classroom use only.
 */

#include <string>

#include "Account.h"

namespace Bank
{

class SavingsAccount : public Account
{

public:
    /**
     * @brief Create a new account.
     * @return name  The name of the account holder.
     */
   SavingsAccount(std::string name):
        Account(name){}
      
    /**
     * @brief Clean up when the account object is deleted. 
     */
    virtual ~SavingsAccount() {}
    
    /**
     * @brief Post completed transactions.
     * 
     * This method in AccountBank class has permission to directly manipluate private fields
     */
    friend void Bank::AccountBank::post();
};

}

#endif // SAVINGSACCOUNT_H