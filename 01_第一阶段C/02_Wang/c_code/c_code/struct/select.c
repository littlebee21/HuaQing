#include <stdio.h>
#include <string.h>

#define NAME_LEN 20
#define N 3
struct candidate
{
	char name[NAME_LEN];
	int cnt;
};

char *mygets(char *pout,int size);
int main(int argc,char *argv[])
{
	struct candidate arr[N] = {{"zhangsan",0},{"lisi",0},{"wanger",0}};
	int i = 0;
	char buf[NAME_LEN] = "";
	struct candidate *pt = NULL;

	for(i = 0;i < 10;i++)
	{
		/*输入候选人姓名*/
		printf("Please input your candidate-name:\n");
		mygets(buf,NAME_LEN);

		/*用输入的人名在数组中查找相同名字的候选人，找到则对应选票+1，未找到则意味着放弃选举权 */
		for(pt = arr;pt < arr + N;pt++)
		{
			if(strcmp(pt->name,buf) == 0)
			{
				pt->cnt++;
			}
		}
	}

	/*输出三个候选人姓名和得票数*/
	for(pt = arr;pt < arr + N;pt++)
	{
		printf("%s:%d\n",pt->name,pt->cnt);
	}
	return 0;
}
