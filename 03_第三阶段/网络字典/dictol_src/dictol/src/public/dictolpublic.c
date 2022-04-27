#include "dictolpublic.h"

int MyWrite(int fd, void *pvBuf, size_t n)
{
   size_t nLeft = n;
   size_t nWrite = 0;
   char *pcTemp = (char *)pvBuf;

   while(nLeft > 0)
   {
      nWrite = write(fd,pcTemp,nLeft);
      if(nWrite <= 0)
      {
         if(nWrite < 0 && errno == EINTR)
         {
            nWrite = 0;
         }
         else
         {
            return -1;
         }
      }
      nLeft = nLeft - nWrite;
      pcTemp = pcTemp + nWrite;
   }

   return (n - nLeft);
}

int MyRead(int fd, void *pvBuf, size_t n)
{
   size_t nLeft = n;
   size_t nRead = 0;
   char *pcTemp = (char *)pvBuf;

   while(nLeft > 0)
   {
      nRead = read(fd,pcTemp,nLeft);
      if(nRead < 0)
      {
         if(errno == EINTR)
         {
            nRead = 0;
         }
         else
         {
            return -1;
         }
      }
      else if(0 == nRead)
      {
         return 0;
      }
      nLeft = nLeft - nRead;
      pcTemp = pcTemp + nRead;
   }

   return (n - nLeft);
}

char *MyGetString(char *pacBuf,int size)
{
    int len = 0;
    char *p = 0;
    if(NULL == pacBuf || size <= 0)
    {
        PrintPublicError("Input Param is invalid\n");
        return NULL;
    }
    p = fgets(pacBuf,size,stdin);
    if(NULL == p)
    {
        PrintPublicError("fgets failed\n");
        return NULL;
    }

    len = strlen(pacBuf);
    if(pacBuf[len-1]=='\n')
    {
        pacBuf[len-1] = '\0';
    }
    else
    {
        while(getchar()!='\n')
        {
            ;
        }
    }
    return pacBuf;	
}

char *MyReadLineFromTxt(FILE *pf,int *linelen)
{
    int len = 0;
    char *p = 0;
    char *pret = 0;
    long cur = 0;
    int ret = 0;

    if(NULL == pf)
    {
        PrintPublicError("Input Param is invalid \n");
        return NULL;
    }
    
    if(linelen != NULL)
    {
        *linelen = 0;
    }

    cur = ftell(pf);
    
    ret = fgetc(pf);
    while(ret >= 0 && ret != '\n')
    {
	len++;
    	ret = fgetc(pf);
    }
    if(ret == '\n')
    {
        len++;
    }

    if(len <= 0)
    {
	return NULL;
    }

    fseek(pf,cur,SEEK_SET);

    p =(char *)malloc(len+1);
    if(NULL == p)
    {
        PrintPublicError("malloc failed\n");
	return NULL;
    }
    memset(p,0,len+1);

    pret = fgets(p,len+1,pf);
    if(pret != p)
    {
        PrintPublicError("fgets failed\n");
        free(p);
        return NULL;
    }

    if(p[len-1]=='\n')
    {
        p[len-1] = '\0';
	len--;
    }
    if(p[len-1]=='\r')
    {
        p[len-1] = '\0';
	len--;
    }

    if(linelen != NULL)
    {
        *linelen = len;
    }
    return p;	
}
