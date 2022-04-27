#include <iostream>

using namespace std;

// 注意：inline关键字在函数声明之前不起作用
/*inline */int getAddValue();  // 这是函数声明

inline int getAddValue(){
    // 有循环/分支等复杂的控制结构在函数体内时，不要使用inline函数
//    for(int i=0; i<100; i++){

//    }
    return 1000;
}

int main()
{
    cout << getAddValue() << endl;
    return 0;
}
