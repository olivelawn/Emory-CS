/* ----------------------------------------------------------------------
 *
 *		author	:  Mark A. Weiss, ch. 5
 *		adapted	:  Sarah E. Chodrow
 *		project	:  CS 253, Fall 1997
 *		created	:  25 September 1997
 *		edited	:  25 September 1997
 *
 *			max-sum.C
 *
 *	Three solutions to the maximum contiguous subsequence
 *	problem, i.e., given the (possibly negative) integers
 *	A1...An, find (and identify) the sequence corresponding
 *	to the maximum sum.  (The empty sequence has sum 0).
 *
 *	These routines do not bother to maintain the location
 *	Of the maximum subsequence.
 *
 *	Etype: must have constructor from int, must have
 *	    += and > defined, must have copy constructor
 *	    and operator=, and must have all properties
 *	    needed for Vector
 *
 * ---------------------------------------------------------------------- */

#include	<iostream.h>		// i/o library
#include	<stdlib.h>
#include	"vector.h"		// we use the Vector class


// The simple O( n^3) algorithm

template <class Etype>
Etype max_subsequence_sum1( const Vector<Etype> & array, int n)
{
  Etype max_sum = 0;

  for (int ii = 0; ii < n; ii++)
    for (int jj = ii; jj < n; jj++) {
      Etype this_sum = 0;
      
      for (int kk = ii; kk <= jj; kk++)
	this_sum += array[kk];

      if (this_sum > max_sum)
	max_sum = this_sum;
    }

  return max_sum;
}

// A better O( n^2) algorithm
template <class Etype>
Etype max_subsequence_sum2( const Vector<Etype> & array, int n)
{
  Etype max_sum = 0;

  for (int ii = 0; ii < n; ii++) {
    Etype this_sum = 0;
    for (int jj = ii; jj < n; jj++) {
      this_sum += array[jj];

      if (this_sum > max_sum)
	max_sum = this_sum;
    }
  }

  return max_sum;
}

template <class Etype>
Etype max_subsequence_sum3( const Vector<Etype> & array, int n)
{
  Etype this_sum = 0;
  Etype max_sum = 0;

  for (int ii = 0, jj = 0; jj < n; jj++) {
    this_sum += array[jj];

    if (this_sum > max_sum)
      max_sum = this_sum;
    else {  flag= jj-1;
	if (this_sum < 0) {
        ii = jj + 1;       // ii is used only if SeqStart is needed
        this_sum = 0;
    			  }
         } 
   }
  return max_sum;
}

main( void)
{
  const int array_size = 1000;
  Vector<int> test( array_size);

  for (int ii = 0; ii < array_size; ii++)
    test[ii] = rand() % 100 - 50;

  cout << max_subsequence_sum3( test, array_size) << endl;
  cout << max_subsequence_sum2( test, array_size) << endl;
  cout << max_subsequence_sum1( test, array_size) << endl;

  return 0;
}
