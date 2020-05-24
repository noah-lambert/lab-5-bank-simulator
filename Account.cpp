#include "Account.h"
#include <iostream>

/**
 * Code for savings account in a banking system.
 * Author: Steven P. Crain, steven.crain@plattsburgh.edu
 * Suitable for classroom use only.
 */
 
bool Bank::Account::deposit(Bank::Money amount)
{
    if(!valid || amount<=0.0)
        return false;
        
    effective+=amount;
    return true;
}

bool Bank::Account::try_withdraw(Bank::Money amount)
{
	if(Withdraw_Count>0)	//checks if user's account is still under 3 witdrawals on the day
	{
		if(!valid || available<amount || effective < amount || amount<=0.0 )
			return false;
		available-=amount;
		
		
		return true;
	}
	else					//fails if user has 3 withdrawals on the day
	{
		std::cout << "Too many withdrawls today. Post Transactions and try again." << std::endl; 
		return false;
	}
}

bool Bank::Account::withdraw(Bank::Money amount, Bank::Money approved)
{
    if(!valid || effective<amount || approved<amount || amount<=0.0 )
        return false;
        
    available+=approved-amount;
    effective-=amount;
	std::cout << "Withdrawls remaining: " << Withdraw_Count-1 << std::endl; //displays a helpful notice for how many withdrawals are left
	Withdraw_Count--;		//increments after a valid withdrawal
	return true;
}