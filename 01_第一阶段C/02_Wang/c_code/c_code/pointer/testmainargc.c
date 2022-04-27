#include <stdio.h>

/*
 * argc:argument count
 * argv:argument value
 *
 * argv是一个二级指针，其一级指向空间中存放着（argc+1）个char *类型的元素，最后元素空间存放的地址值为NULL，
 *     因此，argv一级指向空间是一个char *类型的数组，该数组以NULL作为结束标记
 * */
int main(int argc,char *argv[])
{
	/*
	char **pp = NULL;

	pp = argv;
	while(*pp != NULL)
	{
		printf("argv[%ld] = %s\n",pp-argv,*pp);
		pp++;
	}
	*/
	
	int i = 0;
	for(i = 0;i < argc;i++)
	{
		printf("argv[%d] = %s\n",i,argv[i]);
	}
	
	
	printf("argc = %d\n",argc);
	return 0;
}
