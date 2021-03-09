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

main(int argc, char **argv)

{
FILE *file;
int fd, numbytes, status, status2;
int pipein[2], pipeout[2];
char buf[512];
char str1[256];
char str2[256];
char str3[256];
int test=0;

pipe(pipein);
pipe(pipeout);

switch(fork()){

case -1:
	perror("fork");
case 0:			/* child --do sort*/
	close (pipein[1]); close(pipeout[0]);

	close(0);
	dup(pipein[0]);
	close(pipein[0]);

	close(1);
	dup(pipeout[1]);
	close(pipeout[1]);

	execl("/bin/sort", "sort", NULL);
	perror("execl");
	exit(1);
	      }         /*end of switch statement*/

  if (argc>1) {
        if (fd=open(argv[1], O_RDONLY, 0666)==-1){
			cout<<"file for input dne!"<<endl; exit(1);
						 }
	      }
  else 
    fd=0;

  while  ((numbytes=read(fd, buf, 512)) !=0)
  {
  write (pipein[1], buf, numbytes);
  }

  close (pipein[0]); close (pipein[1]); close (pipeout[1]); 


switch(fork()){

case -1:
	perror("fork");
case 0:			/*child --do uniquify*/
  	
  file = fdopen(pipeout[0], "r");


  if (fgets(str1, 256, file) == 0)
                { exit(0);}
                                       
  while (fgets(str2, 256, file) != 0){
 
   test=strcmp(str1, str2);
 
   if(test==0)
	strcpy(str1, str2);

   else {
	cout<<str1;
	strcpy (str1, str2);
	}                                      
				     }

cout<<str1;


default:		/* parent */
  wait (&status);
  wait (&status2);
  close (pipeout[0]);

		}    /* end of switch statement*/

}//end of main
