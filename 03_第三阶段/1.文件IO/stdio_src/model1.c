/*
已知有文本文件其内容为：
Ruhua Zhang F 1992 3 9 1.8
Siyu Li F 1993 6 19 1.76
Feiyan Zhao F 1999 7 12 1.78
Cengyu Qian  F 2001 9 11 1.79
Luoyan Sun  F 2003 3 6 1.77
每行组成为：名 姓  性别 出生年月日 身高
要求将其读进结构体数组中，输出身高最高的那个人的全部信息
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODEL_FILE_NAME "./model1.txt"

#define FIRST_NAME_LEN 20
#define SECOND_NAME_LEN 12
struct date
{
	int y;
	int m;
	int d;
};

struct model
{
	char firstname[FIRST_NAME_LEN];
	char secondname[SECOND_NAME_LEN];
	char sex;
	struct date birth;
	float height;
};

int get_heightest(struct model *pst,int cnt);
char *myreadline(FILE *pf);

int main(int argc,char *argv[])
{
	FILE *pf = NULL;
	int linecnt = 0;
	char *pret = NULL;
	struct model *pst = NULL;
	int i = 0;
	char sexbuf[4] = "";
	int max = 0;

	/*打开文件*/
	pf = fopen(MODEL_FILE_NAME,"r");
	if(NULL == pf)
	{
		printf("r-fopen %s failed\n",MODEL_FILE_NAME);
		return 1;
	}

	/*读行数*/
	pret = myreadline(pf);
	while(pret != NULL)
	{
		linecnt++;
		free(pret);
		pret = myreadline(pf);
	}
	fseek(pf,0,SEEK_SET);


	/*分配空间*/
	pst = (struct model *)malloc(linecnt * sizeof(struct model));
	if(NULL == pst)
	{
		fclose(pf);
		pf = NULL;
		printf("Malloc Failed!\n");
		return 2;
	}

	/*读信息*/
	for(i = 0;i < linecnt;i++)
	{
		fscanf(pf,"%s%s%s%d%d%d%f",
			  (pst+i)->firstname,
			  (pst+i)->secondname,
			  sexbuf,
			  &((pst+i)->birth.y),
			  &((pst+i)->birth.m),
			  &((pst+i)->birth.d),
			  &((pst+i)->height)
			  );
		(pst+i)->sex = sexbuf[0];
	}

	/*关闭文件*/
	fclose(pf);
	pf = NULL;

	/*get max loc*/
	max = get_heightest(pst,linecnt);

	/*打印最高人的信息*/
	printf("The heightest model info:\n");
	printf("First Name:%s\n",(pst+max)->firstname);
	printf("Second Name:%s\n",(pst+max)->secondname);
	printf("Sex:%c\n",(pst+max)->sex);
	printf("Birth:%d-%d-%d\n",(pst+max)->birth.y,(pst+max)->birth.m,(pst+max)->birth.d);
	printf("Height:%.2f\n",(pst+max)->height);

	/*释放空间*/
	free(pst);
	pst=NULL;
	return 0;
}
int get_heightest(struct model *pst,int cnt)
{
	int max = 0;
	int i = 0;

	for(i = 1;i < cnt;i++)
	{
		if((pst+i)->height > (pst+max)->height)
		{
			max = i;
		}
	}

	return max;
}
