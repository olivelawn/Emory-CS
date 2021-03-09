/* This code is my own own work  -- PARKER JOHNSON */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include <stropts.h>
#include <poll.h>
#include <signal.h>
#include <string.h>
#include <iostream.h>
#include <fcntl.h>
#include <stdlib.h> /* for exit */
#include <unistd.h> /* for close */
#include <errno.h>
#include <iomanip.h>
#include "perfect.h"

//#define NUMCOM 20

void wait_sig_die(int);	/* prototypes */
void exitfcn(int);


map_host map[5000];
char running[5000];
int per_num[20];
int percount=0;
int start, end;
int signal_flag=1;
int num_computes=0;

int find_range(int value)    /*  gets a value returns first num in acceptable range */
{
int vector = value/200;

if (map[vector].flag==0){
  map[vector].flag=1;
  return (vector*200);
		   }

else { ++vector;
  while(1){
    if (map[vector].flag==0){
	map[vector].flag=1;
	return(vector*200); }
    
    else
	++vector;
	  }
     }
}


void found_perfect_num(int num)
{

if (num==1) return;

  for(int kk=0; kk<20; kk++)
  {
    if (per_num[kk]==num){
	cout<<"duplicate perfect numbers"<<endl;
	return;
		       }
	  }

per_num[percount++]=num;

}



void insert_hostname(int element, long address)
{
  char *tmp=0;
  element /= 200;
  
  tmp=gethostbyaddr((char*)&address, 4, AF_INET)->h_name;
  strcpy(map[element].hostname, tmp);
}




main (int argc, char **argv) 
	//int argc;
	//char *argv[];
{

signal (SIGHUP, wait_sig_die);   
signal (SIGINT, wait_sig_die);  
signal (SIGQUIT, wait_sig_die);

if(argc!=2){
	cout<<"USAGE: manage <PORT NUMBER>"<<endl;
	exit(1); }
	
for (int jj=0; jj<5000; jj++)
		map[jj].flag=0;

struct sockaddr_in sin;
long addr[22];
int s;
int fd;
int len, i,num,count,p, q;
struct pollfd pollarray[22];     /* 20 possible sockets and s and report*/
int pt1, pt2;
int el;

for(int g=0; g<22; g++)
	addr[g]=0;

		/* set up IP addr and port number for bind */

	sin.sin_addr.s_addr= INADDR_ANY;
	sin.sin_port = atoi(argv[1]);


		/* Get an internet socket for stream connections */

	if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("Socket");
		exit(1);
		}


		/* Do the actual bind */

	if (bind (s, (struct sockaddr *) &sin, sizeof (sin)) <0) {
		perror("bind");
		exit(2);
		}

		/* Allow a connection queue for up to 20 computes and 1 report */

	listen(s, 21);

		/* Initialize the pollarray */
	
	pollarray[0].fd=s;     /* Accept Socket*/
	pollarray[0].events=POLLIN;
						  /*  possible john's */
	for (i=1;i<=21;i++) {pollarray[i].fd=-1;pollarray[i].events=POLLIN;}
	
	

	while(1) {
		poll(pollarray,21,-1);   /* no timeout, blocks until some activity*/

				/* Check first for new connection */
		if (pollarray[0].revents & POLLIN) {
			len=sizeof(sin);
			if ((fd= accept (s, (struct sockaddr *) &sin, &len)) <0) {
				perror ("accept");
					exit(3);
				}

			/* Find first available slot for new compute */

			for (i=1;i<=21;i++) if (pollarray[i].fd == -1) break;
				pollarray[i].fd=fd;
				addr[i]= sin.sin_addr.s_addr;
			}



		/* If there are no new connections, process waiting compute's info */

		else for (i=1;i<=20;i++) {
			if ((pollarray[i].fd !=-1) && pollarray[i].revents) {
					
read(pollarray[i].fd, &msg, sizeof(struct message));
			 
switch(msg.type) {

case 1:		/* compute start */
	num_computes++;
	start=find_range(msg.data.value);
	end=start + 199;
        msg.data.current_range[0]=start;
	msg.data.current_range[1]=end;
	write(pollarray[i].fd, &msg, sizeof(struct message));
	insert_hostname(start, addr[i]);
	running[start/200]=1;
	//cout<<"compute start"<<endl;
	break;

case 2:		/* compute finds a perfect number */
	found_perfect_num(msg.data.per_num);	
        break;

case 3:		/* compute finishes range and needs new one */
	//running[start/200]=0;

  if(signal_flag==1){		/* normal execution */
	start=msg.data.current_range[0];
	running[start/200]=0;
	
	start=find_range(msg.data.current_range[1]);
	//cout<<start<<endl;
	end=start + 199;
        msg.data.current_range[0]=start;
	msg.data.current_range[1]=end;
	write(pollarray[i].fd, &msg, sizeof(struct message));
	running[start/200]=1;
	insert_hostname(start, addr[i]);
	//cout<<"compute finished range, got new one"<<endl;
	break;	
		     }

  if(signal_flag==-1){		/* recieved a -k or a signal */
	msg.type=-1;		/* -1 send term sig to compute */
	write(pollarray[i].fd, &msg, sizeof(struct message));	
		     }
	break;
	

case 4:		/* compute terminates */	
	num_computes--;
	pollarray[i].fd = -1;
	//cout<<"COMPUTE: terminating"<<endl;	
	//sleep(5);
	break;

case 5:		/* report tells manage to terminate */
	
	wait_sig_die(1);	
	pollarray[i].fd = -1;
	break;

case 6:		/* report query */

close(1);
dup(pollarray[i].fd);	

  char status[15];

cout<<"TESTED    RANGES        HOSTNAME                STATUS"<<endl<<endl;
 
  for (q=0; q<5000; q++)
  {
    if(map[q].flag==1)
    {           
    pt1=q*200;
    pt2=pt1+199; 
                  
    if (running[q]==1)  
          strcpy(status, "[RUNNING]");
    else
          strcpy(status, "[Finished]");
        
cout<<setw(7)<<pt1<<"--"<<pt2<<"\t\t"<<map[q].hostname<<"\t\t\t"<<status<<endl; 
	}
  }
  
cout<<endl<<"PERFECT NUMBERS:"<<endl;  
 
  for(p=0; p<20; p++)
  {
    if (per_num[p]!=0)
        cout<<per_num[p]<<endl;
  }
cout<<"EOF"<<endl;	
	pollarray[i].fd = -1;
	break;

case 7:			// case where compute is given a signal from keyboard 
			// and you need to readjust the map accordingly 

	num_computes--;
	cout<<endl<<"COMPUTE: received term interrupt, adjusting BITMAP"<<endl;
	el=msg.data.current_range[0];
	el/=200;
	map[el].flag=0;
	pollarray[i].fd = -1;
	break;


		}   /* end of switch statement */

									     		}  /* end of if */
								 }  /* end of else for */
			
		}    /* end of main */
} //end of main


void wait_sig_die(int)
{
if(num_computes==0) {/*cout<<"No computes: Exiting"<<endl;*/  exit(0);}
signal(SIGALRM, exitfcn);
signal_flag=-1;
//cout<<"Computes running: Setting Alarm"<<endl;
alarm(35);

}


void exitfcn(int)
{
//cout<<"MANAGE :caught alarm signal, exiting"<<endl;
exit(1);
}

