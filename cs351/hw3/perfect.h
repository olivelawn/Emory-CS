

#define QKEY (key_t)23346
#define MKEY (key_t)102575

typedef struct mes1{
long type;
int data;	
}message; 


typedef struct mem_seg {
int bitmap[4000];
int manpid;
int perfect[20];
int pid[20];
int tested[20];
int not_tested[20];	
int perf[20];  
}mem_seg1;

