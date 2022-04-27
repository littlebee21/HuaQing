#include <iostream>

using namespace std;

int main()
{
    int *p = new int;
    int *p1 = new int[10];

    // 如果使用malloc分配内存空间
    // (type)malloc(size);

    // 如果没有分配成功， 则返回
    if(!p){
        cout << "new failed!" << endl;
        return 0;
    }

    if(!p1){
        cout << "new array failed!" << endl;
        return 0;
    }
    /// .....
    cout << "Hello World!" << endl;   
    delete p;
    p = nullptr;   // 指针使用完毕以后还要置空，防止悬垂指针（野指针）
    delete[] p1;   // 释放一个数组空间
    p1 = nullptr;

    return 0;
}
