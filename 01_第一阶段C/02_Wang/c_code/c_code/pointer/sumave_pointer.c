#include <stdio.h>

int get_sum(int *pi,int *sum);
int main()
{
	int arr[] = {1,2,3,4,5,6,-1};
	int sum = 0;
	int len = 0;

	len = get_sum(arr,&sum);

	printf("The sum is %d,The ave is %.2f\n",sum,(float)sum/len);
	return 0;
}

int get_sum(int *pi,int *sum)
{
	int cnt = 0;

	*sum = 0;

	while(*pi != -1)
	{
		cnt++;
		*sum += *pi;

		pi++;
	}
	return cnt;
}
