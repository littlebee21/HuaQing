/*
 *给定一个文件，先判断其是否存在，如存在，再看其是不是普通文件，如果是普通则输出文件大小，如果不是普通文件，则输出其文件种类
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

int main(int argc,char *argv[])
{
	struct stat st = {0};
	if(argc < 2)
	{
		printf("The argument is too few,Usage:./isexist file\n");
		return 1;
	}

	if(!access(argv[1],F_OK))
	{
		stat(argv[1],&st);
		switch(st.st_mode & S_IFMT)
		{
			case S_IFBLK:  
				printf("block device\n");            
				break;
		        case S_IFCHR:  
				printf("character device\n");        
				break;
           		case S_IFDIR:  
				printf("directory\n");               
				break;
		        case S_IFIFO:  
				printf("FIFO/pipe\n");
		 		break;
		        case S_IFLNK:  
				printf("symlink\n");                 
				break;
           		case S_IFREG:  
				printf("The size of %s is %ld\n",argv[1],st.st_size);            
				break;
           		case S_IFSOCK: 
				printf("socket\n");
	      			break;
           		default:
			 	printf("unknown?\n");
				break;
		}
	}
	else
	{
		printf("The %s file is not exist\n",argv[1]);
	}

	return 0;
}
