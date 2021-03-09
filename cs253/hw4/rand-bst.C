// Program: rand-bst.cpp see Exercise 2, page 299.
// This program computes the height of "random" BST's of various sizes.
#include <math.h>
#define no_main
#include "bst.cpp"
#undef no_main

// This is how we call functions from the standard C library:
extern "C" int rand();		// random integers, not too random
extern "C" int srand(unsigned);	// reset seed

// List of sizes, report Height at each size:
int size[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 
10000, 0};

void RandBst(int seed=1)	// grow a random BST tree through each size
{
  Element<int> e;		// element to update and insert
  BST<int> t;			// an empty tree
  int n=0;			// size of t

  srand(seed);			// set the seed
  cout << "Using seed: " << seed << endl;
  for (int i=0; size[i]; i++) {
    while (n < size[i]) {
      e.key=rand();		// a random integer
      t.Insert(e); n++;		// add random entry to tree
    }
    // Report current Height:
    cout << "With " << n << " nodes, tree Height is " << t.Height()<<" and the ratio height/log2n="<<t.Height()/(log(n)/log(2))<<endl;
  }
}

main(int argc, char *argv[])
{
  if (argc > 1)
    for (int i=1; i<argc; i++) {
      int seed=0;
      for (char *c = argv[i]; *c; c++) seed=10*seed+(*c-'0');
      RandBst(seed);
    }
  else
    RandBst();
}
