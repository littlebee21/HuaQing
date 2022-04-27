```c
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
/*
功能：监测多个监听多个文件描述符，阻塞等待有一个或者多个文件描述符，准备	就绪。
参数：fds:待检测的文件描述符集合
  nfds:待检测的文件描述符的个数
  timeout：超时时间,负数为永久阻塞，0为不阻塞，正数为毫秒数
返回值：成功：返回大于0的数值   失败：-1  超时为0

poll的结构体
struct pollfd{
		int	fd;		   //文件描述符
		short		events;    //设置的可读可写的掩码
		short	revents;   //返回的可读可写的掩码
}；
*/

/*使用模板*/
struct pollfd pd[2] = {{-1}，{-1}};

while(1)
{
    pd[0].fd = fd1;
    pd[0].events = POLLIN;
    pd[0].revents = 0;
    pd[1].fd = fd2;
    pd[1].events = POLLOUT;
    pd[1].revents = 0;

    ret = poll(pd,2,-1);
	if(ret < 0)
	{
        if(errno == EINTR)
        {
            continue;
        }
        else
        {
			perror("poll error!\n");
			break;
        }
	}
    for(i = 0;i < N;i++)
    {
		if(pd[i].revents & POLLIN)
	    {//用数组pd中下标为0的元素的fd成员读数据
    	    //.....
		} 
		if(pd[i].revents & POLLOUT)
	    {//用数组pd中下标1的元素的fd成员写数据
    	    //.....
		}
    }
}
```

