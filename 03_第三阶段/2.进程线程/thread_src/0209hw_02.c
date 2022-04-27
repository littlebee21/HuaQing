/*
 *主线程动态创建一个对象，该对象将可能被用于多个分离的新线程，要求确保每个线程用该对象时该对象必须存在，大家都不用该对象时才被销毁
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

typedef int DT;

struct myobject
{
	DT data;

	int refcnt;

	pthread_mutex_t lock;
};

struct myobject *create_myobject(DT *pdata);
struct myobject *add_object_refcnt(struct myobject *pobj);
int destroy_myobject(struct myobject *pobj);

void *use_object(void *arg);
int main(int argc,char *argv[])
{
	pthread_t tid1;
	pthread_t tid2;
	int ret = 0;
	DT data = 100;
	struct myobject *pnew = create_myobject(&data);

	add_object_refcnt(pnew);//for main thread;


	add_object_refcnt(pnew);//for the first thread;
	ret = pthread_create(&tid1,NULL,use_object,pnew);
	if(ret != 0)
	{
		destroy_myobject(pnew);//for the first thread
		printf("pthread_create the first thread failed\n");
		return 1;
	}

	add_object_refcnt(pnew);//for the second thread;
	ret = pthread_create(&tid2,NULL,use_object,pnew);
	if(ret != 0)
	{
		destroy_myobject(pnew);//for the second thread
		printf("pthread_create the second thread failed\n");
		return 2;
	}
	
	pthread_mutex_lock(&pnew->lock);
	printf("in main thread,data is %d\n",pnew->data);
	pthread_mutex_unlock(&pnew->lock);
	destroy_myobject(pnew);//for the main thread
	pthread_exit(NULL);
	return 0;
}

void *use_object(void *arg)
{
	struct myobject *pobj = (struct myobject *)arg;
	pthread_t tid;

	tid = pthread_self();
	pthread_detach(tid);

	pthread_mutex_lock(&pobj->lock);
	printf("in thread %d,data is %d\n",(int)tid,pobj->data);
	pthread_mutex_unlock(&pobj->lock);
	
	destroy_myobject(pobj);//for the main thread
	return NULL;
}

struct myobject *create_myobject(DT *pdata)
{
	struct myobject *pnew = NULL;

	pnew = (struct myobject *)malloc(sizeof(struct myobject));
	if(NULL == pnew)
	{
		printf("Malloc failed for create_myobject\n");
		return NULL;
	}
	memset(pnew,0,sizeof(struct myobject));
	
	memcpy(&pnew->data,pdata,sizeof(DT));
	pthread_mutex_init(&pnew->lock,NULL);
	return pnew;
}

struct myobject *add_object_refcnt(struct myobject *pobj)
{
	pthread_mutex_lock(&pobj->lock);
	pobj->refcnt++;
	pthread_mutex_unlock(&pobj->lock);

	return pobj;
}

int destroy_myobject(struct myobject *pobj)
{
	pthread_mutex_lock(&pobj->lock);
	
	pobj->refcnt--;
	
	if(pobj->refcnt == 0)
	{//释放pobj指向的空间
		printf("Will free myobject\n");
		pthread_mutex_unlock(&pobj->lock);
		pthread_mutex_destroy(&pobj->lock);
		free(pobj);
		pobj = NULL;
		return 1;
	}
	else
	{
		pthread_mutex_unlock(&pobj->lock);
		return 0;
	}
}
