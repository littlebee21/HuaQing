#include <stdio.h>
#include <string.h>

#define FIRST_NAME_LEN 20
#define LAST_NAME_LEN 20

char *mygets(char *pout,int size);
int main()
{
	char first_name[FIRST_NAME_LEN] = "";
	char last_name[LAST_NAME_LEN] = "";
	char all_name[FIRST_NAME_LEN + LAST_NAME_LEN + 1] = "";

	printf("Please input your first name:\n");
	mygets(first_name,FIRST_NAME_LEN);

	printf("Please input your last name:\n");
	mygets(last_name,LAST_NAME_LEN);


	strcpy(all_name,last_name);
	strcat(all_name," ");
	strcat(all_name,first_name);

	printf("Your name is %s\n",all_name);
	return 0;
}
