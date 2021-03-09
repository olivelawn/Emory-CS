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

char magic_num [] = "!<arch>\n";
char fmag [] = "`\n";

struct ar_hdr		/* archive file member header - printable ascii */
{
	char	ar_name[16];	/* file member name - `/' terminated */
	char	ar_date[12];	/* file member date - decimal */
	char	ar_uid[6];	/* file member user id - decimal */
	char	ar_gid[6];	/* file member group id - decimal */
	char	ar_mode[8];	/* file member mode - octal */
	char	ar_size[10];	/* file member size - decimal */
	char	ar_fmag[2];	/* ARFMAG - string to end header */
};

int check_exist(char *arg)	//this func determines if a file exists
{ 	 int fd;		//and returns its fd
	 fd=open(arg, O_RDONLY, 0666);
				       
	 return fd;
		      
}	

int valid(int fd) 		//valid func checks for magic string
{				//prints out error if not there
        int where;
	char buf[8];
	where = read(fd, buf, 8);

	if (strncmp(buf, magic_num, 7)== 0) { return 1;}
	else {cout<<"Invalid or Corrupt archive file"<<endl; exit(1);}
}

void write_file_hdr(int fd, ar_hdr file)  //write_file_hrd writes to disk 
{

	write(fd, file.ar_name, 16);
	write(fd, file.ar_date, 12);
	write(fd, file.ar_uid, 6);
	write(fd, file.ar_gid, 6);
	write(fd, file.ar_mode, 8);
	write(fd, file.ar_size, 10);	
	write(fd, file.ar_fmag, 2);

}



ar_hdr stat_assign(int fd, char * filename)    //fstats and copies data mem
{
	struct stat sb;
	char * slash = "/";
	fstat(fd, &sb);
	strcat(filename, slash);			   
	ar_hdr tmp;

sprintf(tmp.ar_name, "%-16s/", filename);
sprintf(tmp.ar_date, "%-12d", sb.st_mtime);
sprintf(tmp.ar_uid, "%-6d", sb.st_uid);
sprintf(tmp.ar_gid, "%-6d", sb.st_gid);
sprintf(tmp.ar_mode, "%-8o", sb.st_mode);
sprintf(tmp.ar_size, "%-10d", sb.st_size);
sprintf(tmp.ar_fmag, "%-2s", fmag);

  return tmp;
}


void content_copy (int fd1, int fd2)		//copies contents into arch
{
int size;
struct stat sb;
fstat(fd1, &sb);
size=sb.st_size;
char buff[1];
int iosize;

  for (int i=0; i< size; i++){
    read (fd1, buff, 1);
    write (fd2, buff, 1);
			     }

if (size%2==1) write (fd2, "\n", 1);
  

}

void printerr()					//function to printerr and exit
{
cout<<"File not found"<<endl;
exit(1);
}




void extract(int arch_fd, char *s_file)		//extracting function
{
struct utimbuf tb;
int end, mode, extract_fd, date;
unsigned size;
char buf[16], sfile[17], hfile[17], contents[1];
char slash[2] = "/";

  sprintf(hfile,"%s", s_file); 
  strcat(s_file, slash);
  
while(1)
 {

  end=read(arch_fd, buf, 1);
   if (end==0) printerr();
   if (strncmp(buf, "\n", 1)!=0)
	lseek(arch_fd, -1, 1);

  end=read(arch_fd, buf, 16);
   if (end==0) printerr();
    
    sprintf(sfile, "%-16s", s_file);
   
   if (strncmp(sfile, buf, 16)==0)	//if extractable file==buf
   	{
	read(arch_fd, buf, 12);
	sscanf(buf, "%d", &date);
	lseek(arch_fd, 12, 1);
	read(arch_fd, buf, 8);
	sscanf(buf, "%o", &mode);
	read(arch_fd, buf, 10);
	sscanf(buf, "%u", &size); 
   	lseek(arch_fd, 2, 1);
   	extract_fd=open(hfile, O_WRONLY | O_CREAT | O_TRUNC, mode);
   		
	   for(int i=0; i<size; i++)
	   {
	     read(arch_fd, contents, 1);
	     write(extract_fd, contents, 1);
           }
	tb.actime=date;
	tb.modtime=date;

        utime(hfile, &tb);        
        
   	close(arch_fd); close(extract_fd);
   	exit(1);
   	}

   else {
   	lseek(arch_fd, 32, 1);
	read(arch_fd, buf, 10);
	sscanf(buf, "%u", &size);
 	size += 2; 
   	lseek(arch_fd, size, 1);
	}
 }

}





