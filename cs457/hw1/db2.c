#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

FILE *fp;


int eof(int fd)
{
   char c;
 
   if ( read(fd, &c, 1) != 1 )
      return(1);
   else
    { lseek(fd, -1, SEEK_CUR);
      return(0);
    }
}


void int_handler(int dummy)
{
   fclose(fp);
   printf("\nDone.\n");
   exit(0);
}


main()
{
   char field[10][30];
   int fieldsize[10];
   int n_fields;

   char buffer[100][100];
   char lookup[100], search_field[100];
   int i, j, b;
   int found, sfound, check;
   int fd;

   printf("Program for searching a mini database on FIRST field:\n");
   signal(SIGINT, int_handler);

   /* ---
      Read in definition 
      --- */
   fp = fopen("db-description", "r");
   n_fields = 0;
   while ( fscanf(fp, "%s %d", field[n_fields], &fieldsize[n_fields]) > 0 )
      n_fields++;

   printf("The database consists of these fields:\n");
   for (i = 0; i < n_fields; i++)
      printf("Filedname `%s' - size = %d\n", field[i], fieldsize[i]);
   printf("\n\n");

   /* ---
      Open database file
      --- */
   fd = open("db-file", O_RDONLY);

   /* ---
      Do lookup
      --- */
   i = 1;
   while (1)
    { 
      printf("Enter search_field: ");
      scanf("%s", search_field);

        for (b=0; b<n_fields; b++)
        {
      	if (strcmp(field[b], search_field) == 0)
				{sfound=b;  check=1;}
	}

      if (!check) { printf("No such field.\n"); exit(1); }
      check=0;
      printf("Enter search value: ");
      scanf("%s", lookup);

      lseek(fd, 0, SEEK_SET);           /* Reset to begin of file */
      found = 0;                        /* Assume not found */

      while ( ! eof(fd) )
       { /* -----
            Read 1 record
            ----- */
         for (j = 0; j < n_fields; j++)
          { read(fd, buffer[j], fieldsize[j]);
          }

         /* ------
	    Test on ALL fields
	    ------ */
         if (strcmp(buffer[sfound], lookup) == 0 )
          { found = 1;
            printf("Found: ");
            for (j = 0; j < n_fields; j++)
            { printf("%s ", buffer[j]);
            }
            printf("\n");
          }
       }

      if (!found)
	     printf("No Records found.\n");       
    }
}

