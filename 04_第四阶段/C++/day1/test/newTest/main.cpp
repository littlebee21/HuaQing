#include <iostream>

using namespace std;

int main()
{
    int *p = new int;
    int *p1 = new int[10];

    // ���ʹ��malloc�����ڴ�ռ�
    // (type)malloc(size);

    // ���û�з���ɹ��� �򷵻�
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
    p = nullptr;   // ָ��ʹ������Ժ�Ҫ�ÿգ���ֹ����ָ�루Ұָ�룩
    delete[] p1;   // �ͷ�һ������ռ�
    p1 = nullptr;

    return 0;
}
