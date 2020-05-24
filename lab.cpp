#include <cctype>
#include <iomanip>
#include <iostream>

#include "Account.h"

using namespace std;
/**
 * User Interface Code for banking system.
 * Author: Steven P. Crain, steven.crain@plattsburgh.edu
 * Suitable for classroom use only.
 */

void open_account(Bank::AccountBank &bank);
void check_balance(Bank::AccountBank &bank);
void deposit(Bank::AccountBank &bank);
void withdraw(Bank::AccountBank &bank);
void transfer(Bank::AccountBank &bank);
void post(Bank::AccountBank &bank);
void ledger(Bank::AccountBank &bank);
Bank::Account *lookup(Bank::AccountBank &bank, const std::string label="");
void print_balance(Bank::Account *account);
void print_balance(Bank::Number acctno, Bank::Account *account);
Bank::Money prompt_amount();

/**
 * @brief A user interface to a bank. Provides a number of different options for doing business with the bank.
 * 
 * The user is prompted to enter a command. The commands can be abbreviated or misspelled. Only the first
 * character of the command is examined.
 * 
 * The commands include:
 *      Open Account:       Open a new account. The user must enter the name of the account holder.
 *      Check Balance:      Check the balance on an account. The user must enter the account number.
 *      Deposit:            Deposit money into an account. The user must enter the account number and amount to deposit.
 *                          Money deposited is not available for withdrawal until transacations are posted.
 *      Withdraw:           Withdraw money from an account. The user must enter the account number and amount to withdraw.
 *      Transfer:           Transfer money between accounts. The user must enter source and desitantion accounts and
 *                          the amount to transfer. 
 *                          Money transfered is not available for withdrawal until transacations are posted.
 *      Post Transactions:  Process all unposted transactions.
 *      List Ledger:        Display a list of all accounts and their balances.
 *      Exit:               Exit the program.
 *                      
 * @return Always returns 0.
 */
int main()
{   // Greet the user.
	std::cout << "Welcome to Simple Bank!" << std::endl;
    char command='n';
    Bank::AccountBank bank;
    bool suppress=false;
    
    // Command loop
    while(command!='e' && !std::cin.eof()) // Exit 
    {   std::string input;
        
        if(!suppress) // This suppresses duplicate prompts in some cases.
            // Prompt the user.
            std::cout << std::endl << "What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer," 
                      << std::endl << "\t Post Transactions, List Ledger or Exit)" << std::endl;
        
        suppress=false; // Disable supressing the prompt.
        std::cin.clear(); // Clear any input errors so that getline can process.
        std::getline(std::cin, input); // Read the command.
        
        if(input.length()>0)
            // Extract and normalize the command
            command=std::tolower(input[0]);
        else
            // Default to a dummy command.
            command='n';
            
        switch(command)
        {
            case 'o':
                open_account(bank);
                break;
                
            case 'c':
                check_balance(bank);
                break;
                
            case 'd':
                deposit(bank);
                break;
                
            case 'w':
                withdraw(bank);
                break;
                
            case 't':
                transfer(bank);
                break;
                
            case 'p':
                post(bank);
                break;
            
            case 'l':
                ledger(bank);
                break;

            case 'e': case 'x': case 27: case 'q': // A number of reasonable indications the user wants to quit.
                command='e';
                break;
                
            default:
                // Generally this means that an empty line was read following reading a parameter.
                suppress=true;
        }
    }
    
	return 0;
}

/**
 * @brief Open an account.
 * @param bank The bank.
 */
void open_account(Bank::AccountBank &bank)
{   
    std::string name="George"; // Error handling is a little loose....
	char type_account;
	
	
    
    std::cout << "Please enter the name of the account holder: ";
    if(!std::getline(std::cin, name))
        std::cout << "Warning: I could not understand what you said and am using 'George' instead." << std::endl;

std::cout << "What type of account would you like to open? (Saving, Checking, Loan)" << std::endl;	//Asks user what account to open
	std::cin >> type_account;
	switch(type_account)
	{
		case 's':
			
		case 'S':
			std::cout << "Savings Account opened." << std::endl;
			break;
		default:		//very broad error handling 
			std::cout << "Sorry, this bank does not support that account. Opening a Savings Account instead." << std::endl;
	}

    Bank::Number acctno=bank.open(name);
    
    std::cout << "The new account number is " << acctno << "." << std::endl;
}

/**
 * @brief Collect information needed and check an account balance.
 * @param bank The bank containing the account.
 */
void check_balance(Bank::AccountBank &bank)
{   lookup(bank);
}

/**
 * @brief Print balance information for an account.
 * 
 * A header is printed.
 * 
 * @param account The account to print.
 */
