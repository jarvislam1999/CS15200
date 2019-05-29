#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hw3.h"


// write account information to stdout
void show_account(account_t *acc){
  if(acc == NULL){
    fprintf(stderr, "Cannot print out null pointer for account\n");
  } else {
    fprintf(stdout, "Account number is: %u \n", acc->account_number);
    fprintf(stdout, "Account balance is: %ld \n", acc->balance);
  };
  return;
};


// write transaction information to stdout
void show_transaction(transaction_t *trx){
  if(trx == NULL){
    fprintf(stderr, "Cannot print out null pointer for transaction\n");
  } else {
    if (trx->tag == CHECK){                    //CHECK transaction
      fprintf(stdout, "Transaction type is: CHECK \n");
      fprintf(stdout, "Check number is: %hu \n", trx->t.chk.check_number);
      fprintf(stdout, "Check deposit date is: %u \n", trx->t.chk.date);
      fprintf(stdout, "Check from account: %u \n", trx->t.chk.from_account);
      fprintf(stdout, "Check is made to: %s \n", trx->t.chk.to_whom);
      fprintf(stdout, "Check amount is: %ld \n", trx->t.chk.amount);
    };
    if (trx->tag == WITHDRAWAL){              //WITHDRAWAL transaction
      fprintf(stdout, "Transaction type is: WITHDRAWAL \n");
      fprintf(stdout, "Withdrawal date is: %u \n", trx->t.wth.date);
      fprintf(stdout, "Withdrawal time is: %u \n", trx->t.wth.time);
      fprintf(stdout, "Withdrawal from account: %u \n",
	      trx->t.wth.from_account);
      fprintf(stdout, "Withdrawal amount is: %ld \n", trx->t.wth.amount);
    };
    if (trx->tag == DEPOSIT){                 //DEPOSIT transaction
      fprintf(stdout, "Transaction type is: DEPOSIT \n");
      fprintf(stdout, "Deposit date is: %u \n", trx->t.dep.date);
      fprintf(stdout, "Deposit time is: %u \n", trx->t.dep.time);
      fprintf(stdout, "Deposit from account: %u \n", trx->t.dep.to_account);
      fprintf(stdout, "Deposit amount is: %ld \n", trx->t.dep.amount);
    };
    if (trx->tag == TRANSFER){                //TRANSFER transaction
      fprintf(stdout, "Transaction type is: TRANSFER \n");
      fprintf(stdout, "Transfer date is: %u \n", trx->t.trn.date);
      fprintf(stdout, "Transfer time is: %u \n", trx->t.trn.time);
      fprintf(stdout, "Transfer from account: %u \n", trx->t.trn.from_account);
      fprintf(stdout, "Transfer to account: %u \n", trx->t.trn.to_account);
      fprintf(stdout, "Transfer amount is: %ld \n", trx->t.trn.amount);
    };    
  };
  return;
};


// return a pointer to the given account if present, return NULL otherwise
account_t *find_account(customer_t *cust, account_number_t num){
  if (cust == NULL) {
    fprintf(stderr, "Null customer was passed\n");
  } else {
    for (int i = 0; i < cust->num_accounts; i++){ //Find account matching num
      if ( (*(*((cust->accounts) + i))).account_number == num){
	return *((cust->accounts) + i);
      };
    };
  };
  return NULL;
};


// return the account with the highest balance
// if there is more than one account sharing the max balance, return any one
// if there are no accounts, return NULL
account_t *max_account(customer_t *cust){
  if (cust == NULL) {
    fprintf(stderr, "Null customer was passed\n");
  } else {
    if (cust->num_accounts == 0){
      return NULL;
    };
    account_t *max_out = *(cust->accounts);   // Initialize max variable
    for (int i = 0; i < cust->num_accounts; i++){ //Update max in for loop
      if ( (*(*((cust->accounts) + i))).balance > (*max_out).balance){
	max_out = *((cust->accounts) + i);
      };
    };
    return max_out;
  };
  return NULL;
};


// return the total balance of all accounts
amount_t total_balance(customer_t *cust){
  if (cust == NULL) {
    fprintf(stderr, "Null customer was passed\n");
  } else {
    if (cust->num_accounts == 0){
      return 0;
    };
    amount_t total_out = 0;   //Initialize sum variable
    for (int i = 0; i < cust->num_accounts; i++){ //Add to sum in for loop
      total_out += (*(*((cust->accounts) + i))).balance;
    };
    return total_out;
  };
  return 0;
};


