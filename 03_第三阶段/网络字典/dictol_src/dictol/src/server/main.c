#include "sprivate.h"

static int CreateServerSocket(char *ip,short port);
static int mainloop(int servfd,sqlite3 *pDB);
int main(int argc,char *argv[])
{
	int fd = -1;
	int port = 0;
	int ret = 0;
    sqlite3 *pDB = NULL;
	
	if(argc < 3)
	{
		PrintServerError("Usage is ./dictolserver ip port\n");
		return 1;
	}

	sscanf(argv[2],"%d",&port);
	
	if(port < 1024 || port > 9999)
	{
		
		PrintServerError("port is invalid\n");
		return 2;
	}
	
	fd = CreateServerSocket(argv[1],port);
	if(fd < 0)
	{
		return 3;
	}

	pDB = CreateSQLite3Engine("./dictol.db");
	if(NULL == pDB)
	{
		return 4;
	}

	ret = mainloop(fd,pDB);
	
	sqlite3_close(pDB);
	close(fd);
	fd = -1;	

	return ret;	
}


static int CreateServerSocket(char *ip,short port)
{
	int fd = -1;
	struct sockaddr_in servaddr;
	int ret = 0;

	fd = socket(AF_INET,SOCK_STREAM,0);
	
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_aton(ip,&servaddr.sin_addr);
	ret = bind(fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	ret += listen(fd,6);
	if(ret != 0)
	{
		PrintServerError("bind or listen error\n");
		close(fd);
		return -1;
	}	

	return fd;
}

static int mainloop(int servfd,sqlite3 *pDB)
{
	int datafd = -1;
	pid_t spid;
	int ret = 0;
	

	signal(SIGCHLD,SIG_IGN);
	while(1)
	{
		datafd = accept(servfd,NULL,NULL);
		if(datafd < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				PrintServerError("Accept Failed\n");
				ret = -1;
				break;
			}
		}
		spid = fork();
        if(spid < 0)
        {
			PrintServerError("fork Failed\n");
        }
        else if(spid == 0)
        {
			close(servfd);
			servfd = -1;
			ret = HandleClient(datafd,pDB);
			exit(0);
        }
        else
        {
			close(datafd);
			datafd = -1;
        }
	}

	return ret;
}

