#ifndef _HW3_H_
#define _HW3_H_

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int date_t_;
typedef unsigned int time_t_;
typedef unsigned int account_number_t;
typedef long int amount_t;

struct check {
  unsigned short check_number;
  date_t_ date;
  account_number_t from_account;
  char *to_whom;
  amount_t amount;
};

typedef struct check check_t;

struct withdrawal {
  date_t_ date;
  time_t_ time;
  account_number_t from_account;  
  amount_t amount;
};

typedef struct withdrawal withdrawal_t;

struct deposit {
  date_t_ date;
  time_t_ time;
  account_number_t to_account;
  amount_t amount;
};

typedef struct deposit deposit_t;

struct transfer {
  date_t_ date;
  time_t_ time;
  account_number_t from_account;
  account_number_t to_account;
  amount_t amount;
};

typedef struct transfer transfer_t;

union transaction_union {
  check_t      chk;
  withdrawal_t wth;
  deposit_t    dep;
  transfer_t   trn;
};

enum transaction_type { CHECK, WITHDRAWAL, DEPOSIT, TRANSFER };

struct tagged_transaction {
  enum transaction_type tag;
  union transaction_union t;
};

typedef struct tagged_transaction transaction_t;

struct account {
  account_number_t account_number;
  amount_t balance;
};

typedef struct account account_t;

struct customer {
  char *lname;
  unsigned char num_accounts;
  account_t **accounts; // a pointer to an array of account pointers
};

typedef struct customer customer_t;

// write account information to stdout
void show_account(account_t *acc);

// write transaction information to stdout
void show_transaction(transaction_t *trx);

// return a pointer to the given account if present, return NULL otherwise
account_t *find_account(customer_t *cust, account_number_t num);

// return the account with the highest balance
// if there is more than one account sharing the max balance, return any one
// if there are no accounts, return NULL
account_t *max_account(customer_t *cust);

// return the total balance of all accounts
amount_t total_balance(customer_t *cust);

// if the transaction is a check, subtract the amount from the given account
// if the transaction if a widthdrawal, subtract the amount from the given account
// if the transaction is a deposit, add the amount to the given account
// if the transaction is a transfer, subtract from one account and add to another
// in all cases, print an error message and exit if one or both accounts are not found
// in all cases, print a message to stderr summarizing the transaction
void apply_transaction(customer_t *cust, transaction_t *trx);

// apply all transactions in an array of transactions
void apply_transactions(customer_t *cust, transaction_t *trx, unsigned int n);

// build an array of checks
// return a pointer to that array and write its size into n_out
check_t *checks(transaction_t *trx, unsigned int n_in, unsigned int *n_out);

#endif /* _HW3_H_ */
