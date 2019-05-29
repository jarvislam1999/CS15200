#include <stdio.h>

typedef unsigned int      uint;
typedef unsigned long int lint;

// function prototypes

// factorial
lint fact(uint n);

// exponentiation (nonnegative integer powers only)
double expt(double x, uint n);

// approximate pi
double tpi(uint n_terms);

//approximate exponential
double tex(uint n_terms, double x);

// approximate sin
double tsin(uint n_terms, double x);

// approximate cos
double tcos(uint n_terms, double x);

// ... function implementations here ...

// factorial
lint fact(uint n)
{
  if (n == 0)
    {
      return 1;
    }
  return n * fact(n - 1);
};

// exponentiation (nonnegative integer powers only)
double expt(double x, uint n)
{
  if (n == 0){
    return 1.0;
  };
  return x * expt(x, n - 1);
};

// approximate pi
double tpi(uint n_terms)
{
  if (n_terms == 0){
    return 0.0;
  }
  /**
   * GRADER: While using expt() is mathematically correct,
   * it actually slows down the execution of the fcn a lot
   * as n_terms increases
   * Avoid long lines of code - maintain <= 80 characters width
   * 
   */
 
  return (4 * expt(-1.0, n_terms + 1) * (1.0/(2.0 * n_terms - 1))) + tpi(n_terms - 1);
};

//approximate exponential
double tex(uint n_terms, double x)
{
  if (n_terms == 0){
    return 0.0;
  }
  return expt(x, n_terms - 1)/fact(n_terms - 1) + tex(n_terms - 1, x);
};

// approximate sin
double tsin(uint n_terms, double x)
{
  if (n_terms == 0){
    return 0.0;
  }
  uint a = n_terms * 2 - 1;
  return expt(-1.0, n_terms + 1) * expt(x, a)/fact(a) + tsin(n_terms - 1, x);
};

// approximate cos
double tcos(uint n_terms, double x)
{
  if (n_terms == 0){
    return 0.0;
  }
  uint a = (n_terms - 1) * 2;
  return expt(-1.0, n_terms + 1) * expt(x, a)/fact(a) + tcos(n_terms - 1, x);
};

