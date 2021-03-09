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

void send_intr_deal(int);
int get_element();

	int sid;	/*  shared memory id  */
	int qid;	/*  message queue id  */
	message my_msg; /* message struct */
	mem_seg1 * memptr;


main()
{

signal (SIGHUP, send_intr_deal);
signal (SIGINT, send_intr_deal);
signal (SIGQUIT, send_intr_deal);
signal (SIGUSR1, send_intr_deal);

int pid;
int num_perf=0;   /*  counts number of perfect numbers */
int dub=0;

		/*  make the segment  */

 if ((sid=shmget(MKEY,4000*sizeof (int),IPC_CREAT |0660))== -1) {
                perror("shmget");
                exit(1);
                }
pid=getpid();


                        /* map it into our address space*/
 
        if ((memptr=((mem_seg *) shmat(sid,0,0)))== (mem_seg *) -1) {
                perror("shmat");
                exit(2);
                }

       if ((qid=msgget(QKEY,IPC_CREAT |0660))== -1) {
                perror("msgget");
                exit(1);
                }

	memptr->manpid=pid;


		/*  sit in loop and wait for messages  */
 	while (1) {
               if( msgrcv(qid,&my_msg,sizeof(my_msg),0,0)==-1)
				cout<<"Error: msgrcv";
                
		if (my_msg.type==1) { 		/* this is startup */
		  memptr->pid[get_element()]=my_msg.data;		
		//  cout<<"Manage: received startup pid="<<my_msg.data<<endl;
				    }

		if (my_msg.type==2) {		/* found a perfect num */

		  if (my_msg.data != 1 ) {
			//cout<<"this shouldn't equal 1=="<<my_msg.data<<endl; 
   			for(int l=0; l<20; l++){
			  if (my_msg.data==memptr->perfect[l])
				dub=-1;
					       }
		  if(dub!=-1)			  	
		    memptr->perfect[num_perf++]=my_msg.data;   
					 }

		  //cout<<"Manage: received a perfect num="<<my_msg.data<<endl; }
					       }	  	
	    	    }

}      	/* end of main */

	
	void send_intr_deal(int)
	{
	  for (int h=0; memptr->pid[h]!=0; h++)
	      kill(memptr->pid[h] , SIGUSR1);

	sleep(5);
	shmdt ( (char *) memptr);
	shmctl (sid, IPC_RMID, 0);
	cout<<"Processes Sent INTR and memory deallocated"<<endl;
	exit(1);
	}
  		

	int get_element()
	{
	for(int g=0; g<20; g++){
	  if (memptr->pid[g]==0)
			return g;
			       }
	}
