#include <stdio.h>

int input_dbl_array(double buf[],int cnt);
int print_dbl_array(double buf[],int cnt);
int select_sort(double buf[],int cnt);
int bubble_sort(double buf[],int cnt);
int insert_sort(double buf[],int cnt);
#define N 6
int main()
{
	double arr[N] = {0.0};

	/*用户输入N个小数*/
	input_dbl_array(arr,N);


	/*排序*/
	//select_sort(arr,N);
	//bubble_sort(arr,N);
	insert_sort(arr,N);


	/*输出排序后的数组*/
	print_dbl_array(arr,N);
	return 0;
}

int input_dbl_array(double buf[],int cnt)
{
	int i = 0;

	if(cnt <= 0)
	{
		printf("Input param is invalid\n");
		return -1;
	}

	printf("Please input %d float-number:\n",cnt);
	for(i = 0;i < cnt;i++)
	{
		scanf("%lf",&buf[i]);
	}

	while(getchar() != '\n')
	{
	}

	return 0;
}

int print_dbl_array(double buf[],int cnt)
{
	int i = 0;

	for(i = 0;i < cnt;i++)
	{
		printf("%.1f ",buf[i]);
	}
	printf("\n");
	return 0;
}

int select_sort(double buf[],int cnt)
{
	int i = 0;
	int j = 0;
	int min = 0;
	double t = 0.0;


	for(i = 0;i < cnt;i++)
	{
		min = i;
		for(j = i+1;j < cnt;j++)
		{
			if(buf[j] < buf[min])
			{
				min = j;
			}
		}

		if(min != i)
		{
			t = buf[i];
			buf[i] = buf[min];
			buf[min] = t;
		}
	}

	return 0;
}

int bubble_sort(double buf[],int cnt)
{
	int i = 0;
	int j = 0;
	double t = 0.0;


	for(i = 0;i < cnt;i++)
	{
		for(j=0;j < cnt - i - 1;j++)
		{
			if(buf[j] > buf[j+1])
			{
				t = buf[j];
				buf[j] = buf[j+1];
				buf[j+1] = t;
			}
		}
	}

	return 0;
}

int insert_sort(double buf[],int cnt)
{
	int i = 0;
	int j = 0;
	double t = 0.0;

	for(i = 1;i < cnt;i++)
	{
		t = buf[i];

		for(j = i-1;j>=0;j--)
		{
			if(buf[j] > t)
			{
				buf[j+1] = buf[j];
			}
			else
			{
				break;
			}
		}
		buf[j+1] = t;
	}
	
	return 0;
}
