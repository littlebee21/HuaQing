#include "cprivate.h"

int Do_QueryWord(struct DictOLClientCTL * pstClient)
{
   int ret = 1;
   struct DictOLPDU *pstPDU = NULL;
   char acWord[WORD_LEN] = "";

   if(NULL == pstClient)
   {
      PrintClientError("Invalid Input Parameter!!!\n");
      return -1;
   }

   do
   {
      /*读用户输入的单词*/
      InputWord(acWord,WORD_LEN);
   
      /*创建并发送注册PDU*/
      pstPDU = CreateQueryWordREQPDU(acWord);
      if(NULL == pstPDU)
      {
         PrintClientError("Create QueryWord User Name PDU Error!!!\n");
         ret = -2;
         break;
      }
      ret = SendPDU(pstClient->sockfd,pstPDU);
      DestroyDictOLPDU(pstPDU);
      pstPDU = NULL;
      if(ret != 0)
      {
         PrintClientError("Send QueryWord PDU Failed\n");
         ret = -3;
         break;
      }

      /*接收并处理服务发送过来回应*/
      pstPDU = RecvPDU(pstClient->sockfd);
      if(pstPDU != NULL && DICTOL_PDU_TYPE_QUERYWORD_RSP == pstPDU->type)
      {//查询单词操作成功，但未必找到了释义
         DisplayExplain(acWord,pstPDU->buf);
         DestroyDictOLPDU(pstPDU);
         ret = 0;
         break;
      }
      else
      {//查询单词失败
         if(NULL == pstPDU)
         {
            PrintClientError("QueryWord Failed:RecvPDU Error\n");
            ret = -4;
            break;
         }
         if(DICTOL_PDU_TYPE_QUERYWORD_RSP != pstPDU->type)
         {
            PrintClientError("QueryWord Failed:The PDU is invalid\n");
         }
         DestroyDictOLPDU(pstPDU);
      }
   }while(0);

   return ret;
}
