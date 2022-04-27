#include <stdio.h>

int main()
{
	char ch = 'M';
	int x = 84;
	float f = 1.8;
	char str[] = "Laobai";
	char out[20] = ""; 
	
	sprintf(out,"%s %c %d %.1f",str,ch,x,f);

	printf("out=%s\n",out);
	return 0;
}
