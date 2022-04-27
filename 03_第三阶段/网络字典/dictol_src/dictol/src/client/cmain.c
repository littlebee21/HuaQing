#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "cprivate.h"

static void InitClientCTL(struct DictOLClientCTL * pstClient);
static void EndClientCTL(struct DictOLClientCTL * pstClient);

static int ConnectServer(struct DictOLClientCTL * pstClient,char *ip,int port);
static void MainUILoop(struct DictOLClientCTL *pstClient);
static int FunctionUILoop(struct DictOLClientCTL *pstClient);
int main(int argc,char *argv[])
{
   struct DictOLClientCTL stClient = {-1};
   int ret = 0;
   int port = 0;

   if(argc < 3)
   {
      PrintClientError("The usage is ./dictolclient ip port\n");
      return 1;
   }
   
   sscanf(argv[2],"%d",&port);
   if(port < 1024 || port > 0xFFFF)
   {
      PrintClientError("port is error\n");
      return 2;
   }
   

   InitClientCTL(&stClient);
   ret = ConnectServer(&stClient,argv[1],port);
   if(0 == ret)
   {
      MainUILoop(&stClient);
   }
   else
   {
      PrintClientError("Can't into ClientMainLoop Function\n");
   }

   EndClientCTL(&stClient);
   return ret;
}

static void InitClientCTL(struct DictOLClientCTL * pstClient)
{
   memset(pstClient,0,sizeof(struct DictOLClientCTL));

   pstClient->sockfd = -1;
}

static void EndClientCTL(struct DictOLClientCTL * pstClient)
{
   if(pstClient->sockfd >= 0)
   {
      close(pstClient->sockfd);
   }
}

static int ConnectServer(struct DictOLClientCTL * pstClient,char *ip,int port)
{
   struct sockaddr_in servaddr;
   int fdSocket = -1;
   int ret = 0;

   fdSocket = socket(AF_INET,SOCK_STREAM,0);
   if(fdSocket < 0)
   {
      PrintClientError("Open Socket Failed!!!\n");
      return -1;
   }

   memset(&servaddr,0,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(port);
   inet_aton(ip,&servaddr.sin_addr);

   ret = connect(fdSocket,(struct sockaddr *)&servaddr,sizeof(servaddr));
   if(ret < 0)
   {
      PrintClientError("Connect Server Failed!!!\n");
      close(fdSocket);
      fdSocket = -1;
   }

   pstClient->sockfd = fdSocket;

   return ret;
}

static void MainUILoop(struct DictOLClientCTL *pstClient)
{
   int op = -1;
   int exitflag = 0;
   int ret = 0;

   if(NULL == pstClient)
   {
      PrintClientError("Invalid Input Parameter!!!\n");
      return;
   }

   while(1)
   {
      op = DisplayMainUI();
      switch(op)
      {
         case 1://register
            ret = Do_UserRegister(pstClient);
            break;
         case 2://login
            ret = Do_UserLogin(pstClient);
            if(ret == 0)
            {//登录成功，进入功能界面
               ret = FunctionUILoop(pstClient);
               if(ret < 0)
               {
                  exitflag = 1;
               }
            }
            else if(ret < 0)
            {
               exitflag = 1;
            }
            break;
         case 0:
            exitflag = 1;
            break;
      }
      if(exitflag)
      {
         break;
      }
   }//end while(1)
}

static int FunctionUILoop(struct DictOLClientCTL *pstClient)
{
   int op = -1;
   int exitflag = 0;
   int ret = 0;

   if(NULL == pstClient)
   {
      PrintClientError("Invalid Input Parameter!!!\n");
      return -1;
   }

   while(1)
   {
      op = DisplayFunctionUI();
      switch(op)
      {
         case 1://Query Word
            ret = Do_QueryWord(pstClient);
            if(ret < 0)
            {
               exitflag = 1;
            }
            break;
         case 2://Query History
            ret = Do_QueryHistory(pstClient);
            if(ret < 0)
            {
               exitflag = 1;
            }
            break;
         case 0:
            exitflag = 1;
            ret = -1;
            break;
         default:
            break;
      }
      if(exitflag)
      {
         break;
      }
   }//end while(1)

   return ret;
}
