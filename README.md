# Lab 5 Refactoring Class Hierarchies

This assignment invovles refactoring the code to a banking system to support additional account types.

## Part 1. Setup.

1. Copy the HTTPS link for your Git repository on the GitHub website.
2. In CodeLite Git tab, clone the repository into your workspace. Then switch to the new repository.
3. If working on a lab machine, double-check that the permissions do not permit your classmates to access your work.
4. Create a new Console C++ project. Browse to the Git repository you cloned. Do not create a separate directory.
5. Right-click on the project name and fix the settings.
6. Right-click on the "src" folder in the project and add existing files. Select all the .cpp and .h files except main.cpp.
7. Delete the main.cpp file from the project.

After completing this assignment, your program should function just like initially. Run it now and play around with it to get a feel for how it works. Here is an example session:

```
Welcome to Simple Bank!

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
o
Please enter the name of the account holder: Henry Winchester
The new account number is 1001.

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
d
Please enter the account number for : 1001
Name    Balance         Effective       Available
Henry Winchester        0.00    0.00    0.00
Please enter the amount for the transaction: 23000
Deposit completed.
Name    Balance         Effective       Available
Henry Winchester        0.00    23000.00        0.00

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
o
Please enter the name of the account holder: Jerry Blake
The new account number is 1002.

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
d
Please enter the account number for : 1002
Name    Balance         Effective       Available
Jerry Blake     0.00    0.00    0.00
Please enter the amount for the transaction: 243
Deposit completed.
Name    Balance         Effective       Available
Jerry Blake     0.00    243.00  0.00

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
w
Please enter the account number for : 1002
Name    Balance         Effective       Available
Jerry Blake     0.00    243.00  0.00
Please enter the amount for the transaction: 120
Withdrawal not approved.

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
p

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
w
Please enter the account number for : 1002
Name    Balance         Effective       Available
Jerry Blake     243.00  243.00  243.00
Please enter the amount for the transaction: 250
Withdrawal not approved.

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
w
Please enter the account number for : 1002
Name    Balance         Effective       Available
Jerry Blake     243.00  243.00  243.00
Please enter the amount for the transaction: 100
Withdrawal approved.
Name    Balance         Effective       Available
Jerry Blake     243.00  243.00  143.00
Withdrawal completed.
Name    Balance         Effective       Available
Jerry Blake     243.00  143.00  143.00

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
l
Account Number  Name    Balance         Effective       Available
Henry Winchester        23000.00        23000.00        23000.00
Jerry Blake     243.00  143.00  143.00

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
t
Please enter the account number for Source: 1001
Name    Balance         Effective       Available
Henry Winchester        23000.00        23000.00        23000.00
Please enter the account number for Destination: 1002
Name    Balance         Effective       Available
Jerry Blake     243.00  143.00  143.00
Please enter the amount for the transaction: 50
Withdrawal approved.
Name    Balance         Effective       Available
Henry Winchester        23000.00        23000.00        22950.00
Deposit completed.
Name    Balance         Effective       Available
Jerry Blake     243.00  193.00  143.00
Withdrawal completed.
Name    Balance         Effective       Available
Henry Winchester        23000.00        22950.00        22950.00

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
l
Account Number  Name    Balance         Effective       Available
Henry Winchester        23000.00        22950.00        22950.00
Jerry Blake     243.00  193.00  143.00

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
p

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
l
Account Number  Name    Balance         Effective       Available
Henry Winchester        22950.00        22950.00        22950.00
Jerry Blake     193.00  193.00  193.00

What would you like to do? (Open Account, Check Balance, Deposit, Withdrawal, Transfer,
         Post Transactions, List Ledger or Exit)
quit
```

## Part 2. Generalize Savings Account (10 pts)
Your goal is to create a new Account class and a specialized SavingsAccount. Everything that currently refers to the SavingsAccount needs to change to referring to the Account.

The easist way to do this is to copy the files for SavingsAccount to equivalent files for Account and then use the search functionality to change all instances of SavingsAccount in the new files to just Account. Then look through the file to make sure you didn't miss anything.

## Part 3. Virtualize Account (20 pts)
In order to specialize Account, it will need to have virtual functions. Look through the functions in Account.h, and add virtual in front of any function if it might need different logic for different kinds of account. For example, the try_withdraw function in a loan account would always just fail.

Also, remember that constructors are never virtual and the parent class should always define a virtual destructor.

Remember to commit your changes and test before proceeding.

## Part 4. Remake Savings Account (20 pts)
Now it is time to create the new SavingsAccount class.

1. Right-click on "src" folder and select "New Class."
2. Class name: SavingsAccount
3. Namespace: Bank
4. Click "OK"
5. Edit SavingsAccount.h so that the class has Account as a parent class.
6. Selectively copy or move data and functionality from Account to SavingsAccount. In general, things that are useful in many different kinds of accounts do not need to be moved. Things that are unique to SavingsAccounts should be moved (put a more generic version of the function in Account).
7. Change the open function in the AccountBank class to create a SavingsAccount instead of an Account.
8. Test your work and commit.

## Part 5. Account Types (10 pts)
Augment your program so that it has these characteristics:

1. Account has a method that returns the type of account (savings, loan, etc.). For now, you just need two types (savings and error).
2. Modify the process for creating an account so that it prompts the user for the account type (only savings available for now) and uses the selected account type to make an account of the correct type.
3. Test that your program still works (of course, you can only create savings accounts) and commit.

## Part 6. Savings Enhancement (20 pts)
Add either one of the following functionality unique to savings accounts:

1. Each savings account is limited to a maximum of 3 withdrawals "per day." The count is reset when transactions are posted. That is, if you attempt to withdraw 4 times before picking "post," it should fail. Then, after picking "post," you should be able to do 3 more withdrawals.
2. Modify the savings account so that the interest rate can be specified. Modify the user interface so that the user can choose a "1% Savings" or a "0.2% Savings." Presumably they will have different balance requirements or fees, but we will not worry about that. Store the selected rate in the SavingsAccount class. Modify post so that it multiplies the balance by (1+rate/365.0).

## Submit

Make sure to push your changes and verify that the program is correctly submitted on GitHub.


