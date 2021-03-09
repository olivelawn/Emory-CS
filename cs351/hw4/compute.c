/* this code is my own work --PARKER JOHNSON */
/* HEY CARLA!! COMPLILED using CC */

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
#include "perfect.h"
 

message per_msg;    	/* message struct for sending perfect numbers */
	int s;		/* s--the server fd */

void termfcn(int);
void send_msg(int);
void keyfcn(int);

void perfect(int start)
{
        int i,sum;
             
        int n=start;
 
        sum=1;
        for (i=2;i<n;i++)
                if (!(n%i)) sum+=i;
 
        if ((sum==n)&&(sum!=1))  
         		send_msg(sum);
                 
 
}


void send_msg(int per)
{
per_msg.type=2;
per_msg.data.value=per;

write(s, &per_msg, sizeof (struct message));
}


main (int argc, char **argv) 
	//int argc;
	//char *argv[];
{

if (argc!=4){
cout<<"USAGE: compute <HOSTNAME> <PORT NUMBER> <START NUMBER>"<<endl;
exit(1);    }


signal (SIGHUP, keyfcn);   
signal (SIGINT, keyfcn);  
signal (SIGQUIT, keyfcn);

	
	struct sockaddr_in sin; /* socket address for destination */
	int len;
	long address;
	int i, start, end;
		

			/* Fill in computes Address */
	address = *(long *) gethostbyname(argv[1])->h_addr;
	sin.sin_addr.s_addr= address;
	sin.sin_family= AF_INET;
	sin.sin_port = atoi(argv[2]);

	while(1) { /*loop waiting for manage if Necessary */		
			/* create the socket */
	if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("Socket");
		exit(1);
		}

		/* try to connect to manage */
	if (connect (s, (struct sockaddr *) &sin, sizeof (sin)) <0) {
		printf("compute says: Where is Manage?\n");
		close(s);
		sleep(10);
		continue;
		}
	break; /* connection successful */
	}

	/* startup sequence */

	msg.type=1;
	msg.data.value= atoi(argv[3]);   	/* compute start num */
	write(s, &msg, sizeof(struct message));

	read(s, &msg, sizeof(struct message));
	start=msg.data.current_range[0];
	end=msg.data.current_range[1];

	for (start; start<=end; start++)
	  			perfect(start);
	
	/* finished range, send back a message with old range */

while(1){
	msg.type=3;
	write(s, &msg, sizeof(struct message)); /* write finished */
	read(s, &msg, sizeof(struct message));  /* read new range */
	
	if(msg.type==-1) termfcn(1);	       /* manage says term */

	start=msg.data.current_range[0];
	end=msg.data.current_range[1];
	
	for (start; start<=end; start++)
	  			perfect(start);	
	
	start=-1; end =-1;
	}

}  /* end of main */


void termfcn(int)
{
msg.type=4;
write(s, &msg, sizeof(struct message)); 	/* write finished */
exit(1);
}

void keyfcn(int)
{
msg.type=7;
write(s, &msg, sizeof(struct message));
close (s);
exit(0);
}