// main program
int main()
{
  // test fact
  if (fact(0) != 1) {
    fprintf(stdout, "Factorial for %d yielded %lu, expected %d\n", 0, 
	    fact(0), 1);
  }
  else if (fact(3) != 6){
    fprintf(stdout, "Factorial for %d yielded %lu, expected %d\n", 3, 
	    fact(3), 6);
  }
  else if (fact(6) != 720){
    fprintf(stdout, "Factorial for %d yielded %lu, expected %d\n", 6, 
	    fact(6), 720);
  }
  else if (fact(9) != 362880){
    fprintf(stdout, "Factorial for %d yielded %lu, expected %d\n", 9, 
	    fact(9), 362880);
  }
  else {
    fprintf(stdout, "Everything seems fine for fact\n");
  }

  // test expt
  if (expt(20.0, 0) != 1.0){
    fprintf(stdout, "Power for %f^%d yielded %f, expected %f\n", 
	    20.0, 0, expt(20.0, 0), 1.0);
  }
  else if (expt(10.0, 2) != 100.0){
    fprintf(stdout, "Power for %f^%d yielded %f, expected %f\n", 
	    10.0, 2, expt(10.0, 2), 100.0);
  }
  else if (expt(1000.0, 3) != 1000000000.0){
    fprintf(stdout, "Power for %f^%d yielded %f, expected %f\n", 
	    1000.0, 3, expt(1000.0, 3), 1000000000.0);
  }
  else if (expt(2.0, 5) != 32.0){
    fprintf(stdout, "Power for %f^%d yielded %f, expected %f\n", 
	    2.0, 5, expt(2.0, 5), 32.0);
  }
  else if (expt(4.0, 4) != 256.0){
    fprintf(stdout, "Power for %f^%d yielded %f, expected %f\n", 
	    4.0, 4, expt(4.0, 4), 256.0);
  }
  else {
    fprintf(stdout, "Everything seems fine for expt\n");
  }  

  // test tpi
  if (tpi(0) != 0.0){
    fprintf(stdout, "Pi approximation for %d terms yielded %f, expected %f\n", 
	    0, tpi(0), 0.0);
  }
  else if (tpi(1) != 4.0){
    fprintf(stdout, "Pi approximation for %d terms yielded %f, expected %f\n", 
	    1, tpi(1), 4.0);
  }
  else if (tpi(3) != 52.0/15.0){
    fprintf(stdout, "Pi approximation for %d terms yielded %f, expected %f\n", 
	    3, tpi(3), 4.0 * 13.0/15.0);
  }
  else {
    fprintf(stdout, "Everything seems fine for tpi, approximation tpi(%d) = %f\n",
	   1500, tpi(1500));
  }

  // test tex
  if (tex(0, 0.0) != 0.0){
    fprintf(stdout, "E^%f approximation for %d terms yielded %f, expected %f\n",
	    0.0, 0, tex(0, 0.0), 0.0);
  }  
  else if (tex(2, 1.0) != 2.0){
    fprintf(stdout, "E^%f approximation for %d terms yielded %f, expected %f\n",
	    1.0, 2, tex(2, 1.0), 2.0);
  }
  else if (tex(2, 2.0) != 3.0){
    fprintf(stdout, "E^%f approximation for %d terms yielded %f, expected %f\n",
	    2.0, 2, tex(2, 2.0), 3.0);
  }
  else {
    fprintf(stdout, "Everything seems fine for tex, approximation tex(%d, %f) = %f\n",
	    50, 1.0, tex(50, 1.0));
  }
  
  // test tsin
  if (tsin(0, 0.0) != 0.0){
    fprintf(stdout, "Sin(%f) for %d terms yielded %f, expected %f\n", 
	    0.0, 0, tsin(0, 0.0), 0.0);
  }
  else if (tsin(1, 1.0) != 1.0){
    fprintf(stdout, "Sin(%f) for %d terms yielded %f, expected %f\n", 
	    1.0, 1, tsin(1, 1.0), 1.0);
  }
  else if (tsin(3, 1.0) != 101.0/120.0){
    fprintf(stdout, "Sin(%f) for %d terms yielded %f, expected %f\n", 
	    1.0, 3, tsin(3, 1.0), 101.0/120.0);
  }
  else if (tsin(1, 2.0) !=2.0){
    fprintf(stdout, "Sin(%f) for %d terms yielded %f, expected %f\n", 
	    2.0, 1, tsin(1, 2.0), 2.0);
  }
  else {
    fprintf(stdout, "Sin function appears to be functional\n");
    fprintf(stdout, "Example of proximation: tsin(%d, %f) = %f,\n",
	   15, 3.14, tsin(15, 3.14));
  }
  
  // test tcos
  if (tcos(0, 0.0) != 0.0){
    fprintf(stdout, "Cos(%f) approximation for %d terms yielded %f, expected %f", 
	    0.0, 0, tcos(0, 0.0), 0.0);
  }
  else if (tcos(1, 1.0) != 1.0){
    fprintf(stdout, "Cos(%f) approximation for %d terms yielded %f, expected %f", 
	    1.0, 1, tcos(1, 1.0), 1.0);
  }
  else if (tcos(3, 1.0) != 13.0/24.0){
    fprintf(stdout, "Cos(%f) approximation for %d terms yielded %f, expected %f", 
	    1.0, 3, tcos(3, 1.0), 13.0/24.0);
  }
  else if (tcos(1, 2.0) != 1.0){
    fprintf(stdout, "Cos(%f) approximation for %d terms yielded %f, expected %f", 
	    2.0, 1, tcos(1, 2.0), 1.0);
  }
  else {
    fprintf(stdout, "Cos function appears to be functional\n");
    fprintf(stdout, "Example of proximation: tcos(%d, %f) = %f,\n",
	   15, 3.14, tcos(15, 3.14));
  }
  
 /**
  * GRADER: great testing!
  */


  return 0; // Everything is OK!
}
