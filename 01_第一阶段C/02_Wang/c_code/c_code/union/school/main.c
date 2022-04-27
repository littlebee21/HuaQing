#include "school.h"

int main(int argc,char *argv[])
{
	int cnt = 0;
	struct person *pt = NULL;

	if(argc < 2)
	{
		printf("The argument is too few,Usage:./sch 6\n");
		return 1;
	}

	sscanf(argv[1],"%d",&cnt);

	pt = (struct person *)malloc(cnt * sizeof(struct person));
	if(NULL == pt)
	{
		printf("Malloc failed\n");
		return 2;
	}
	memset(pt,0,cnt * sizeof(*pt));


	input_persons(pt,cnt);

	printf("The avescore of student is %.1f\n",get_student_avescore(pt,cnt));

	output_math_teacherinfo(pt,cnt);

	free(pt);
	pt = NULL;
	return 0;
}
