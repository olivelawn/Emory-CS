/*	Parker Johnson
	hw3.C
	2/24/96
*/
#include <iostream.h>
#include <stdlib.h>						//including libraries
#include "Stack.C"
#include "Mess.C"



main()
{
TreeNode *root;
Token x;
int done=0;
tok.type=1; tok.ch='#'; tok.num=0;	//setting up '#' token
op.Add(tok); 				//add it to the stack
  cout << "Infix Stack calculator: enter digits, (, ), ^, +, -, *, /, or q" << endl;

while(!done){

next_token();		//values in token tok are now set

cout<<"token values: type= "<<tok.type<<" ch= "<<tok.ch<<" num= "<<tok.num<<endl; 

  if (tok.type==2)  {done=1; continue;}   //case quit

  if (tok.type==0){    		//if token is a number
	TreeNode *T1=new TreeNode;
	T1->data=tok;
	T1->left=0;
	T1->right=0;
	tree.Add(T1); continue;
		  }

  if (tok.type==1){
            Token y;

	if((tok.type==1)&&(tok.ch==')')){

	for(y=*(op.Delete(y));  y.ch!='(';  y=*(op.Delete(y))){ do_op(y); }	
		  }

	else{	  
	  
	  for (y=*op.Delete(y); ISP(y.ch)<=ICP(tok.ch); y=*op.Delete(y)){ do_op(y); }	

	  op.Add(y);
	  op.Add(tok);
	    }

	continue;  }
     
           }							//end of while



for(x=*(op.Delete(x));  x.ch!='#';  x=*(op.Delete(x))) { do_op(x); }	
root=*tree.Delete(root);
InOrder(root);
}									//end of main()




