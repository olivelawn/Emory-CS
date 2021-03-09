#include <iostream.h>
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


  Token tok;
  Stack <Token> op;
  Stack <TreeNode *> tree;


void next_token()
{
  int done=0; tok.ch=' '; tok.num=0;
  int input=cin.get();

while(!done){
	switch(input){

	  case 'Q': case 'q':
 		tok.type=2;		//set type to 2 for quit
		done=1; continue;

	  case '+': case '-': case '*': case '/': case '^': case '(': case ')':
		tok.type=1;	
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
		 tok.type=0;
		 tok.num=input;
					      }
		done=1; continue;
				
			}  //end of switch statement
	   }   //end of while loop
}   //end of function


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



void do_op(Token op)
{
  TreeNode *T1, *T2, *a;
    if ((tree.Delete(T1))&&(tree.Delete(T2))){
	a=new TreeNode;
	a->data=op; a->left=T2; a->right=T1;
	tree.Add(a);
					      }
}


void InOrder(TreeNode *current)
{	
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

