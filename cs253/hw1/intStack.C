/*
Parker Johnson, cs 253, 10/23/96
This is the .cpp file defining the functions implemented in the 
class declaration located in file calc.C
*/

#ifndef calc_c
#define calc_c


#include <iostream.h>

intStack::intStack(int MaxStackSize)		//constructor
{
	MaxSize=MaxStackSize;
	array=new int[MaxSize];
	top=1;
}


intStack::~intStack()		//destructor
{
	delete [] array;
}


Boolean intStack::IsFull()	//Checks array stack to see if full
{				//True if full, false otherwise
	if(top==MaxSize) return TRUE;
		else return FALSE;
}


Boolean intStack::IsEmpty()	//Checks array stack to see if empty
{				//True if empty, false otherwise
	if(top==-1) return TRUE;
		else return FALSE;
}


void intStack::Add(int x)	//Adds an int onto the stack unless stack full
{
	if (IsFull()) cerr<<"Stack Overflow"<<endl;
		else array[++top]=x;
}


int* intStack::Delete(int& x)
{
	if (IsEmpty()){
		return 0;
		cerr<<"Stack Underflow"<<endl;
		       }

	x=array[top];
	top--;
	return &x;
}

#endif

