/*	Parker Johnson
	hw3.C
	2/24/96
*/
#include <iostream.h>
#include <stdlib.h>						//including libraries
#include "Stack.C"   //****impt  I included the cerr mess for empty there!!!
//#include "Mess.C"
//Mess.C


  struct Token{
	int type;   	//0 for an integer 1 for character
	char ch;	//char value
	long num;	//long value
	      };	


  struct TreeNode{     			
	Token data;		//token of type, ch, num
	TreeNode *left;		//ptr to left child
	TreeNode *right;	//ptr to right child
		 };


  Token tok;			//global token
  Stack <Token> op;		//global stack of tokens
  Stack <TreeNode *> tree;	//global stack of ptrs to treenode


void next_token()		//function to read in tokens from std in
{
  int done=0; tok.ch=' '; tok.num=0;
  int input=cin.get();

while(!done){
	switch(input){

	  case 'Q': case 'q':
 		tok.type=2;		//set type to 2 for quit
		done=1; continue;

	  case '+': case '-': case '*': case '/': case '^': case '(': case ')':
		tok.type=1;		//set type to 1 if char
		tok.ch=input;
		tok.num=0;
		done=1; continue;

	  case ' ': case '\t': case 'n': case 'r':
	  //silently ignore white space
	  continue;

	  default:
		if((input>='0')&&(input<='9')){
       		  input=input-'0';

		    while ((cin.peek()>='0')&&(cin.peek()<='9')){
			input=input*10 + (cin.get()-'0');
								}
		 tok.type=0;		//set type to 0 if long
		 tok.num=input;
					      }
		done=1; continue;
				
			}  //end of switch statement
	   }   //end of while loop
}   //end of next_tokenfunction


int ISP (int input)			//in-stack priority
{
  if (input=='^') return 2;
  if ((input=='*')||(input=='/')) return 3;
  if ((input=='+')||(input=='-')) return 4;
  if (input==')') return 5;
  if (input=='(') return 6;
  if (input=='#') return 6;

}


int ICP (int input)			//in-coming stack priority
{
  if (input=='(') return 0;
  if (input=='^') return 1;
  if ((input=='*')||(input=='/')) return 3;
  if ((input=='+')||(input=='-')) return 4;
  if (input==')') return 5;
}


long power2(long x, long n)		//mic's bit masking func for power
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



void do_op(Token op)			//my func to pop of ptrs to bintrees
{
  TreeNode *T1, *T2, *a;
    if ((tree.Delete(T1))&&(tree.Delete(T2))){
	a=new TreeNode;
	a->data=op; a->left=T2; a->right=T1;
	tree.Add(a);
					      }
}


void InOrder(TreeNode *current)		//my recursive func to print out bintree
{					//with appropriate parens
  if (current->left){
	cout<<"(";
	InOrder(current->left);

        if(current->data.type==1)	cout<<current->data.ch;
        if(current->data.type==0)	cout<<"("<<current->data.num;

	InOrder(current->right);
	cout<<")";
	      }
  else { 
        if(current->data.type==1)	cout<<current->data.ch;
        if(current->data.type==0)	cout<<current->data.num;
 	}
}




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

//cout<<"token values: type= "<<tok.type<<" ch= "<<tok.ch<<" 
//num= "<<tok.num<<endl; 

  if (tok.type==2)  {done=1; continue;}   //case quit

  if (tok.type==0){    			//if token is a number
	TreeNode *T1=new TreeNode;	//cast it to a treenode and
	T1->data=tok;			//add it to the stack
	T1->left=0;
	T1->right=0;
	tree.Add(T1); continue;
		  }

  if (tok.type==1){			//if token is a character
            Token y;			

	if((tok.type==1)&&(tok.ch==')')){

	for(y=*(op.Delete(y));  y.ch!='(';  y=*(op.Delete(y))){ do_op(y); }	
		  }			//if ')' delete until '('

	else{	  
	  
	  for (y=*op.Delete(y); ISP(y.ch)<=ICP(tok.ch); y=*op.Delete(y)){ do_op(y); }	

	  op.Add(y);			//add toks back on to token stack
	  op.Add(tok);			//one of which will always be a '#'
	    }

	continue;  }
     
           }							//end of while



for(x=*(op.Delete(x));  x.ch!='#';  x=*(op.Delete(x))) { do_op(x); }	
root=*tree.Delete(root);		//delete all left over tokens
InOrder(root);
cout<<endl;
}							//end of main()




