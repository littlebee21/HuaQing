#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int display_dirent_name(char *dirname);
int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("The argumnet is too few,Usage:./printdir dirname\n");
		return 1;
	}

	display_dirent_name(argv[1]);
	return 0;
}

int display_dirent_name(char *dirname)
{
	DIR *pd = NULL;
	struct dirent *pitem = NULL;
	char *pnewpath = 0;
	int len = 0;
	
	pd = opendir(dirname);
	if(NULL == pd)
	{
		printf("opendir %s failed\n",dirname);
		return -1;
	}

	pitem = readdir(pd);
	while(pitem != NULL)
	{
		printf("%s\n",pitem->d_name);

		if(pitem->d_type == DT_DIR)
		{
			/*如果子目录的名字不是.和.. 则再次调用本函数打印该子目录下的所有项名称*/
			if(strcmp(pitem->d_name,".") != 0 && strcmp(pitem->d_name,"..") != 0)
			{
				//1. 组织本子目录路径 pnewpath指向空间内容 ----> "dirname/d_name"
				//pnewpath指向空间大小：strlen(dirname) + strlen(d_name) + 1 + 1 
					//计算空间大小
					len = strlen(dirname) + strlen(pitem->d_name) + 1 + 1;

					//分配空间
					pnewpath = (char *)malloc(len);
					if(NULL == pnewpath)
					{
						printf("Malloc failed\n");
						break;
					}
					
					//strcpy+strcat
					strcpy(pnewpath,dirname);
					strcat(pnewpath,"/");
					strcat(pnewpath,pitem->d_name);

				//2.display_dirent_name(pnewpath);
					display_dirent_name(pnewpath);
				
				//3.free(pnewpath);
					free(pnewpath);
					pnewpath = NULL;
			}
		}

		pitem = readdir(pd);
	}

	closedir(pd);
	pd = NULL;

	return 0;
}
