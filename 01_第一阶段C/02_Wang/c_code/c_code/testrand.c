#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int main()
{
	int n1 = 0;
	int n2 = 0;

	srand(time(NULL));

	n1 = rand();
	n2 = rand();

	printf("n1=%d,n2=%d\n",n1,n2);
	return 0;
}
