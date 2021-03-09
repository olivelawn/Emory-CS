#include <iostream.h>

main()

{

int array[13] = {28,-19,19,-74,-61,-66,400,300,200,-1000,2,30,23};
int n = 13;
int this_sum = 0;
int max_sum = 0;
int low = 0;
int high = 0;

  for (int ii = 0; ii < n; ii++)
    for (int jj = ii; jj < n; jj++) {
       this_sum = 0;
 
      for (int kk = ii; kk <= jj; kk++)
        this_sum += array[kk];

      if (this_sum > max_sum)
        {max_sum = this_sum;
	 low = ii;
	 high = jj;  }  

   }

  cout<<"max sum "<<max_sum<<endl;  
  cout<<"low "<<low<<endl;  
  cout<<"high "<<high<<endl;  


}

