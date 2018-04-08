
// 
/* 
 * File:   pid.h
 * Author: Sean Downes
 * CS450 PID assignment
 * Created on April 11, 2017, 2:09 PM
 */

#ifndef PID_H
#define PID_H

#define PID_MAX 5000
#define PID_MIN 300

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
 typedef struct pidData
{
    int pidID;
    pid_t threadUse;
    int inUse;
    
} pidDat;


int allocate_map(void) ;


int allocate_pid(pid_t);

void release_pid(int);

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* PID_H */

