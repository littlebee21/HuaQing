/*
 * 从上题的model1.dat文件中读出model们的信息到结构体数组中，按身高从高到低排序后，按如下形式写入到文本文件model3.txt中：
每行保存一个model的信息，每行的组织形式：姓 名 性别 出生年-月-日 身高
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODEL_DAT_FILE "./model1.dat"
#define MODEL_TXT_FILE "./model3.txt"

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

int cmpheight(const void *pv1,const void *pv2);
int main(int argc,char *argv[])
{
	struct model *pst = NULL;
	int cnt = 0;
	FILE *pf = NULL;
	int ret = 0;
	int i = 0;

	pf = fopen(MODEL_DAT_FILE,"rb");
	if(NULL == pf)
	{
		printf("rb-fopen %s failed\n",MODEL_DAT_FILE);
		return 1;
	}

	fseek(pf,0,SEEK_END);
	cnt = ftell(pf);
	fseek(pf,0,SEEK_SET);

	pst = (struct model *)malloc(cnt);
	if(NULL == pst)
	{
		fclose(pf);
		pf = NULL;
		printf("malloc failed\n");
		return 2;
	}
	memset(pst,0,cnt);

	cnt = cnt / sizeof(struct model);

	ret = fread(pst,sizeof(struct model),cnt,pf);
	fclose(pf);
	pf = NULL;
	if(ret != cnt)
	{
		free(pst);
		pst = NULL;
		printf("read model info failed,ret=%d\n",ret);
		return 3;
	}

	qsort(pst,cnt,sizeof(struct model),cmpheight);

	pf = fopen(MODEL_TXT_FILE,"w");
	if(NULL == pf)
	{
		printf("w-fopen %s failed\n",MODEL_TXT_FILE);
		free(pst);
		pst = NULL;
		return 4;
	}

	for(i = 0;i < cnt;i++)
	{
		fprintf(pf,"%s %s %c %d-%d-%d %.2f\n",
			   (pst+i)->secondname,
			   (pst+i)->firstname,
			   (pst+i)->sex,
			   (pst+i)->birth.y,
			   (pst+i)->birth.m,
			   (pst+i)->birth.d,
			   (pst+i)->height
		       );
	}

	fclose(pf);
	pf = NULL;

	free(pst);
	pst = NULL;

	return 0;
}

int cmpheight(const void *pv1,const void *pv2)
{
	float h1 = ((struct model *)pv1)->height;
	float h2 = ((struct model *)pv2)->height;

	if(h1 > h2)
	{
		return -1;
	}
	else if(h1 < h2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
