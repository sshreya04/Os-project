#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#define PID_H

#define MAX_PID 1000
#define MIN_PID 100




 typedef struct dataPid
{
    int pidID;
    pid_t threadUse;
    int inUse;
    
} datPid;


int allocate_map(void) ;


int allocate_pid(pid_t);

void release_pid(int);

datPid * pid_map;
int lastPID;
int allocate_map(void) 
{
    
    int i;
    int numPIDS = MAX_PID - MIN_PID + 1;
    
    pid_map = malloc(numPIDS * sizeof(datPid));
    
    
    // initialize pid array to all zeros and assign ID
    for(i = 0; i < numPIDS; i++)
    {
        pid_map[i].pidID = MIN_PID + i;
        pid_map[i].threadUse = 0;
        pid_map[i].inUse = 0;
    }
    
    if(i == numPIDS) return 0;
    else return 1;
    
}

int allocate_pid(pid_t processId)
{
    int i; 
    i = 0;
    
    if(lastPID > 0 && pid_map[lastPID - MIN_PID + 1].inUse == 0)
    {
        i = lastPID - MIN_PID + 1;
        
        pid_map[i].inUse = 1;
         
        pid_map[i].threadUse = processId;
         
        return pid_map[i].pidID;
        
    }
    i = 0;
    while(pid_map[i].inUse == 1)
    {
        i++;
    }
    if (i < MAX_PID)
    {
        pid_map[i].inUse = 1;
        pid_map[i].threadUse = processId;
        return pid_map[i].pidID;
    }
    else return -1;
}

void release_pid(int pid)
{
    int i = 0;
    lastPID = pid;
    while (pid_map[i].pidID != pid)
    {
        i++;
    }
    pid_map[i].inUse = 0;
    pid_map[i].threadUse = -1;
    
}

static const int noofthreads = 100;
pthread_mutex_t mutex;




void *assignPids(void *params)
{
    
    pthread_mutex_lock(&mutex);
    pid_t tempProcessId;
    int pidG;
    
    tempProcessId = pthread_self();
    pidG = allocate_pid(tempProcessId);
    pthread_mutex_unlock(&mutex);
    if ( pidG > -1)
    {
        printf("PID ASSIGNED IS %d\n", pidG);
    }
    else 
    {
        printf("ERROR ASSIGNING PID\n");
        return;
    }
    
    sleep(rand() % 7);
    
    release_pid(pidG);
    printf("RELEASED PID %d\n " ,pidG);
}


int main(void)
{
    pthread_attr_t thread_attributes;
    
    pthread_t threads[noofthreads];
    int i;
   
    pthread_mutex_init(&mutex, NULL);
    srand((unsigned)time(NULL));
    
    if(allocate_map() != 0)
    {
        printf("Failed to create map\n");
        return 1;
    }
    
    pthread_attr_init(&thread_attributes);
    for (i = 1; i < noofthreads; i++)
    {
        pthread_create(&threads[i], &thread_attributes, assignPids, NULL);
       pthread_join(threads[i], NULL);
    }
    
    for (i = 1; i < noofthreads; i++)
    {
        pthread_join(threads[i], NULL);
        
    }
    
    return 0;
}
