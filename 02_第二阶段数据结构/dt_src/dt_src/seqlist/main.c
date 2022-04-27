#include "person_sl.h"

int main(int argc,char *argv[])
{
	struct seqlist *psl = create_seqlist(40);
	T t = {"Xiaocai",'F',"14444444444","Taiwan diyu"};
	int ret = 0;

	insert_at_head(psl,&t);

	strcpy(t.name,"ATian");
	t.sex = 'M';
	strcpy(t.phone,"17777777777");
	strcpy(t.address,"Japan fushishan");
	insert_at_head(psl,&t);

	strcpy(t.name,"Dawen");
	t.sex = 'M';
	strcpy(t.phone,"15555555555");
	strcpy(t.address,"Korea shouer");
	insert_at_head(psl,&t);

	strcpy(t.name,"Laobai");
	t.sex = 'M';
	strcpy(t.phone,"19999999999");
	strcpy(t.address,"America huashengdun");
	insert_at_tail(psl,&t);
	
	strcpy(t.name,"Ruhua");
	t.sex = 'F';
	strcpy(t.phone,"18888888888");
	strcpy(t.address,"Nanjin xianhemen");
	insert_at_location(psl,&t,3);

	printf("After insert:*********************\n");
	print_all_person(psl);
	printf("**********************************\n");

	delete_at_head(psl);
	delete_at_location(psl,2);
	delete_at_tail(psl);
	
	printf("After detele:*********************\n");
	print_all_person(psl);
	printf("**********************************\n");

	ret = search_by_name(psl,"Xiaocai");
	if(ret < 0)
	{
		printf("Not found!\n");
	}
	else
	{
		print_a_person(psl->pt + ret);


		strcpy(t.name,"Xiaocai");
		t.sex = 'M';
		strcpy(t.phone,"748748748748");
		strcpy(t.address,"Taiwan xinzhu");
		modify(psl,ret,&t);
		
		print_a_person(psl->pt + ret);
	}

	sort_by_phone(psl);
	printf("After sort:*********************\n");
	print_all_person(psl);
	printf("**********************************\n");

	destroy_seqlist(psl);
	psl = NULL;
	return 0;
}