// if the transaction is a check, subtract the amount from the given account
// if the transaction if a widthdrawal, subtract the amount from the given account
// if the transaction is a deposit, add the amount to the given account
// if the transaction is a transfer, subtract from one account and add to another
// in all cases, print an error message and exit if one or both accounts are not found
// in all cases, print a message to stderr summarizing the transaction
void apply_transaction(customer_t *cust, transaction_t *trx){
  if (cust == NULL) {
    fprintf(stderr, "Null customer was founded for transaction \n");
  } else if (trx == NULL){
    fprintf(stderr, "Null transaction was found for customer \n");
  } else {
    if (trx->tag == CHECK){                //CHECK transaction
      if(trx->t.chk.amount <= 0) {         //Negative amount test
	fprintf(stdout,
		"Warning: Transaction amount negative, will proceed\n");
      };
      fprintf(stderr, "Begin CHECK transaction: \n");
      account_t *check_account = find_account(cust, trx->t.chk.from_account);
      if (check_account == NULL){
	fprintf(stderr, "Failed to secure account for CHECK transaction \n");
	return;
      } else {
	check_account->balance -= trx->t.chk.amount;
      };
      fprintf(stderr,
	      "CHECK transaction finished, account info after transaction:\n");
      show_account(check_account);
      fprintf(stderr, "CHECK amount: %ld \n", trx->t.chk.amount);
      return;
    };
    if (trx->tag == WITHDRAWAL){                //WITHDRAWAL transaction
      if(trx->t.wth.amount <= 0) {              //Negative amount test
	fprintf(stdout,
		"Warning: Transaction amount negative, will proceed\n");
      };
      
      fprintf(stderr, "Begin WITHDRAWAL transaction: \n");
      account_t *withd_account = find_account(cust, trx->t.wth.from_account);
      if (withd_account == NULL){
	fprintf(stderr,
		"Failed to secure account for WITHDRAWAL transaction\n");
	return;
      } else {
	withd_account->balance -= trx->t.wth.amount;
      };
      fprintf(stderr,
	      "WITHDRAWAL transaction finished, act info after transaction:\n");
      show_account(withd_account);
      fprintf(stderr, "WITHDRAWAL amount: %ld \n", trx->t.wth.amount);
      return;
    };
    if (trx->tag == DEPOSIT){              //DEPOSIT transaction
      if(trx->t.dep.amount <= 0) {         //Negative amount
	fprintf(stdout,
		"Warning: Transaction amount negative, will proceed\n");
      };
      fprintf(stderr, "Begin DEPOSIT transaction: \n");
      account_t *withd_account = find_account(cust, trx->t.dep.to_account);
      if (withd_account == NULL){
	fprintf(stderr,"Failed to secure account for DEPOSIT transaction\n");
	return;
      } else {
	withd_account->balance += trx->t.dep.amount;
      };
      fprintf(stderr,
	      "DEPOSIT transaction finished, act info after transaction:\n");
      show_account(withd_account);
      fprintf(stderr, "DEPOSIT amount: %ld \n", trx->t.dep.amount);
      return;
    };
    if (trx->tag == TRANSFER){                //TRANSFER transaction
      if(trx->t.trn.amount <= 0) {            //Negative amount test
	fprintf(stdout,
		"Warning: Transaction amount negative, will proceed\n");
      };
      fprintf(stderr, "Begin TRANSFER transaction: \n");
      account_t *from_account = find_account(cust, trx->t.trn.from_account);
      account_t *to_account = find_account(cust, trx->t.trn.to_account);
      if (from_account == NULL){
	fprintf(stderr,
		"Failed to secure origin account for TRANSFER transaction\n");
	return;
      } else if (to_account == NULL){
	fprintf(stderr,
		"Failed to secure destination act for TRANSFER txn\n");
	return;
      } else {
	from_account->balance -= trx->t.trn.amount;
	to_account->balance += trx->t.trn.amount;
      };
      fprintf(stderr, "TRANSFER transaction finished, account info for ");
      fprintf(stdout,
	      "origin and destination respectively after transaction: \n");
      show_account(from_account);
      show_account(to_account);
            fprintf(stderr, "TRANSFER amount: %ld \n", trx->t.trn.amount);
      return;
    };
  };
  return;
};


// apply all transactions in an array of transactions
void apply_transactions(customer_t *cust, transaction_t *trx, unsigned int n){
  if (cust == NULL) {
    fprintf(stderr, "Null customer was founded for transaction \n");
  } else if (trx == NULL){
    fprintf(stderr, "Null transaction was found for customer \n");
  } else {
    for (int i = 0; i < n; i++) {    //Execute transactions in for loop
      apply_transaction(cust, trx + i);
      fprintf(stderr, "\n");
    };
  };
  return;
};


