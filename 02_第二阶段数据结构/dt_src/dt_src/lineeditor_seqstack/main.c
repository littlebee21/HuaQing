#include "charstack.h"

int main(int argc,char *argv[])
{
	char ch = '\0';
	struct charstack *pst = create_charstack(100);

	printf("Please input your line-content:\n");

	ch = getchar();
	while(ch != '\n')
	{
		switch(ch)
		{
			case '#'://出栈
				pop_charstack(pst);
				break;
			case '@'://清空栈
				clear_charstack(pst);
				break;
			default://入栈
				push_charstack(pst,ch);
				break;
		}
		ch = getchar();
	}

	print_charstack(pst);
	destroy_charstack(pst);
	pst = NULL;
	return 0;
}
