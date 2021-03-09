#ifndef intStack_C
#define intStack_C

/// A simple stack-based calculator.

/// Assignment:
//
// Do not modify this file at all.
//
// Rather, write the missing functions to finish implementing the
// intStack class (declared below), and put them in a file named
// intStack.C, which this file includes.
//
// When you are done, "CC calc.C" should compile to a program
// (a.out) which behaves like the examples in "calc.io".
//
// You will be graded primarily on the correct behavior of your
// program, and secondarily on the style of your code (it should be
// adequately commented).
//
// BIG HINT: the missing code is very similar to the "Bag" class code
// in Section 3.1 of your textbook.

/// Intention:
//
// This should be easy if you are familiar with C++ and our computing
// environment.   If you are not familiar with C++, you should be
// able to work it out from the code in the textbook (and take the
// opportunity to understand this program!)

#include <iostream.h>

enum Boolean {FALSE, TRUE};	// usual 0 and 1

int DefaultStackSize = 10;	// default size of a new stack

class intStack			// a stack of ints
{

// We will overload << to print out an intStack:
friend ostream& operator<<(ostream&, intStack&);

public:

  // Constructor and Destructor:
  intStack(int MaxStackSize = DefaultStackSize);
  ~intStack();			// should return any allocated memory

  Boolean IsFull();		// TRUE if stack is full, FALSE otherwise

  Boolean IsEmpty();		// TRUE if stack is empty, FALSE otherwise

  void Add(int);		// Push another int on the top of the stack.
				// Or if the stack is already full,
				// just print a warning message to cerr.

  int *Delete(int&);		// Pop the top int from the stack, and
				// return a copy by reference and pointer.
				// If the stack is empty, print a warning
				// message to cerr and return 0 (NULL pointer).

protected:
  int *array;			// the allocated array of ints
  int MaxSize;			// size of the array
  int top;			// max position containing an element,
				// or -1 when empty.

};

// Now we include the file that the student must write.  This file
// should implement the remaining intStack::* functions declared above.

// intStack friend for output
ostream& operator<<(ostream& os, intStack& b)
{
  for (int i = 0; i <= b.top; i++)
    os << b.array[i] << (i < b.top ? " " : "");
  // os << endl;
  return os;
}

// This main program implements a simple stack-based
// calculator.  The user types characters.  The system
// responds as follows:
//    '0' to '9':            push that digit (as an int) on the stack
//    '+', '-', '*', '/':    pop two operands, push the result
//    q or EOF:              quit.

main()
{
  intStack opstack;		// stack of "operands"
  int done=0, ch;

  cout << "Stack calculator: enter digits, +, -, *, /, or q" << endl;
  while (!done) {
    ch = cin.get();		// read another character, or EOF
    switch (ch) {
    case 'q': case 'Q': case EOF:
      done = 1;			// all done
      continue;
    case ' ': case '\t': case '\n': case '\r':
      // silently ignore whitespace
      continue;
    case '+': case '-': case '*': case '/':
      // Each of these operators pops two operands,
      // and pushes back one result.
      {
	int op1, op2, result;
	if (opstack.Delete(op1) &&
	    opstack.Delete(op2))
	  {
	    switch (ch) {
	    case '+': result = op2+op1; break;
	    case '-': result = op2-op1; break;
	    case '*': result = op2*op1; break;
	    case '/': result = op2/op1; break;
	    }
	    opstack.Add(result);
	  }
	else
	  continue;
      }
      break;
    default:
      if (ch >= '0' && ch <= '9')
	{
	  opstack.Add(ch - '0'); // assumes ASCII character set
	  break;
	}
      cerr << "unexpected character: '" << (char) ch << "'" << endl;
      continue;
    }				// switch (ch)
    // Now print out the stack.
    // Note the various "continue" statements above skip this step.
    cout << "Stack after '" << (char) ch << "': " << opstack << endl;
  }				// while (!done)
  return 0;
}
#endif
