#include "cprivate.h"

int Do_UserLogin(struct DictOLClientCTL * pstClient)
{
   int ret = 1;
   struct DictOLPDU *pstPDU = NULL;
   char acUserName[NAME_LEN] = "";
   char acPassword[PASS_LEN] = "";
   int i = 0;

   if(NULL == pstClient)
   {
      PrintClientError("Invalid Input Parameter!!!\n");
      return -1;
   }

   for(i = 0;i < 3;i++)
   {
      /*读用户输入的用户名和密码*/
      memset(acUserName,0,NAME_LEN);
      memset(acPassword,0,PASS_LEN);
      InputUserName(acUserName,NAME_LEN,i);
      InputPassword(acPassword,PASS_LEN,i);
   
      /*创建并发送登录PDU*/
      pstPDU = CreateLoginREQPDU(acUserName,acPassword);
      if(NULL == pstPDU)
      {
         PrintClientError("Create Login User Name PDU Error!!!\n");
         ret = -2;
         break;
      }
      ret = SendPDU(pstClient->sockfd,pstPDU);
      DestroyDictOLPDU(pstPDU);
      pstPDU = NULL;
      if(ret != 0)
      {
         PrintClientError("Send Login PDU Failed\n");
         ret = -3;
         break;
      }

      /*接收并处理服务发送过来回应*/
      pstPDU = RecvPDU(pstClient->sockfd);
      if(pstPDU != NULL && DICTOL_PDU_TYPE_LOGIN_RSP == pstPDU->type && 0 == *(int *)pstPDU->buf)
      {//登录成功
         strcpy(pstClient->acClientUserName,acUserName);
         DestroyDictOLPDU(pstPDU);
         ret = 0;
         break;
      }
      else
      {//登录失败
         if(NULL == pstPDU)
         {
            PrintClientError("Login Failed:RecvPDU Error\n");
            ret = -4;
            break;
         }
	 ret = 1;
         if(DICTOL_PDU_TYPE_LOGIN_RSP != pstPDU->type)
         {
            PrintClientError("Login Failed:The PDU is invalid\n");
         }
         else
         {
            PrintClientError("Login Check Name Failed Cause:%d\n",*(int *)(pstPDU->buf));
         }
         DestroyDictOLPDU(pstPDU);
      }
   }//end for

   if(ret > 0)
   {
      DisplayLoginRedoFailed();
   }
   else if(ret < 0)
   {
      DisplayLoginExitFailed();
   }
   else
   {
      DisplayLoginOK();
   }
   return ret;
}
