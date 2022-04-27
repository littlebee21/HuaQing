#include <stdio.h>
#include <string.h>

int main()
{
	/*
	char buf[] = "12#34*56";
	int x = 0;
	int y = 0;
	int z = 0;

	sscanf(buf,"%d#%d*%d",&x,&y,&z);

	printf("x=%d,y=%d,z=%d\n",x,y,z);
	*/

	/*
	char buf[] = "Zhang 	\nSan";
	char xing[20] = "";
	char ming[20] = "";

	sscanf(buf,"%s%s",xing,ming);
	printf("xing is %s,ming is %s\n",xing,ming);
	*/
	
	char buf[] = "Zhang#San";
	char xing[20] = "";
	char ming[20] = "";

	//sscanf(buf,"%s%s",xing,ming); //No OK
	//sscanf(buf,"%s#%s",xing,ming); //No OK
	
	{
		char *p = NULL;

		p = strchr(buf,'#');
		strncpy(xing,buf,p - buf);

		p++;
		strcpy(ming,p);
	}

	printf("xing is %s,ming is %s\n",xing,ming);
	return 0;
}
