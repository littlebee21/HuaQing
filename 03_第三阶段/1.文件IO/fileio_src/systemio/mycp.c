#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#include <stdio.h>

int main(int argc,char *argv[])
{
	int srcfd = -1;//file description
	int destfd = -1;//file description
	char buf[10] = "";
	int rret = 0;
	int wret = 0;

	if(argc < 3)
	{
		printf("The argument is too few,Usage:./mycp srcfile destfile\n");
		return 1;
	}

	srcfd = open(argv[1],O_RDONLY);
	if(srcfd < 0)
	{
		printf("rdonly-open %s failed\n",argv[1]);
		return 2;
	}

	destfd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0666);
	if(destfd < 0)
	{
		printf("wronly-open %s failed\n",argv[2]);
		return 2;
	}
	
	rret = read(srcfd,buf,10);
	while(rret > 0)
	{
		wret = write(destfd,buf,rret);
		if(wret != rret)
		{
			printf("Write %d bytes to %s failed,wret=%d\n",rret,argv[2],wret);
			break;
		}
		rret = read(srcfd,buf,10);
	}
	
	close(srcfd);
	srcfd = -1;

	close(destfd);
	destfd = -1;
	return 0;
}
