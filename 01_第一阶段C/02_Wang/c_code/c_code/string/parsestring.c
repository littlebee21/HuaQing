#include <stdio.h>
#include <string.h>

int main()
{
	char buf[] = "LaoTe@70@F";
       	char out[12] = "";	
	char name[8] = "";
	char sex = '\0';
	int age = '0';

	char *p = NULL;

	p = strchr(buf,'@');//p---->第一个@
	strncpy(name,buf,p-buf);

	p++;//p------->'7'
	sscanf(p,"%d",&age);

	p = strchr(p,'@');//p---->第二个@
	p++;//p------->F

	sex = *p;

	age+=2;
	sex = 'M';

	sprintf(out,"%s#%d#%c",name,age,sex);
	
	printf("out=%s\n",out);

	return 0;
}
