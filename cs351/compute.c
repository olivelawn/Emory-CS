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
	
	mem_seg1 *memptr;/* pointer to memory segment */
	int element=0;  /* index into process */
    	int qid;        /* message queue id */
	int sid;	/* shared memory id */
	int pid;	/* process id */
	message my_msg; /* message struct */
	int start;

void sendmsg(int sum)
{
my_msg.type=2;		/* two means found a pefect num */
my_msg.data=sum;
msgsnd(qid,&my_msg,sizeof(my_msg.data),0);
}



void perfect(int start)
{
        int i,sum;
                   
        int n=start;
 
        sum=1;
        for (i=2;i<n;i++)
                if (!(n%i)) sum+=i;
        
        if ((sum==n)&&(sum!=1)) 
	  { sendmsg(sum); memptr->perf[element]++; }
        
         
}

void del_entry_term(int);    

main(int argc, char **argv)
{
signal (SIGHUP, del_entry_term);
signal (SIGINT, del_entry_term);
signal (SIGQUIT, del_entry_term);
signal (SIGUSR1, del_entry_term);
 
if (argc!=2){
	cout<<"Usage: compute num"<<endl;
	exit(1);
	    }

int flag=1;
pid=getpid();
 
                        /* create queue if necessary */
        if ((qid=msgget(QKEY,IPC_CREAT |0660))== -1) {
                perror("msgget");
                exit(1);
                }
			
			/*  process startup */

 		my_msg.type=1;  /* one type means startup*/ 
                my_msg.data=pid;
                if(msgsnd(qid,&my_msg,sizeof(my_msg.data),0)==-1)
					cout<<"Error: compute msgsnd";


			/*  set up shared memory segment  */

        if ((sid=shmget(MKEY,4000*sizeof (int), 0660))== -1) {
                perror("shmget");
		cout<<"Manage needs to be executed to set up shared memory."<<endl;
                exit(1);
                }
 
                        /* map it into our address space*/
 
        if ((memptr=((mem_seg1 *) shmat(sid,0,0)))== (mem_seg1 *)-1) {
                perror("shmat");
                exit(2);
                }

   while (flag){        	/*  this loop waits for manage to msgrcv */
	
	for(element=0; element<20; element++){
	if(memptr->pid[element]==pid)
	{ flag=0; break; }
					   }

	sleep(1); 
		} 
//cout<<"found pid num in element="<<element<<endl;

start=atoi (argv[1]);  //check for neg and 0 and 1

while (start<128000)
{
  if ((memptr->bitmap[start/32] & (1<<(start%32))) == 0){
	memptr->bitmap[start/32]|=(1<<(start%32));   /* set */
	perfect(start); 
	memptr->tested[element]++;
					     }

  else { memptr->not_tested[element]++; }
  start++;
}

}		/* end of main */


	void del_entry_term(int)
	{
	memptr->pid[element]=0;
	memptr->tested[element]=0;
	memptr->not_tested[element]=0;
	memptr->perf[element]=0;
	cout<<"Process deleted from shared memory segment"<<endl;
	exit(1);
	}
