#ifndef DICTOL_PUBLIC_H
#define DICTOL_PUBLIC_H

#include "dictolprotocol.h"
#include "dictoldebug.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))

int MyWrite(int fd, void *pvBuf, size_t n);
int MyRead(int fd, void *pvBuf, size_t n);

char *MyGetString(char *pacBuf,int size);

/*
  该函数确保从已打开的文本文件中读出整行
  因此该函数返回的是动态分配内存空间的首地址，别忘记不用该空间后应及时调用free进行释放

  linelen参数用来保存整行字符串的长度，注意已去除结尾的'\n'和次结尾的'\r'
*/
char *MyReadLineFromTxt(FILE *pf,int *linelen);

#endif
