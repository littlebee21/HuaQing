#include "charstack.h"

int main(int argc,char *argv[])
{
	char ch = '\0';
	struct charstack *pst = create_charstack(100);
	struct charnode *ptemp = NULL;

	printf("Please input your line-content:\n");

	ch = getchar();
	while(ch != '\n')
	{
		switch(ch)
		{
			case '#'://出栈
				ptemp = pop_charstack(pst);
				destroy_charnode(ptemp);
				ptemp = NULL;
				break;
			case '@'://清空栈
				clear_charstack(pst);
				break;
			default://入栈
				ptemp = create_charnode(ch);
				push_charstack(pst,ptemp);
				break;
		}
		ch = getchar();
	}

	print_charstack(pst);

	destroy_charstack(pst);
	pst = NULL;
	return 0;
}
