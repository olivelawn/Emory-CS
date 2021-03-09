The following is a copy of program 3.19 from the book,
with some extra comments at the end. This is NOT working
code.  For your Homework #2 assignment, you need to adapt
this to:  read the expression from standard input,
immediately evaluate the output postfix expression on a
second stack, print more informative error messages, and
output the final answer.  --- Mic


void postfix(expression e)
// Output the postfix form of the infix expression e. NextToken
// and stack are as in function eval (Program 3.18).  It is assumed
// that the last token in e is '#'.  Also, '#' is used at the bottom
// of the stack.
{
  Stack<token> stack; // initialize stack of tokens (operators)
  token y;
  stack.Add('#');
  for (token x = NextToken(e); x != '#'; x = NextToken(e))
  {
    if (x is an operand) cout << x;  // immediately output numbers
    else if (x == ')') // unstack and output operators until '('
      for (stack.Delete(y); y != '('; stack.Delete(y)) cout << y;
    else { // x is an operator, or '('      
      // output stacked operators of "higher" or equal priority.
      for (stack.Delete(y); isp(y) <= icp(x); stack.Delete(y)) cout << y;
      stack.Add(y); // restore the last unstacked y
      stack.Add(x);
    }
  }
  // end of expression, empty the stack:
  while (!stack.IsEmpty()) cout << *stack.Delete(y);
} // end of postfix


Extra Comments on the "token" type:

The book is not clear about tokens.   For our purposes
it suffices for a token to be a char, and for an expression
to be an array of tokens (a "string", terminated by '#'):
	typedef char token;
	typedef token *expression;
	token NextToken(expression &e) { return *e++; }
See "hello.C" for a simple program that exercises these.

Extra Comments on isp(y) and icp(x):

These functions (probably implemented with 'switch'),
compute the "priorities" of operators. 
  icp(x) == the "in-coming priority" of the new token x
  isp(y) == the "in-stack priority" of stacked token y
The way the book has chosen to do things, larger numbers
correspond to "lower" priority.
The following values are suggested by the book:

Token		icp		isp
-----		---		---
 '('		0		8
 '#'		unused		8
 '+', '-'	3		3
 '*', '/'	2		2
 '^'		???		???

Note that isp=8 makes it impossible for any operator
(except ')') to pop a '(' or '#' from the stack.
Likewise icp('(')=0 makes sure that we pop *nothing*
from the stack when we read a '('.

A central part of your assignment is to figure out how to
fill in the two blank "???" entries.  Hint: you are free
to change the other priorities to "make room". 
