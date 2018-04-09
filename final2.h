#define PID_MAX 1000
#define PID_MIN 100

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
 typedef struct dataPid
{
    int pidID;
    pid_t threadUse;
    int inUse;
    
} datPid;


int allocate_map(void) ;
int allocate_pid(pid_t);
void release_pid(int);


