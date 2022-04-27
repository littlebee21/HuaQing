#include "workqueue.h"

int input_workdata(T *pdata);
char ask_continue();
void *thread_func(void *arg);

int main(int argc,char *argv[])
{
	struct work *pnew = NULL;
	struct wkqueue *pq = create_wkqueue();
	T data;
	char ch = '\0';
	pthread_t tid;
	int ret = 0;

	/*创建线程*/
	ret = pthread_create(&tid,NULL,thread_func,pq);
	if(ret != 0)
	{
		printf("pthread_create failed\n");
		destroy_wkqueue(pq);
		pq = NULL;
		return 1;
	}

	while(1)
	{
		/*输入新工作的数据*/
		input_workdata(&data);

		/*创建节点*/
		pnew = create_work(&data);

		pthread_mutex_lock(&pq->lock);
		/*入队*/
		work_enqueue(pq,pnew);

		/*通知新线程有新的工作待处理*/
		pthread_cond_signal(&pq->cond);

		/*询问是否继续*/
		ch = ask_continue();
		if(ch != 'Y' && ch != 'y')
		{
			set_exit(pq,1);
			pthread_mutex_unlock(&pq->lock);
			break;
		}
		pthread_mutex_unlock(&pq->lock);
	}

	pthread_join(tid,NULL);

	destroy_wkqueue(pq);
	pq = NULL;
	return 0;
}

int input_workdata(T *pdata)
{
	printf("Please input your work data:\n");

	scanf("%d",pdata);
	while(getchar() != '\n')
	{
	}

	return 0;
}

void *thread_func(void *arg)
{
	struct work *ptemp = NULL;
	struct wkqueue *pq = (struct wkqueue *)arg;
	int isexit = 0;

	while(1)
	{
		/*检查是否退出*/
		pthread_mutex_lock(&pq->lock);
		isexit = get_exit(pq);
		if(isexit)
		{
			pthread_mutex_unlock(&pq->lock);
			break;
		}

		/*检查队列是否为空*/
		if(get_wkqueue_len(pq) == 0)
		{
			/*空则等待*/
			pthread_cond_wait(&pq->cond,&pq->lock);
		}

		/*出队一个工作*/
		ptemp = work_dequeue(pq);

		pthread_mutex_unlock(&pq->lock);
		/*处理工作*/
		ptemp->handle(&ptemp->data);

		/*销毁工作*/
		destroy_work(ptemp);
		ptemp = NULL;
	}

	return NULL;
}

char ask_continue()
{
	char ret = '\0';

	printf("Do you continue?Y/N:\n");
	ret = getchar();
	while(getchar() != '\n')
	{
	}

	return ret;
}
