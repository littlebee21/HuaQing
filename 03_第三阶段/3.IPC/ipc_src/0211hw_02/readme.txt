进程1向共享字符数组中输入多个字符'a'，进程2向共享字符数组中输入多个字符'b'，进程3等两个进程退出后再执行负责打印该共享字符数组的内容，要求打印的结果不能有ab字符同时出现

编译设置a b进程
gcc setab.c mysem.c -o setab -Wall

编译打印进程
gcc print.c -o print -Wall
