/*
 * 给定一个bmp图片文件，输出该图片的款和高，bmp文件二进制位布局描述，自行网络搜索：bmp文件格式
 * */
#include <stdio.h>


int main(int argc,char *argv[])
{
	FILE *pf1 = NULL;
	int width = 0;
	int height = 0;
	int ret = 0;
	char ch1 = '\0';
	char ch2 = '\0';
	
	if(argc < 2)
	{
		printf("The argument is too few,Uasge:./readwh bmp_file_name\n");
		return 1;
	}


	pf1 = fopen(argv[1],"rb");
	if(NULL == pf1)
	{
		printf("fopen %s failed\n",argv[1]);
		return 2;
	}

	fread(&ch1,sizeof(char),1,pf1);
	fread(&ch2,sizeof(char),1,pf1);

	if(ch1 != 'B' || ch2 != 'M')
	{
		fclose(pf1);
		pf1 = NULL;
		printf("The %s file is not bmp file\n",argv[1]);
		return 3;
	}

	fseek(pf1,18,SEEK_SET);
	ret = fread(&width,sizeof(int),1,pf1);
	if(ret != 1)
	{
		printf("read width failed\n");
		fclose(pf1);
		pf1 = NULL;
		return 4;
	}

	ret = fread(&height,sizeof(int),1,pf1);
	if(ret != 1)
	{
		printf("read height failed\n");
		fclose(pf1);
		pf1 = NULL;
		return 5;
	}

	if(width < 0)
	{
		width = -width;
	}
	if(height < 0)
	{
		height = -height;
	}

	printf("The %s:width-%d,height-%d\n",argv[1],width,height);

	fclose(pf1);
	pf1 = NULL;
	return 0;
}

