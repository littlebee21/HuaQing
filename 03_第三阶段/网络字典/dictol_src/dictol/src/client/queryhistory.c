#include "cprivate.h"

int Do_QueryHistory(struct DictOLClientCTL * pstClient)
{
   int ret = 1;
   struct DictOLPDU *pstPDU = NULL;

   if(NULL == pstClient)
   {
      PrintClientError("Invalid Input Parameter!!!\n");
      return -1;
   }

   do
   {
      /*创建并发送查询历史记录的PDU*/
      pstPDU = CreateHistoryREQPDU();
      if(NULL == pstPDU)
      {
         PrintClientError("Create QueryHistory User Name PDU Error!!!\n");
         ret = -2;
         break;
      }
      ret = SendPDU(pstClient->sockfd,pstPDU);
      DestroyDictOLPDU(pstPDU);
      pstPDU = NULL;
      if(ret != 0)
      {
         PrintClientError("Send QueryHistory PDU Failed\n");
         ret = -3;
         break;
      }

      /*接收并处理服务发送过来回应*/
      pstPDU = RecvPDU(pstClient->sockfd);
      if(pstPDU != NULL && DICTOL_PDU_TYPE_HISTORY_RSP == pstPDU->type)
      {//查询历史操作成功，但未必找到了历史记录
         DisplayHistory(pstClient->acClientUserName,pstPDU->buf);
         DestroyDictOLPDU(pstPDU);
         ret = 0;
         break;
      }
      else
      {//查询历史记录失败
         if(NULL == pstPDU)
         {
            PrintClientError("QueryHistory Failed:RecvPDU Error\n");
            ret = -4;
            break;
         }
         if(DICTOL_PDU_TYPE_HISTORY_RSP != pstPDU->type)
         {
            PrintClientError("QueryHistory Failed:The PDU is invalid\n");
         }
         DestroyDictOLPDU(pstPDU);
      }
   }while(0);

   return ret;
}