// build an array of checks
// return a pointer to that array and write its size into n_out
check_t *checks(transaction_t *trx, unsigned int n_in, unsigned int *n_out){
  //I will assume this means building an array out of a series of transactions
  //and only taking the check transactions
  if (trx == NULL) {
    fprintf(stderr, "Null transaction \n");
  } else if (n_out == NULL){
    fprintf(stderr, "Need non-null pointer to assign n-out to\n");
  } else {    
    (*n_out) = 0; //Set n_out to zero
    for (int i = 0; i < n_in; i++) {   // Calculate length of array
      if ((trx + i)->tag == CHECK){
	(*n_out) += 1;	
      };
    };
    check_t *checks_out = malloc(sizeof(check_t) * (*n_out));//Initialize array
    int count = 0;
    for (int i = 0; i < n_in; i++) {   // Fill in array with checks
      if ((trx + i)->tag == CHECK){
	*(checks_out+count) = (trx +i)->t.chk;
	count += 1;
      };
    };
    return checks_out;
  };
  return NULL;
};


int main(){
  account_t checking = {1111,1000};
  account_t checking_ = {1111,1000};
  account_t savings  = {2222,5500};
  account_t savings_  = {2222,5500};
  account_t checking2  = {3333,2200};
  account_t checking2_  = {3333,2200};
  account_t savings2  = {4444,3400};
  account_t savings2_  = {4444,3400};
  account_t savings3  = {5555,4200};
  account_t savings3_  = {5555,4200};
  
  account_t *accs[5] = {&checking, &savings, &checking2, &savings2, &savings3};
  account_t *accs1[2] = {&checking_, &checking2_};
  account_t *accs2[3] = {&savings_, &savings2_, &savings3_};
  
  customer_t jar = {"Jarvis",5,accs};
  customer_t jar1 = {"Nhat", 2, accs1};
  customer_t jar2 = {"Tin", 3, accs2};
  
  
  // Testing show_account()
  fprintf(stdout, "Customer Jarvis has account numbers %u, %u, %u, %u, %u \n",
	  1111, 2222, 3333, 4444, 5555);
  fprintf(stdout, "Customer Nhat has account numbers %u, %u \n",
	  1111, 3333);
  fprintf(stdout, "Customer Tin has account numbers %u, %u, %u \n",
	  2222, 4444, 5555);
  fprintf(stdout, "\n \n");

  fprintf(stdout, "Testing show_account() \n");
  fprintf(stdout, "Information for account number %u, balance %ld \n",
	  checking.account_number, checking.balance);
  show_account(&checking);
  fprintf(stdout, "Information for account number %u, balance %ld \n",
	  savings.account_number, savings.balance);
  show_account(&savings);
  fprintf(stdout, "Information for account number %u, balance %ld \n",
	  checking2.account_number, checking2.balance);
  show_account(&checking2);
  fprintf(stdout, "Information for account number %u, balance %ld \n",
	  savings2.account_number, savings2.balance);
  show_account(&savings2);
  fprintf(stdout, "Information for account number %u, balance %ld \n",
	  savings3.account_number, savings3.balance);
  show_account(&savings3);
  fprintf(stdout, "\n \n");

  
  // Testing find_account()
  fprintf(stdout, "Testing find_account() \n");
  fprintf(stdout, "Information for account number %u for Jarvis:\n", 4444);
  show_account(find_account(&jar,4444));
  fprintf(stdout, "Information for account number %u for Jarvis:\n", 1111);
  show_account(find_account(&jar,1111));
  fprintf(stdout, "Information for account number %u for Jarvis\n", 3223);
  show_account(find_account(&jar,3223));
  fprintf(stdout, "Information for account number %u for Nhat: \n", 3333);
  show_account(find_account(&jar1,3333));
  fprintf(stdout, "Information for account number %u for Nhat: \n", 4444);
  show_account(find_account(&jar1,4444));
  fprintf(stdout, "\n \n");


  // Testing max_account()
  fprintf(stdout, "Testing max_account() \n");
  fprintf(stdout,"Jarvis expects the highest balance in his 2222 account:\n");
  fprintf(stdout, "Result of maximum function: \n");
  show_account(max_account(&jar));
  fprintf(stdout, "Nhat expects the highest balance in his 3333 account: \n");
  fprintf(stdout, "Result of maximum function: \n");
  show_account(max_account(&jar1));
  fprintf(stdout, "Tin expects the highest balance in his 2222 account: \n");
  fprintf(stdout, "Result of maximum function: \n");
  show_account(max_account(&jar2));
  fprintf(stdout, "\n \n");


  // Testing total_balance()
  fprintf(stdout, "Testing total_balance() \n");
  fprintf(stdout,"Jarvis' total balance is %ld, expecting %d\n",
	  total_balance(&jar), 16300);
  fprintf(stdout,"Nhat's total balance is %ld, expecting %d\n",
	  total_balance(&jar1), 3200);
  fprintf(stdout,"Tin's total balance is %ld, expecting %d\n",
	  total_balance(&jar2), 13100);
  fprintf(stdout, "\n \n");


  // Checking apply_transaction()
  fprintf(stdout, "Testing apply_transaction() \n");
  deposit_t d0 = {20190206,0,2222,100};
  transaction_t t0;
  t0.tag = DEPOSIT;
  t0.t.dep = d0;
  fprintf(stdout,"Testing deposit on Jarvis' following account: \n");
  show_account(find_account(&jar, 2222));
  apply_transaction(&jar,&t0);
  fprintf(stdout, "\n \n");
  
  check_t c0 = {125,20190206,3333,"Tin",200};
  t0.tag = CHECK;
  t0.t.chk = c0;
  fprintf(stdout,"Testing checking on Nhat's following account: \n");
  show_account(find_account(&jar1, 3333));
  apply_transaction(&jar1,&t0);
  fprintf(stdout, "\n \n");

  withdrawal_t w0 = {20190206,0,4444,1200};
  t0.tag = WITHDRAWAL;
  t0.t.wth = w0;
  fprintf(stdout,"Testing withdrawal on Tin's following account: \n");
  show_account(find_account(&jar2, 4444));
  apply_transaction(&jar2,&t0);
  fprintf(stdout, "\n \n");

  withdrawal_t w1 = {20190206,0,4444,1200};
  t0.tag = WITHDRAWAL;
  t0.t.wth = w1;
  fprintf(stdout,"Testing withdrawal on Nhat's non-existent account: \n");
  show_account(find_account(&jar1, 4444));
  apply_transaction(&jar1,&t0);
  fprintf(stdout, "\n \n");

  transfer_t tr0 = {20190206,0,2222,4444,1200};
  t0.tag = TRANSFER;
  t0.t.trn = tr0;
  fprintf(stdout,"Testing withdrawal on Jarvis's following accounts: \n");
  show_account(find_account(&jar, 2222));
  show_account(find_account(&jar, 4444));
  apply_transaction(&jar,&t0);
  fprintf(stdout, "\n \n");

  transfer_t tr1 = {20190206,0,1111,4444,1200};
  t0.tag = TRANSFER;
  t0.t.trn = tr1;
  fprintf(stdout,"Testing withdrawal on Tin's non-existent accounts: \n");
  show_account(find_account(&jar2, 1111));
  show_account(find_account(&jar2, 4444));
  apply_transaction(&jar2,&t0);
  fprintf(stdout, "\n \n");


  // Testing apply_transactions()
  fprintf(stdout, "Testing apply_transactions() \n");
  fprintf(stdout,
	  "Testing transfer, check, deposit, transfer on Jarvis' accounts:\n");
  transaction_t t1;
  t1.tag = TRANSFER;
  t1.t.trn = tr1;
  transaction_t t2;
  t2.tag = CHECK;
  t2.t.chk = c0;
  transaction_t t3;
  t3.tag = DEPOSIT;
  t3.t.dep = d0;
  transaction_t t4;
  t4.tag = TRANSFER;
  t4.t.trn = tr0;
  
  transaction_t t[4] = {t1, t2, t3, t4};

  check_t c1 = {500,20190206,3333,"Tin",200};
  transaction_t t5;
  t5.tag = CHECK;
  t5.t.chk = c1;

  check_t c2 = {125,20190206,5555,"Nhat",150};
  transaction_t t6;
  t6.tag = CHECK;
  t6.t.chk = c2;

  check_t c3 = {86,20190206,2222,"Tin",230};
  transaction_t t7;
  t7.tag = CHECK;
  t7.t.chk = c3;

  transaction_t t10[7] = {t1, t2, t5, t3, t6, t4, t7};

  apply_transactions(&jar,t,4);
  fprintf(stdout, "\n \n");

  fprintf(stdout, "Testing transfer, check, check, deposit, check, ");
  fprintf(stdout, "transfer, check on Jarvis' accounts:\n");
  apply_transactions(&jar,t10,7);
  fprintf(stdout, "\n \n");


  // Testing checks()
  unsigned int n_out_ = 0;
  fprintf(stdout, "Testing checks() for the latest series of transactions:\n");
  check_t *checks_test = checks(t10, 7, &n_out_);
  fprintf(stdout, "Number of CHECK transactions: %u\n", n_out_);
  for (int i = 0; i < n_out_; i++) {
    fprintf(stdout, "Check no: %d\n", i+1);
    fprintf(stdout, "Check number: %hu\n", (*(checks_test+i)).check_number);
    fprintf(stdout, "Check date: %u\n", (*(checks_test+i)).date);
    fprintf(stdout,
	    "Check account number: %u\n",(*(checks_test+i)).from_account);
    fprintf(stdout, "Check receiver: %s\n", (*(checks_test+i)).to_whom);
    fprintf(stdout, "Check amount: %ld\n", (*(checks_test+i)).amount);
    fprintf(stdout, "\n");
  };

  free(checks_test);

  return 0;
};
