#include <stdio.h>

int main()
{
	int i = 0;
	int cnt = 0;

	for(i = 1;i <= 200;i++)
	{
		if(i % 2 == 0)
		{
			printf("%-4d",i);
			cnt++;
			if(cnt % 10 == 0)
			{
				printf("\n");
			}
		}
	}

	return 0;
}
