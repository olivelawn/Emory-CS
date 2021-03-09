#include <stdio.h>
#include <iostream.h>

main()
{

char c, d, tmp1, tmp2;  //char declarations
int flag=0;		// flag determines actions after
			// break in inner while loop
c=getchar();		// read char into c
tmp1=getchar();		// tmp1 acts as a read ahead, or buf

while (c!=EOF)  {

  if ((c=='(')&&(tmp1=='*')) {  	// commented code
	
	d=getchar();
	tmp2=getchar();
	
	  while (1) {
	     if ((d=='*')&&(tmp2==')')) { flag=1; break; }
					
	     else {  d=tmp2;			//break if end
		     tmp2=getchar();		//of comments
		     continue;  }		//otherwise keep
		    }				//reading chars

			     }

  else cout<<c;				//everything normal dump
    
    if (flag) {  c=getchar();		//do this if hit the break
		 tmp1=getchar();	//statement.  This just
		 flag=0;  }		//refreshes vars c and tmp1
					//to correct values
    else {c=tmp1;
  	  tmp1=getchar(); }		//everything normal refresh  
		}
}
