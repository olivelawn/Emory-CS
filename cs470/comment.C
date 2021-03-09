#include <stdio.h>
#include <iostream.h>

main()
{
char c,d,e,f;

c=getchar();

while (c!=EOF) {

  if((c=='(')&&((d=getchar()=='*'))) {
	while(1){
		if((e=getchar()=='*')&&(f=getchar()==')'))
				break;
		else 	
				continue;
		}
				     }
  
  else cout<<c;
  c=getchar();
	       }

}

