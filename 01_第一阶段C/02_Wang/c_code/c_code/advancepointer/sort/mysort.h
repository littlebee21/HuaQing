#ifndef MY_SORT_H
#define MY_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bubble_sort(void *pv,int cnt,int size,int (*pfcmp)(void *,void *));
int select_sort(void *pv,int cnt,int size,int (*pfcmp)(void *,void *));
int insert_sort(void *pv,int cnt,int size,int (*pfcmp)(void *,void *));


#endif
