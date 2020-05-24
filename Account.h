#ifndef ACCOUNT_H
#define ACCOUNT_H

/**
 * API for savings account data structure for a banking system.
 * Author: Steven P. Crain, steven.crain@plattsburgh.edu
 * Suitable for classroom use only.
 */

#include <string>

#include "Bank.h"
namespace Bank
{
typedef double Money;   // Datatype used consistently for money.

/**
 * @class Account
 * @author scrain
 * @date 10/04/2018
 * @file Account.h
 * @brief A savings account in a bank.
 */
class Account
{
protected:
    Money effective;    // The balance taking into account completed transactions that have not posted.
    Money available;    // The balance that is currently available for withdrawal.
    bool valid;         // Flag to indicate if this account is valid for transactions.

private:
    std::string name;   // The name of the account holder.
    Money balance;      // The current posted balance.
	int Withdraw_Count = 3; 
public:
   
    /**
     * @brief Special constructor for making an invalid account to flag that the account was not found. 
     */
    Account():
        effective(0), available(0),  valid(false), name("Not Found"), balance(0) {}
    
        
protected:    
    /**
     * @brief Create a new account.
     * @param name  The name of the account holder.
     */
    Account(std::string name):
        effective(0), available(0), valid(true), name(name), balance(0) {}
        
public:        
    /**
     * @brief Clean up when the account object is deleted. 
     */
    virtual ~Account() {}

    /**
     * @brief Get the ledger information for the account.
     * 
     * This function is used to request information about the account.
     * The information is passed back in reference parameters.
     * If the request is invalid, the balance references are not changed and the 
     * error message is returned in the name reference.
     * 
     * @param name Reference for where to place the name of the account holder or error message.
     * @param balance Reference for where to place the posted balance.
     * @param effective Reference for where to place the effective balance.
     * @param available Reference for where to place the available balance.
     * @return Whether the account information was available. If false, only the name is set.
     */
    bool get_balance(std::string &name, Money &balance, Money &effective, Money &available) const
    {
        name=this->name;
        
        if(!valid)
            return false;
            
        balance=this->balance;
        available=this->available;
        effective=this->effective;
        return true;
    }
    
    /**
     * @brief Perform a deposit.
     * @param amount The amount to deposit.
     * @return Whether the deposit was completed.
     */
    virtual bool deposit(Money amount);
    
    /**
     * @brief Attempt to pre-approve a withdrawal.
     * 
     * Verifies whether the amount could be wthdrawn, considering all policies. If successful,
     * places a hold on the specified amount to ensure that the withdrawal will be able to 
     * complete.
     * 
     * @param amount The amount to withdraw.
     * @return Whether it is possible to withdraw the amount.
     */
    virtual bool try_withdraw(Money amount);
    
    /**
     * @brief Attempt to complete a withdrawal. 
     * 
     * The withdrawal should have been previously approved with the try_withdraw function.
     * The amount may be less than was pre-approved.
     * 
     * @param amount The amount of the transaction.
     * @param approved_mmount The pre-approved amount.
     * @return Whether the transaction completed successfully.
     */
    virtual bool withdraw(Money amount, Money approved_amount);
    
    /**
     * @brief Post completed transactions.
     * 
     * This method in the AccountBank class has permission to directly manipulate the private fields.
     */
    friend void Bank::AccountBank::post();
};

}

#endif // ACCOUNT_H