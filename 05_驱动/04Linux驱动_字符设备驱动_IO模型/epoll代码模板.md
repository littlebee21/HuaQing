```c
int epoll_create(int size);
/*
功能：创建epoll描述符
参数：size：epoll描述符监测的文件描述符的个数，大于0的数字
返回值：成功合法描述符，失败：-1
*/

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
/*
功能：epoll的事件注册函数
参数：epfd：epoll描述符
Op：表示动作
	EPOLL_CTL_ADD：注册新的fd到epfd中；
	EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
	EPOLL_CTL_DEL：从epfd中删除一个fd；
fd：需要监听的fd
Event:告诉内核需要监听什么事
typedef union epoll_data {
		void *ptr;
		int fd;
		__uint32_t u32;
		__uint64_t u64;
	} epoll_data_t;

struct epoll_event {
		__uint32_t events; // Epoll events     EPOLLIN EPOLLOUT
		epoll_data_t data; // User data variable
};
返回值：成功：0  失败：-1
 */

int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
/*
功能：等待事件的产生
参数：epfd：epoll的文件描述符
     events：用来从内核得到事件的集合
  Maxevents：告之内核这个events有多大，不能大于创建epoll_create()时的size
  Timeout：超时时间（毫秒，0会立即返回，-1将一直阻塞不超时）。
返回值：成功：返回需要处理的事件数目
   			超时：0
*/

//使用模板
epollfd = epoll_create(10);//创建epoll对象
struct epoll_event evt;
struct epoll_event * pevtret = NULL;
int fdnum = 0;
int i = 0;

evt.data.fd = fd1;
evt.events = EPOLLIN | EPOLLOUT;
epoll_ctl(epollfd,EPOLL_CTL_ADD,fd1,&evt);////注册epoll事件
fdnum++;

evt.data.fd = fd2;
evt.events = EPOLLOUT;
epoll_ctl(epollfd,EPOLL_CTL_ADD,fd2,&evt);
fdnum++;

while(1)
{
    	if(pevtret != NULL)
        {
    		free(pevtret);
        }
 		pevtret = malloc(fdnum * sizeof(struct epoll_event));
    	if(pevtret == NULL)
        {
        	break;
        }
    	memset(pevtret,0,fdnum * sizeof(struct epoll_event));
		ret = epoll_wait(epollfd,pevtret,fdnum,-1);
    	if(ret < 0)
        {
            if(errno = EINTR)
            {
                continue;
            }
            else
            {
                printf("epoll error\n");
                break;
            }
        }
    
    	for(i = 0;i < fdnum;i++)
        {
            if(epd[i].data.fd == 服务端监控连接用描述符)
            {
                newfd=accept(...);
            	evt.data.fd = newfd;
				evt.events = EPOLLIN | EPOLLOUT;
				epoll_ctl(epollfd,EPOLL_CTL_ADD,newfd,&evt);////注册epoll事件
				fdnum++;
            }
            else
            {
            	if(epd[i].events & EPOLLIN)
	            {//读数据
                
    	        }
        	    if(epd[i].events & EPOLLOUT)
            	{//写数据
                
            	}
            }
        }
    	free(pevtret);
    	pevtret = NULL;
}
close(epollfd);

//根据程序逻辑选择适当位置对被监控描述符进行close，同时调epoll_ctl做EPOLL_CTL_DEL操作和fdnum--
```

