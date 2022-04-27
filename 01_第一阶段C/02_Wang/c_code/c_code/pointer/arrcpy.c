#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	float arr1[5] = {1.2,3.4,5.6,7.8,9.9};
	float arr2[5] = {0.0f};

	/*
	{
		float *pf = NULL;

		for(pf = arr1;pf < arr1 + 5;pf++)
		{
			*(arr2 + (pf - arr1))=*pf;
		}
	}
	*/

	memcpy(arr2,arr1,5 * sizeof(float));

	{
		float *pf = NULL;
		for(pf = arr2;pf < arr2 + 5;pf++)
		{
			printf("%.1f ",*pf);
		}
		putchar('\n');
	}
	return 0;
}
