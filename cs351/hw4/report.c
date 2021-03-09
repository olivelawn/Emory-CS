/* this code is my own work --PARKER JOHNSON */
/* HEY CARLA!! COMPILED using CC */

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


main (int argc,char **argv) 
	//int argc;
	//char *argv[];
{

char tmp[256];
char flag[]="-k";	

if ((argc<3)||(argc>4)){
	cout<<"USAGE: report <HOSTNAME> <PORT NUMBER> <-k>"<<endl;
	exit(1);	}

if ((argc==4)&&(strcmp(argv[3], flag)!=0)){
	cout<<"USAGE: report <HOSTNAME> <PORT NUMBER> <-k>"<<endl;
	exit(1);	}


	struct sockaddr_in sin; /* socket address for destination */
	int s;
	int len;
	long address;
	
		

			/* Fill in Mary's Address */
	address = *(long *) gethostbyname(argv[1])->h_addr;
	sin.sin_addr.s_addr= address;
	sin.sin_family= AF_INET;
	sin.sin_port = atoi(argv[2]);

	while(1) { /*loop waiting for Mary if Necessary */		
			/* create the socket */
	if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("Socket");
		exit(1);
		}

		/* try to connect to Mary */
	if (connect (s, (struct sockaddr *) &sin, sizeof (sin)) <0) {
		printf("report says: Where is Manage?\n");
		close(s);
		sleep(10);
		continue;
		}
	break; /* connection successful */
	}


   if ((argc==4)&&(!strcmp(argv[3], flag))){	/* terminating */
	msg.type=5;
	write(s, &msg, sizeof (struct message));
			    }

   else{					/* report */

	msg.type=6;				/* write msg to manage */
	write(s, &msg, sizeof (struct message));

	char tmp[256];
	close(0);
	dup(s);
while(1){
	gets(tmp);

	if(strcmp(tmp, "EOF")==0)
		exit(1);
	cout<<tmp<<endl;
	}

	    }


}  /* end of main */
