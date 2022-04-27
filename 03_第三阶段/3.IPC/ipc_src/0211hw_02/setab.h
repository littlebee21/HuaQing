#ifndef SET_A_OR_B_H
#define SET_A_OR_B_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include <stdio.h>

#include "mysem.h"

#define SHMEM_LEN 20

#define SHMEM_KEY_F "./setab.c"
#define SHMEM_KEY_V 9

#endif
