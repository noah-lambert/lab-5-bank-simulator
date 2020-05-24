#ifndef BANK_H
#define BANK_H

/**
 * API for account ledger for a banking system.
 * Author: Steven P. Crain, steven.crain@plattsburgh.edu
 * Suitable for classroom use only.
 */

#include <map>
#include <memory>

namespace Bank
{

typedef unsigned long long Number;  // The datatype for an account number.
class Account;               // The datatype for a savings account.

class AccountBank
{   
private:
    std::map<Number, std::unique_ptr<Account>> bank; // Container for accounts, map from the account number to the account itself.
    std::unique_ptr<Account> bad_not_found;          // Special account flagging that the account was not found.
    Number max_number;                                      // Highest assigned account number, used to pick new numbers.
    
public:
    /**
     * @brief Create a new, empty bank with no accounts.
     */
    AccountBank();

    /**
     * @brief Cleanup when the bank is deleted.
     */
    ~AccountBank();
    
    /**
     * @brief Find the account given the account number.
     * 
     * If there is an error finding the account, returns a pointer to an invalid account. 
     * The name of the account contains the error message.
     * 
     * @param acctno The account number to look up.
     * @return Pointer to the account.
     */
    Bank::Account *lookup(Number acctno);
    
    /**
     * @brief Open a new account.
     * @param name The name of the account holder.
     * @return The account number for the new account.
     */
    Number open(std::string name);
    
    /**
     * @brief Post all unposted transactions on all accounts.
     */
    void post();
    
    /**
     * @brief Return the map of accounts so that the ledger can be processed.
     */
    const std::map<Number, std::unique_ptr<Account>> &ledger()
    {
        return bank;
    }
	
	//void setWithdraw_Count(const Withdraw_count)
};

}

#endif // BANK_H
