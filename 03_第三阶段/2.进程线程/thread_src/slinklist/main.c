#include "person_ll.h"

void *thread_func(void *arg);
char ask_continue();
int input_a_node(T *pt);
int main(int argc,char *argv[])
{
	struct linklist *pll = create_linklist();
	T t = {""};
	struct node *pnew = NULL;
	pthread_t tid;
	int ret = 0;
	char ch = '\0';

	ret = pthread_create(&tid,NULL,thread_func,pll);
	if(ret != 0)
	{
		destroy_linklist(pll);
		pll = NULL;
		printf("pthread_create failed\n");
		return 1;
	}
	
	while(1)
	{
		/*用户输入节点信息*/
		input_a_node(&t);

		/*创建节点*/
		pnew = create_node(&t);

		/*插入节点*/
		insert_at_head(pll,pnew);

		/*continue?*/
		ch = ask_continue();
		if(ch != 'Y'  && ch != 'y')
		{
			set_exit(pll,1);
			break;
		}
	}

	pthread_join(tid,NULL);

	print_all_person(pll);
	destroy_linklist(pll);
	pll = NULL;
	return 0;
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

char *mygets(char *pout,int size);
int input_a_node(T *pt)
{
	printf("Please input a name:\n");
	mygets(pt->name,NAME_LEN);

	printf("Please input a sex:\n");
	pt->sex = getchar();
	while(getchar() != '\n')
	{
	}

	printf("Please input a phone:\n");
	mygets(pt->phone,PHONE_LEN);

	printf("Please input an address:\n");
	mygets(pt->address,ADDR_LEN);

	return 0;
}


void *thread_func(void *arg)
{
	struct linklist *pll = (struct linklist *)arg; 
	int isexit = 0;
	struct node *ptemp = NULL;

	while(1)
	{
		isexit = get_exit(pll);
		if(isexit)
		{
			break;
		}

		ptemp = search_by_name(pll,"lisi");
		if(ptemp != NULL)
		{
			remove_a_node(pll,ptemp);
			print_a_person(ptemp);
			destroy_node(ptemp);
			ptemp = NULL;
		}
		sleep(1);
	}

	return NULL;
}
