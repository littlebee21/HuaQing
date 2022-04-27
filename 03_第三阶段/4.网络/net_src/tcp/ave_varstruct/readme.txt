编译多进程并发版服务端:
gcc server_mp.c avepdu.c -o svr -Wall

编译多线程并发版服务端:
gcc server_mt.c avepdu.c -o svr -Wall -lpthread


编译客户端：
gcc client.c avepdu.c -o clt -Wall
