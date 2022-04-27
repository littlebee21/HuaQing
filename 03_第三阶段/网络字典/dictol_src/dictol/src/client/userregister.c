#include "cprivate.h"

int Do_UserRegister(struct DictOLClientCTL * pstClient)
{
   int ret = 1;
   struct DictOLPDU *pstPDU = NULL;
   char acUserName[NAME_LEN] = "";
   char acPassword[PASS_LEN] = "";

   if(NULL == pstClient)
   {
      PrintClientError("Invalid Input Parameter!!!\n");
      return -1;
   }

   do
   {
      /*读用户输入的用户名和密码*/
      InputUserName(acUserName,NAME_LEN,0);
      InputPassword(acPassword,PASS_LEN,0);
   
      /*创建并发送注册PDU*/
      pstPDU = CreateRegisterREQPDU(acUserName,acPassword);
      if(NULL == pstPDU)
      {
         PrintClientError("Create Register User Name PDU Error!!!\n");
         ret = -2;
         break;
      }
      ret = SendPDU(pstClient->sockfd,pstPDU);
      DestroyDictOLPDU(pstPDU);
      pstPDU = NULL;
      if(ret != 0)
      {
         PrintClientError("Send Register PDU Failed\n");
         ret = -3;
         break;
      }

      /*接收并处理服务发送过来回应*/
      pstPDU = RecvPDU(pstClient->sockfd);
      if(pstPDU != NULL && DICTOL_PDU_TYPE_REG_RSP == pstPDU->type && 0 == *(int *)pstPDU->buf)
      {//注册成功
         DestroyDictOLPDU(pstPDU);
         ret = 0;
         break;
      }
      else
      {//注册失败
         if(NULL == pstPDU)
         {
            PrintClientError("Register Failed:RecvPDU Error\n");
            ret = -4;
            break;
         }
         ret = 1;
         if(DICTOL_PDU_TYPE_REG_RSP != pstPDU->type)
         {
            PrintClientError("Register Failed:The PDU is invalid\n");
         }
         else
         {
            PrintClientError("Register Check Name Failed Cause:%d\n",*(int *)(pstPDU->buf));
         }
         DestroyDictOLPDU(pstPDU);
      }
   }while(0);

   if(ret > 0)
   {
      DisplayRegisterRedoFailed();
   }
   else if(ret < 0)
   {
      DisplayRegisterExitFailed();
   }
   else
   {
      DisplayRegisterOK();
   }
   return ret;
}
