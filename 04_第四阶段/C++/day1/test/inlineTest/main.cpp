#include <iostream>

using namespace std;

// ע�⣺inline�ؼ����ں�������֮ǰ��������
/*inline */int getAddValue();  // ���Ǻ�������

inline int getAddValue(){
    // ��ѭ��/��֧�ȸ��ӵĿ��ƽṹ�ں�������ʱ����Ҫʹ��inline����
//    for(int i=0; i<100; i++){

//    }
    return 1000;
}

int main()
{
    cout << getAddValue() << endl;
    return 0;
}
