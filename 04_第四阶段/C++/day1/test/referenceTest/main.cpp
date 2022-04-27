#include <iostream>

using namespace std;

void swap1(int x, int y){
    int nTemp = x;
    x = y;
    y = nTemp;
}

void swap2(int *x, int *y){
    int nTemp = *x;
    *x = *y;
    *y = nTemp;
}

void swap3(int &x, int &y){
    int nTemp = x;
    x = y;
    y = nTemp;
}

int main()
{
    int a = 10;
    int &ra = a;
    cout << "a's address = " << &a << endl;
    cout << "ra's address = " << &ra << endl;

    int x = 10, y = 20;
    cout << "x = " << x << "  " << "y = " << y << endl;
    // swap1(x, y);
    // swap2(&x, &y);
    swap3(x, y);
    cout << "x = " << x << "  " << "y = " << y << endl;
    return 0;
}
