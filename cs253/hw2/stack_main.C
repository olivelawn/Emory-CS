/*
	Parker Johnson
	file: stack_main.C
	2/4/96
*/

#include <stdlib.h>						//including libraries
#include <iostream.h>
#include "Stack.C"

template <class KeyType>
void Stack<KeyType>::StackEmpty(){ cerr<<"Error:Stack empty or user inputed neg exp"<<endl; exit(1);}

template <class KeyType>
void Stack<KeyType>::StackFull(){ cerr<<"Stack full"<<endl; exit(1);}



void do_math(int);
int ISP(int);				//prototypees for InStackPriority, InComingPriotiy, power2
int ICP(int);
long power2(long  x, long n);

  Stack <long> num;			//stack declaration to hold longs
  Stack <char> op;			//stack declaration to hold chars

main()
{
  op.Add('#');

  int done=0, ch; 
  char x=0;
  long ANS;			//int declaration done and ch

  cout << "Infix Stack calculator: enter digits, (, ), ^, +, -, *, /, or q" << endl;
 

   while (!done) {
    ch = cin.get();		// read another character, or EOF

    switch (ch) {

    case 'q': case 'Q': case EOF:
      done = 1;			// all done
      continue;

    case ' ': case '\t': case '\n': case '\r':
      // silently ignore whitespace
      continue;



//------------------------------------------------------------------------------------------------------------
    case '+':  case '-':  case '*':  case '/':  case '^':  case '(':  case ')':
      char y;
     	
	if(ch==')')
		for(y=*(op.Delete(y));  y!='(';  y=*(op.Delete(y))){ do_math(y); }	//deletes until '('

//-----------------------------------------------------------------
	else{	  

	  for (y=*op.Delete(y); ISP(y)<=ICP(ch); y=*op.Delete(y)){ do_math(y); }	

	  op.Add(y);
	  op.Add(ch);
	    }

	continue;
//-----------------------------------------------------------------------------------------------------------
    

     default:
      if (ch >= '0' && ch <= '9')
	{
	  num.Add(ch-'0');
	  break;
	}
      cerr << "unexpected character: '" << (char) ch << "'" << endl;
      continue;
    }									//end of switch

//--------------------------------------------------------------end of main

}
while(*(op.Delete(x))!='#'){do_math(x);}
ANS=*num.Delete(ANS);
cout<<"Answer is: "<<ANS<<endl;
}									//end of main()




int ISP (int input)
{
  if (input=='^') return 2;
  if ((input=='*')||(input=='/')) return 3;
  if ((input=='+')||(input=='-')) return 4;
  if (input==')') return 5;
  if (input=='(') return 6;
  if (input=='#') return 6;

}


int ICP (int input)
{
  if (input=='(') return 0;
  if (input=='^') return 1;
  if ((input=='*')||(input=='/')) return 3;
  if ((input=='+')||(input=='-')) return 4;
  if (input==')') return 5;
}


long power2(long x, long n)
{
  long int ret=1.0;
   if(n>=0){
     for (int i=1; i<=n; i+=i, x *=x)
	if (i&n) ret *=x;
     return ret;
	   }
   else
      cerr<<"Exponents may not be negative"<<endl;
      exit(1);
}



void do_math(int input)
{
  long op1, op2, result;
    if ((num.Delete(op1))&&(num.Delete(op2))){
	switch(input){
	case '+': result=op2+op1; break;		
	case '-': result=op2-op1; break;
	case '*': result=op2*op1; break;
	case '/': result=op2/op1; break;
	case '^': result=power2(op2, op1);
		     }
					     }
	num.Add(result);
}