void print_balance(Bank::Account *account)
{   std::string name;
    Bank::Money balance, effective, available;
    
    account->get_balance(name, balance, effective, available);
    
    std::cout << "Name \tBalance \tEffective \tAvailable" << std::endl
              << std::fixed << std::setprecision(2) 
              << name << '\t'
              << balance << '\t' << effective << '\t' << available << std::endl;
}

/**
 * @brief Print account number and balance information for an account.
 * 
 * No header is printed.
 *
 * @param acctno  The account number.
 * @param account The account.
 */
void print_balance(Bank::Number acctno, Bank::Account *account)
{   std::string name;
    Bank::Money balance, effective, available;
    
    // Load the name and balances from the account.
    account->get_balance(name, balance, effective, available);
    
    std::cout << std::fixed << std::setprecision(2) 
              << name << '\t'
              << balance << '\t' << effective << '\t' << available << std::endl;
}

/**
 * @brief Collect information needed and deposit into an account.
 * @param bank The bank containing the account.
 */
void deposit(Bank::AccountBank &bank)
{   Bank::Account *account=lookup(bank);
    Bank::Money amount=prompt_amount();
    
    if(account->deposit(amount))
    {   std::cout << "Deposit completed." << std::endl;
        print_balance(account);
    } else
        std::cout << "Deposit failed." << std::endl;
}

/**
 * @brief 
 * @param bank
 */
void withdraw(Bank::AccountBank &bank)
{
    Bank::Account *account=lookup(bank);
    Bank::Money amount=prompt_amount();
    
    if(!account->try_withdraw(amount))
    {   std::cout << "Withdrawal not approved." << std::endl;
        return;
    }
    
    std::cout << "Withdrawal approved." << std::endl;
    print_balance(account);
        
    if(!account->withdraw(amount, amount))
    {
        std::cout << "Withdrawal failed." << std::endl;
        return;
    }
        
    std::cout << "Withdrawal completed." << std::endl;
    print_balance(account);
}

/**
 * @brief Transfer money between accounts.
 * @param bank The bank containing the accounts.
 */
void transfer(Bank::AccountBank &bank)
{
    Bank::Account *source=lookup(bank,"Source");
    Bank::Account *dest=lookup(bank,"Destination");
    Bank::Money amount=prompt_amount();

    // First hold money from the source.
    if(!source->try_withdraw(amount))
    {   std::cout << "Withdrawal not approved." << std::endl;
        return;
    }
    
    std::cout << "Withdrawal approved." << std::endl;
    print_balance(source);
    
    // Now deposit the money into the destination.
    if(!dest->deposit(amount))
    {
        std::cout << "Deposit failed." << std::endl;
        return;
    }
    
    std::cout << "Deposit completed." << std::endl;
    print_balance(dest);
    
    // Now complete the withdrawal.
    if(!source->withdraw(amount, amount))
    {
        std::cout << "Withdrawal failed." << std::endl;
        return;
    }
        
    std::cout << "Withdrawal completed." << std::endl;
    print_balance(source);
}

/**
 * @brief Post completed transactions on all accounts.
 * @param bank The bank containing the accounts.
 */
void post(Bank::AccountBank &bank)
{
    bank.post();
}

/**
 * @brief Print the ledger of all accounts.
 * @param bank The bank containing the accounts.
 */
void ledger(Bank::AccountBank &bank)
{
    // Print the header for the table.
    std::cout << "Account Number \tName \tBalance \tEffective \tAvailable" << std::endl;
    
    // Loop over the accounts in the ledger.
    for(auto &i: bank.ledger())
        // Print the account number, account holder and balances.
        print_balance(i.first, i.second.get());
}

/**
 * @brief Utility to prompt the user for an account number and find the account.
 * 
 * If an error is encountered, returns an invalid account. The name in the account is
 * the error message.
 * 
 * @param bank The bank containing the account.
 * @param label An optional label to speialize the prompt.
 * @return Pointer to the account which may be an invalid account.
 */
Bank::Account *lookup(Bank::AccountBank &bank, const std::string label)
{   Bank::Number acctno;

    if(label.length())
        std::cout << "Please enter the account number for " << label <<": ";
    else
        std::cout << "Please enter the account number for " << label <<": ";
        
    // Error handling is a little loose.
    if(!(std::cin >> acctno ))
        std::cout << "Warning: I could not understand what you said and am using 0 instead." << std::endl;

    Bank::Account *account=bank.lookup(acctno);
    print_balance(account);
    return account;
}

/**
 * @brief Utiltiy function to prompt the user for a transaction amount.
 * @return The transaction amount.
 */
Bank::Money prompt_amount()
{
    Bank::Money ret(0);
   
    std::cout << "Please enter the amount for the transaction: ";
    
    // Error handling is a little loose....
    if(!(std::cin >> ret))
        std::cout << "Warning: I could not understand what you said and am using 0 instead." << std::endl;

    return ret;     
}
