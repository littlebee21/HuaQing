#include <stdio.h>

//#define false  0
//#define true   1
//#define bool   int

typedef enum{
    false,
    true
}bool;

int main()
{
    bool b = true;

    if(b)   // ���ַ���ͬ��������ָ��
        printf("b is true!\n");     // if(b) <==> if(b != false)
    else
        printf("b is false!\n");    // if(!b) <==> if(b == false)

    return 0;
}
