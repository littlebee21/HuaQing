#include <stdio.h>
#include <string.h>

#define N 5
int print_names(char **ppnames,int cnt);
int sort_names(char **ppnames,int cnt);
int main()
{
	char *name_arr[5] = {"ruhua","siyu","cengyu","luoyan","biyue"};

	sort_names(name_arr,5);

	print_names(name_arr,5);
	return 0;
}

int sort_names(char **ppnames,int cnt)
{
	int i = 0;
	char * pt = NULL;
	/*
	int j = 0;
	for(i = 0;i < cnt;i++)
	{
		for(j = 0;j < cnt - i - 1;j++)
		{
			if(strcmp(ppnames[j],ppnames[j+1]) > 0)
			{
				pt = ppnames[j];
				ppnames[j] = ppnames[j+1];
				ppnames[j+1] = pt;
			}
		}
	}
	*/
	char **pp = NULL;
	for(i = 0;i < cnt;i++)
	{
		for(pp = ppnames;pp < ppnames+cnt - i - 1;pp++)
		{
			if(strcmp(*pp,*(pp+1)) > 0)
			{
				pt = *pp;
				*pp = *(pp+1);
				*(pp+1) = pt;
			}
		}
	}

	return 0;
}

int print_names(char **ppnames,int cnt)
{
	/*
	int i = 0;

	for(i = 0;i < cnt;i++)
	{
		printf("%s\n",ppnames[i]);
	}
	*/
	char **pp = NULL;

	for(pp = ppnames;pp < ppnames + cnt;pp++)
	{
		printf("%s\n",*pp);
	}

	return 0;
}
