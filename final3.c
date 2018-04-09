#include "final2.h"

static const int noofthreads = 100;
pthread_mutex_t mutex;

void *PIDAssign(void *params)
{ 
    pthread_mutex_lock(&mutex);
    pid_t tempPID;
    int pidG;   
    tempPID = pthread_self();
    pidG = allocate_pid(tempPID);
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
    sleep(rand() % 5);
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
        pthread_create(&threads[i], &thread_attributes, PIDAssign, NULL);
    }    
    for (i = 1; i < noofthreads; i++)
    {
        pthread_join(threads[i], NULL);   
    }
    return 0;
}
