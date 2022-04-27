#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>

int main(int argc,char *argv[])
{
	DIR *pd = NULL;
	struct dirent *pitem = NULL;

	if(argc < 2)
	{
		printf("The argumnet is too few,Usage:./printdir dirname\n");
		return 1;
	}

	pd = opendir(argv[1]);
	if(NULL == pd)
	{
		printf("opendir %s failed\n",argv[1]);
		return 2;
	}

	pitem = readdir(pd);
	while(pitem != NULL)
	{
		switch(pitem->d_type)
		{
			case DT_BLK:
				printf("Filename %s,it is a block device\n",pitem->d_name);
				break;
			case DT_CHR:
				printf("Filename %s,it is a char device\n",pitem->d_name);
				break;
			case DT_FIFO:
				printf("Filename %s,it is a fifo\n",pitem->d_name);
				break;
			case DT_DIR:
				printf("Filename %s,it is a directory\n",pitem->d_name);
				break;
			case DT_SOCK:
				printf("Filename %s,it is a local socket\n",pitem->d_name);
				break;
			case DT_LNK:
				printf("Filename %s,it is a soft-link\n",pitem->d_name);
				break;
			case DT_REG:
				printf("Filename %s,it is a regular file\n",pitem->d_name);
				break;
			default:
				break;
		}

		pitem = readdir(pd);
	}

	closedir(pd);
	pd = NULL;
	return 0;
}
