CC = CC

DEBUG =  -g #This is the debuging flag for the compiler

HEADER = perfect.h

CFLAGS = $(DEBUG) #add other compiler flags here 

LIBS = -lm -lsocket -lnsl #The necessary libraries you need (eg -lsocket)

TARGETS = manage compute report #These are the executables you will make

all: $(TARGETS)

report: report.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)

compute: compute.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)

manage: manage.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)

clobber:	#cleans up so that everything will be remade
	rm -f *.o *~* *.a 
	rm -f $(TARGETS) 
