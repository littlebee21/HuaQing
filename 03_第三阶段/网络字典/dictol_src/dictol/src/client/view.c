#include "cprivate.h"

int DisplayMainUI()
{
    int cmd = -1;

    do
    {
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@1.Register    @@@@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@2.Login       @@@@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@0.Exit        @@@@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@Please Input Your Choice@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

        scanf("%d",&cmd);
        while(getchar() != '\n')
        {
        }

        if(cmd < 0 || cmd > 2)
        {
            printf("Your input is invalid,please redo it\n");
            continue;
        }
        else
        {
            break;
        }
    }while(1);

    return cmd;
}

int DisplayFunctionUI()
{
    int cmd = -1;

    do
    {
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@1.Query Word    @@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@2.Query History @@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@0.Exit          @@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@Please Input Your Choice@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

        scanf("%d",&cmd);
        while(getchar() != '\n')
        {
        }

        if(cmd < 0 || cmd > 2)
        {
            printf("Your input is invalid,please redo it\n");
            continue;
        }
        else
        {
            break;
        }
    }while(1);

    return cmd;
}

char *InputUserName(char *pstr,int size,int times)
{
    char *pret = NULL;

    if(times)
    {
        printf("Please input your name again at %d times:\n",times+1);
    }
    else
    {
        printf("Please input your name:\n");
    }

    pret = MyGetString(pstr,size);

    return pret;
}

char *InputPassword(char *pstr,int size,int times)
{
    char *pret = NULL;

    if(times)
    {
        printf("Please input your password again at %d times:\n",times+1);
    }
    else
    {
        printf("Please input your password:\n");
    }

    pret = MyGetString(pstr,size);

    return pret;
}

char *InputWord(char *pstr,int size)
{
    char *pret = NULL;

    printf("Please input a word:\n");

    pret = MyGetString(pstr,size);

    return pret;
}

void DisplayExplain(char *word,char *explain)
{
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    if(strcmp(explain,QUERY_WORD_ERR_STR) != 0)
    {
        printf("Means of %s is:\n",word);
        printf("%s\n",explain);
    }
    else
    {
        printf("Means of %s is %s!!!\n",word,explain);
    }
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}

void DisplayHistory(char *username,char *history)
{//字符串内容为'@'分隔的多条历史记录，每条历史记录用#分隔时间和单词
    char *p = NULL;
    
    if(strcmp(history,QUERY_HISTORY_ERR_STR) == 0)
    {
        printf("%s have %s\n",username,history);
        return;
    }
    printf("***************************************************************\n");
    printf("%s's history list:\n",username);
    p = history;
    while(*p != '\0')
    {
        if(*p == '#')
        {
            printf("\t");
        }
        else if(*p == '@')
        {
            printf("\n");
        }
        else
        {
            printf("%c",*p);
        }
        p++;
    }
    //printf("\n");
    printf("***************************************************************\n");
    
    return;
}

void DisplayLoginRedoFailed()
{
    printf("Three times login failed,We will back MainUI\n");
}

void DisplayLoginExitFailed()
{
    printf("Login failed,We will exit program\n");
}

void DisplayLoginOK()
{
    printf("Login OK!!!\n");
}

void DisplayRegisterRedoFailed()
{
    printf("Register failed,We will back MainUI\n");
}

void DisplayRegisterExitFailed()
{
    printf("Register failed,We will exit program\n");
}

void DisplayRegisterOK()
{
    printf("Register OK!!!\n");
}

