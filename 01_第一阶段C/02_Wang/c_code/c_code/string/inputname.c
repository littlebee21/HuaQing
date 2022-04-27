#include <stdio.h>

char *mygets(char *pout,int size);
int main()
{
	char firstname[20] = "";
	char lastname[20] = "";

	printf("Please input your first name:\n");
	mygets(firstname,20);

	printf("Please input your last name:\n");
	mygets(lastname,20);

	printf("Your name is %s %s\n",lastname,firstname);
	return 0;
}