void p_perm(int per)			//func takes in octal num and prints perms
{

if (per==0) cout<<"---";
if (per==1) cout<<"--x";
if (per==2) cout<<"-w-";
if (per==3) cout<<"-wx";
if (per==4) cout<<"r--";
if (per==5) cout<<"r-x";
if (per==6) cout<<"rw-";
if (per==7) cout<<"rwx";
}

void fix_print(char * datestr)		//func converts ctime output
{					//to ar verbose formatted output

  for(int i=4; i<16; i++)
  {
  cout<<datestr[i];
  }

   for(i=19; i<24; i++)
   {
   cout<<datestr[i];
   }

}


void verbose_print(int fd)		//function to print out verbose listing
{ 
  int end=1;
  ar_hdr header;
  int other, group, owner;
  char * tokenptr;
 
while (end)
 {

 end = read(fd, &header, sizeof(struct ar_hdr));  if(end==0) exit(1);

 
long date;
int mode;
int size; 

sscanf(header.ar_name, "%16s", header.ar_name);
sscanf(header.ar_date, "%s", header.ar_date);
sscanf(header.ar_uid, "%s", header.ar_uid);
sscanf(header.ar_gid, "%s", header.ar_gid);
sscanf(header.ar_mode, "%s", header.ar_mode);
sscanf(header.ar_size, "%s", header.ar_size);
sscanf(header.ar_fmag, "%s", header.ar_fmag);

  sscanf(header.ar_date, "%d", &date);    //translation error
  sscanf(header.ar_mode, "%o", &mode);     //translation error
  sscanf(header.ar_size, "%d", &size);    //translation error


  other= (mode & 7);
  group= ((mode & 070) >> 3);
  owner= ((mode & 0700) >> 6);
	p_perm (owner);
	p_perm (group);
	p_perm (other);
 char * pdate=ctime(&date);

cout<<" "<<header.ar_uid<<"/"<<header.ar_gid<<" ";
fix_print(pdate);
tokenptr = strtok(header.ar_name, "/");		//strtok eliminates "/"
cout<<" "<<tokenptr<<endl;

lseek(fd, size, 1);
  if (size%2==1) lseek(fd, 1, 1);
 }
}

  








main(int argc,char **argv) 
{

if (argc==1) {cout<<"Invalid entry.  Usage: myar key[q][x][v][d] afile name"<<endl;
 	exit(1);}

if (*argv[1]=='q')
{
  int fd_file;
  int fd_arch;
  ar_hdr head;  
  struct stat sbuf;

  if (argc != 4 ) {
		printf("Usage: myar key afile name\n");
		exit(1);
		}

	fd_arch=open(argv[2], O_RDWR | O_CREAT, 0666);
	fstat (fd_arch, &sbuf);
	 if (sbuf.st_size==0) 
		write (fd_arch, magic_num, 8);
	
	 else 
		valid (fd_arch);	//prints error message and exits if not valid


	fd_file=check_exist(argv[3]);
	  if (fd_file==-1){
		cout<<"Invalid file"<<endl; exit(1);
			  }


 	lseek(fd_arch, 0, 2);       

  if (check_exist(argv[3]))
 	fd_file=open(argv[3], O_RDONLY, 0666);


  head=stat_assign(fd_file, argv[3]);
  write_file_hdr(fd_arch, head);
  content_copy(fd_file, fd_arch);

}


    //CASE "X"
   else if (*argv[1]=='x')
   {

	if (argc != 4 ) {
		printf("Usage: myar key afile name\n");
		exit(1);
		        }
	int fd_arch;
	int fd_file;	
	  fd_arch=open(argv[2], O_RDONLY, 0666);
          valid(fd_arch);           //prints out error messages if not valid

	extract(fd_arch, argv[3]);
	close (fd_arch);						
   }


   else if (*argv[1]=='v')
   {

	if (argc != 3 ) {
		printf("Usage: myar key afile\n");
		exit(1);
		        }

     int fd_arch;
     fd_arch=open(argv[2], O_RDONLY, 0666);
     valid(fd_arch);    	      //prints out error messages if not valid
     verbose_print(fd_arch);
   }

/*
   else if (*argv[1]=='d')&&(check_exist(*argv[2]))
   {

	if (argc != 4 ) {
		printf("Usage: myar key afile name\n");
		exit(1);
		        }

						
   }
*/

   else { cout<<"improper usage"<<endl;}  	

}   //end of main function


