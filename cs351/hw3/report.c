/*THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING A 
TUTOR OR CODE WRITTEN BY OTHER STUDENTS- PARKER JOHNSON*/

#include <string.h>
#include <iostream.h>
#include <sys/types.h> /* for creat */
#include <sys/stat.h>  /* for stat */
#include <fcntl.h>
#include <stdlib.h> /* for exit */
#include <unistd.h> /* for close */
#include <stdio.h> /* for perror*/
#include <errno.h>
#include <utime.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <sys/shm.h>
#include <signal.h> 

#include "perfect.h"


main(int argc, char **argv)
{
int sid;
char flag[]="-k";

		/*  set uo shared memory segment  */

	mem_seg1 *memptr;

	if  ((sid=shmget(MKEY, 4000*sizeof (int), 0660))==-1)  {
		perror("shmget");
		cerr<<"Manage needs to be executed"<<endl;
		exit(1);
		}
		


		/*  map it into our address space*/

	if ((memptr=((mem_seg *) shmat(sid,0,0)))== (mem_seg *)-1) {
		perror("shmat");
		exit(2);
		}


				/* print out a message */
  cout<<"Perfect Numbers:"<<endl;

	for(int i=0; i<20; i++)
	{
	if (memptr->perfect[i]!=0)
		cout<<memptr->perfect[i]<<endl;
	}

  cout<<"Process Statistics"<<endl;
  cout<<"PID#     #perf	  #tested  #not tested"<<endl;
  cout<<"----------------------------------------"<<endl;
	
  for (int element=0; element<20; element++){
    if(memptr->pid[element]!=0){
  cout<<memptr->pid[element]<<"       "<<memptr->perf[element]<<"       ";
  cout<<memptr->tested[element]<<"     "<<memptr->not_tested[element]<<endl;
			       }
					    }	

  if ((argc==2)&&(!strcmp(argv[1], flag)))
  {
  kill(memptr->manpid, SIGINT);
  cout<<"Report sent manager interrupt signal"<<endl<<"report terminating"<<endl;
  exit(1);
  }

}
