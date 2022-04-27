#include "person_ll.h"

int main(int argc,char *argv[])
{
	struct linklist *pll = create_linklist();
	T t = {"Xiaocai",'F',"14444444444","Taiwan diyu"};
	struct node *pnew = NULL;
	struct node *ptemp = NULL;

	ptemp = pnew = create_node(&t);
	insert_at_head(pll,pnew);

	strcpy(t.name,"ATian");
	t.sex = 'M';
	strcpy(t.phone,"17777777777");
	strcpy(t.address,"Japan fushishan");
	pnew = create_node(&t);
	insert_at_head(pll,pnew);

	strcpy(t.name,"Dawen");
	t.sex = 'M';
	strcpy(t.phone,"15555555555");
	strcpy(t.address,"Korea shouer");
	pnew = create_node(&t);
	insert_at_head(pll,pnew);

	strcpy(t.name,"Laobai");
	t.sex = 'M';
	strcpy(t.phone,"19999999999");
	strcpy(t.address,"America huashengdun");
	pnew = create_node(&t);
	insert_at_tail(pll,pnew);
	
	strcpy(t.name,"Ruhua");
	t.sex = 'F';
	strcpy(t.phone,"18888888888");
	strcpy(t.address,"Nanjin xianhemen");
	pnew = create_node(&t);
	insert_at_after_node(pll,ptemp,pnew);

	printf("After insert:*********************\n");
	print_all_person(pll);
	printf("**********************************\n");

	ptemp = remove_at_head(pll);
	destroy_node(ptemp);

	ptemp = search_by_name(pll,"Ruhua");
	if(ptemp != NULL)
	{
		remove_a_node(pll,ptemp);
		destroy_node(ptemp);
	}
	else
	{
		printf("Not find Ruhua\n");
	}

	ptemp = remove_at_tail(pll);
	destroy_node(ptemp);
	
	printf("After detele:*********************\n");
	print_all_person(pll);
	printf("**********************************\n");

	ptemp = search_by_name(pll,"Xiaocai");
	if(NULL == ptemp)
	{
		printf("Not found!\n");
	}
	else
	{
		print_a_person(ptemp);


		strcpy(t.name,"Xiaocai");
		t.sex = 'M';
		strcpy(t.phone,"748748748748");
		strcpy(t.address,"Taiwan xinzhu");
		modify(ptemp,&t);
		
		print_a_person(ptemp);
	}
	
	/*
	sort_by_phone(pll);
	printf("After sort:*********************\n");
	print_all_person(pll);
	printf("**********************************\n");
	*/

	destroy_linklist(pll);
	pll = NULL;
	return 0;
}
