#ifndef MY_SEM_H
#define MY_SEM_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <stdio.h>

#define KEY_FILE_NAME "./mysem.h"

int create_a_sem();

int set_sem_value(int id,int val);

int my_sem_p(int id,int val);
int my_sem_v(int id,int val);







#endif
