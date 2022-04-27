## 多态的实现

### 什么是多态?

1. 相同对象收到不同消息或不同对象收到相同消息时产生的不同的动作。
2. 一个接口，多种方法



### 虚成员函数表（vtable）

​		这一节将介绍多态是如何实现的，关于如何实现多态，对于程序设计人员来说即使不知道也是完全没有关系的，但是对于加深对多态的理解具有重要意义，故而在此节中稍微阐述一下多态的实现机制。

​    	在C++中通过虚成员函数表vtable实现多态，虚函数表中存储的是类中虚函数的入口地址。在普通的类中是没有虚函数表的，只有在具有虚函数的类中（无论是自身添加的虚函数还是继承过来的虚函数表）才会具有虚函数表，通常虚成员函数表的首地址将会被存入对象的最前面（在32位的操作系统中，存储地址是用4个字节，因此这个首地址就会占用对象的前四个字节的空间）。

```C++
// 在这个类中完全没有虚函数表的概念
class A{
public:
    void func(){}
private:
    int x;
};

// 这个类中有虚函数了，所以这个类中已经包含了虚函数表
class B{
public:
    virtual void func(){}		// 这个函数的入口地址就存在虚函数表中
private:
    int x;
};

// 这个类继承自B类，因为B类中含有虚函数表，所以该表也被继承到C类中，也有虚函数表
class C : public B{
};

int main(){
    A a;	// a的大小为4byte
    B b;	// b大小为8byte,因为b中含有虚函数表(vtable),占用4个byte
    return 0;
}
```

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220303174852387.png" alt="image-20220303174852387" style="zoom:50%;" />

```C++
#include <iostream>
using namespace std;
 
class base{
public:
    virtual void v1(){ }
    virtual void v2(){ }
};
 
class derived : public base{
public:
    virtual void v1() override{ }
    virtual void v2() override{ }
};
 
int main(){
    base b;
    derived d;
    base *p;
    p = &b;
    p->v1();
    p->v2();
    p = &d;  // 基类指针指向子类对象
    p->v1();
    p->v2();
 
    return 0;
}
```



我们将两个类定义成例1所示形式，两个类中各有两个虚函数v1和v2，我们将其函数入口地址找到列于下表中：

| 虚成员函数 | 函数入口地址 | 虚成员函数  | 函数入口地址 |
| ---------- | ------------ | ----------- | ------------ |
| base::v1   | 00D15834     | derived::v1 | 00D15844     |
| base::v2   | 00D15838     | derived::v2 | 00D15848     |

​		虚函数表里面存储的就是虚函数的入口地址。我们再来看主函数，在主函数中先定义了base类对象b，因为b类中有虚函数，因此存在虚函数表，而虚函数表的首地址就存储在对象所在存储空间的最前。当然声明derived对象d之后，情况也跟下图中一样，同样在对象存储空间中包含虚成员函数表地址。

​                 ![img](https://qqadapt.qpic.cn/txdocpic/0/0f244c406bed4c1e999c58fbc7a6679d/0?_type=png)        

​    	之后定义了一个基类类型的指针p，当我们通过基类指针p调用虚函数v1或v2时，系统会先去p所指向的对象的前四个字节中寻找到虚函数表地址，之后在内存中找到该虚函数表，然后在表中找到对应函数的入口地址，之后直接访问这个函数了。**当p指针指向的是基类对象时，基类的虚函数表将会被访问，基类中虚函数将会被调用。当p指针指向的是派生类对象，则访问的是派生类的虚函数表，派生类的虚函数表中存的是派生类中的虚函数入口地址，因此调用的是派生类中的虚函数。**

​    	使用多态会降低程序运行效率，使用多态的程序会使用更多的存储空间，存储虚函数表等内容，而且在调用函数时需要去虚函数表中查询函数入口地址，这会增加程序运行时间。在设计程序时，程序设计人员可以选择性的使用多态，对于有需要的函数使用多态，对于其它的函数则不要采用多态。**通常情况下，如果一个类需要作为基类，并且期望在派生类中修改某成员函数的功能，并且在使用类对象的时候会采用指针或引用的形式访问该函数，则将该函数声明为虚函数。**



普通继承

```C++
class A{  
};
// 用于取得基类中的成员方法和属性的过程，会产生拷贝，代码重用的过程
class B ； public A{    
};
```

虚继承(一般用于解决菱形继承产生的相关问题:1. 多重拷贝问题 2. 二义性问题)

```C++
class A{  
public:
    void setValue();
};
// 用于取得基类中的成员方法和属性的过程，会产生拷贝，代码重用的过程
class B : virtual public A{    
};
class C : virtual public A{    
};
class D : public B, public C{    
};

int main(){
    D d;
    d.setValue();	// 虚继承才能不报错
    return 0;
}
```



### 虚析构函数

```C++
#include <iostream>
using namespace std;

class base{
public:
	base();
	~base();
private:
	int *a;
};
 
class derived : public base{
public:
	derived();
	~derived();
private:
	int *b;
};

base::base(){
	cout << "base constructor!" << endl;
	a = new int[10];
}

base::~base(){
	cout << "base destructor!" << endl;
	delete[] a;
} 

derived::derived(){
	cout << "derived constructor!" << endl;
	b = new int[10];
}

derived::~derived(){
	cout << "derived destructor!" << endl;
	delete[]  b;
} 

int main(){
	base *p = new derived;
	delete p;    
    
	return 0;
}
```

​		在本类中定义了两个类，一个基类，一个派生类，派生类和基类中都分别定义了自己的构造函数和析构函数。基类和派生类中各有一个int型指针成员变量，在基类的构造函数中，给指针变量a分配了10个int型空间，在基类的析构函数则用于将是将a所指向的空间释放掉，在派生类的构造函数中，指针成员变量被分配了10个整型空间，派生类的析构函数则是为了释放掉b指针所指向的存储空间。在主函数中，我们创建一个基类类型的指针，指针指向一个派生类对象，之后释放p指针所指向的对象的存储空间。最后程序运行结果如下：

```C++
base constructor!
derived constructor!
base destructor!
```

​		观察程序运行结果，程序打印出了“base  constructor!”这串字符，则说明基类的构造函数被调用了，之后又打印出了“derived constructor!”这串字符，同样地派生类的构造函数也被调用了。当我们用new操作符创建一个派生类对象时会先调用基类构造函数，然后再调用派生类构造函数，程序输出结果与我们料想的是一致的。至此基类的成员变量a通过构造函数被分配了10个整型存储空间，派生类的成员变量b通过构造函数被分配了10个整型存储空间。之后程序打印出了“base destructor!”字符串，这说明基类的析构函数被调用了，a指针所指向的10个整型内存空间被释放了。但是之后却并未调用派生类的析构函数，不调用派生类的析构函数则会导致b指针所指向的10个整型存储空间不会被释放，如此一来造成了内存泄露了。内存泄露问题肯定是我们程序设计人员需要极力避免的。本例中出现的问题就是因为派生类的析构函数未被调用，为了解决这个问题，我们将基类的析构函数声明为虚函数，修改后基类的定义如下： 

```C++
class base{
public:
   base();
   virtual ~base();
private:
   int * a;
};
```



修改基类的定义后，程序运行结果如下:

```C++
base constructor!
derived constructor!
derived destructor!
base destructor!
```



#### 为什么需要使用虚析构函数？

我们先来看一个例子，如下代码你认为最后的输出会是什么呢？

```C++
class A{  
public: 
    ~A(){
        cout << "Destruct class A" << endl;
    }  

class B : public A{  
public:  
    ~B(){
        cout << "Destruct class B " << endl;
    }  
};  

int main(){  
    A *a = new B;  
    delete a;  
    return 0;  
}  
```

输出为:

```C++
Destruct class A 
```



 而只要你在A类的析构函数前加上virtual使其成为一个虚析构函数，那么输出就将是:

```C++
Destruct class B  
Destruct class A  
```

​		一般情况下类的析构函数里面都是释放内存资源，而析构函数不被调用的话就会造成内存泄漏，如上面所说，如果基类析构函数不是虚析构函数的话，将造成只释放了基类部分，而没有释放子类部分，造成内存泄漏。

#### 总结1：

​		虚析构解决内存泄漏问题



#### 什么情况下使用虚析构函数？

​		**当你在程序中使用一个基类的指针指向子类对象的时候，那么你得注意了，此时你的基类析构函数必须为虚析构，在你delete基类指针时，才会先进入子类的析构函数释放资源，再进入基类析构函数释放资源，达到完全释放的效果。**

​		当然，并不是要把所有类的析构函数都写成虚函数。因为当类里面有虚函数的时候，编译器会给类添加一个虚函数表，里面来存放虚函数指针，这样就会增加类的存储空间。所以，只有当一个类被用来作为基类，并且指向子类对象的时候，才把析构函数写成虚函数。

​		将基类的析构函数声明为虚函数之后，派生类的析构函数也自动成为虚析构函数，在主函数中基类指针p指向的是派生类对象，当delete释放p指针所指向的存储空间时，会执行派生类的析构函数，派生类的析构函数执行完之后会紧接着执行基类的析构函数，以释放从基类继承过来的成员变量所消耗的资源。如此一来就不会存在内存泄漏问题了。



#### 结论

​		从此例中我们很明显可以看出析构函数声明为虚函数的必要性，但是如果将所有的基类的析构函数都声明为虚函数，这也是不合适的。通常来说，如果基类中存在一个指向动态分配内存的成员变量，并且基类的析构函数中定义了释放该动态分配内存的代码，则应该将基类的析构函数声明为虚函数。



#### 总结2：

​		构造函数能不能是虚函数		// ❌

​		析构函数能不能是虚函数		// ✔

​		构造函数能不能重载				// ✔

​		析构函数能不能重载				// ❌



### C++静态成员函数

只有非静态成员函数才可以成为虚函数，而静态成员函数不能声明为虚函数。

```C++
class test{
public :
    virtual test(){a = new int[5];}     // error
    static void g();         			// ok
    virtual void f();        			// ok
    virtual static void h(); 			// compile  error
    virtual ~test(){delete[] a;} 		// ok
  
private:
    int *a;
};
```

​		在本例中定义了一个test类，这个类中有一个指针成员变量a，test类中有五个成员函数，在本例中将析构函数和普通成员函数f声明为虚函数是没有问题的，将构造函数和静态成员函数声明为虚函数则会出现编译错误，这两种做法都是有违C++语法规定的。





## 重载/重写/覆盖/遮蔽/隐藏 区别和联系

2) 覆盖（重写override）

​		覆盖构成条件和多态构成条件是相同的，覆盖是一种函数间的表现关系，而多态描述的是函数的一种性质，二者所描述的其实是同一种语法现象。

​		覆盖首先要求有继承关系，其次是要求构成继承关系的两个类中必须具有相同函数名的成员函数，并且这两个成员函数必须是虚成员函数，具备这两个条件后，派生类中的虚成员函数则会覆盖基类中的同名的虚成员函数。如果我们通过基类指针或引用来调用虚成员函数，则会形成多态。



例1：

```C++
#include <iostream>
using namespace std;

class base{
public :
    virtual void vir1(){}
    virtual void vir2(){}
    virtual ~base(){}
};

class derived : public base{
public:
    void vir1(){}
    void vir2(){}
};

int main(){
    base *p = new derived;
    p->vir1();
    p->vir2();
    delete p;
    return 0;
}
```

​		本例是一个非常简单的多态的示例程序，base类和derived类构成继承关系，在这两个类中成员函数vir1和vir2同名，并且这两个同名函数都被声明为了虚函数。如此一来则构成了函数覆盖，派生类中的vir1函数覆盖了基类中的vir1函数，派生类中的vir2函数覆盖了基类中的vir2函数。在主函数中通过基类指针调用vir1和vir2虚函数，构成多态，这两个函数的运行为运行期绑定。

​		函数覆盖属于运行期绑定，但是要注意如果函数不是虚函数，则无论采用什么方法调用函数均为编译期绑定。如果我们将例6中的基类中的两个virtual关键字去掉，则主函数中调用vir1和vir2函数属于编译期绑定，无论p指向的是派生类对象或者是基类对象，执行的都将会是基类的vir1和vir2函数。



3) 遮蔽(隐藏)

函数遮蔽同样要求构成继承关系，构成继承关系的两个类中具有相同函数名的函数，如果这两个函数不够成覆盖关系，则就构成了遮蔽关系。遮蔽理解起来很简单，只要派生类与基类中具有相同函数名（注意不是相同函数签名，只需要相同函数名就可以了）并且不构成覆盖关系即为遮蔽。

遮蔽可以分为两种情况，一种是非虚函数之间，另一种则是虚函数之间。我们通过程序示例来分别介绍这两种遮蔽情况。



例2：

```C++
#include <iostream>
using namespace std;

class base{
public:
    void vir1(){cout << "base vir1" << endl;}
    void vir2(){cout << "base vir2" << endl;}
};

class derived : public base{
public:
    void vir1(){cout << "derived vir1" << endl;}
    void vir2(int){cout << "derived vir2" << endl;}
};

int main(){
    base* p = new derived;  // 自由存储区分配
    p->vir1();
    p->vir2();
    delete p;
    derived d;              // 栈分配
    d.vir1();
    d.vir2(5);
    d.base::vir1();
    d.base::vir2();
    return  0;
}
```

​		在本例中没有虚函数，base类和derived类构成继承关系，因为构成继承关系的两个类中有同名函数，因此构成了函数遮蔽。派生类中的vir1函数遮蔽了基类中的vir1函数，派生类中的vir2函数遮蔽了基类中的vir1函数。需要注意的是虽然派生类中的vir2函数和基类中的vir2函数的函数签名不同，但是只需要函数名相同就构成函数遮蔽。我们接着来分析一下主函数，主函数中我们先是定义了基类类型的指针，指针指向的是派生类对象，然后通过指针调用函数vir1和vir2，这个时候因为并不构成多态，因此调用的还是基类的vir1和vir2函数。之后定义了一个派生类对象d，通过该对象调用vir1和vir2函数，因为派生类中的vir1和vir2遮蔽了基类中的vir1和vir2函数，因此直接调用的将会是派生类中的vir1和vir2函数。如果需要通过派生类对象调用被遮蔽的基类中的函数，则需要通过域解析操作符来处理，在本例的最后d.base::vir1();和d.base::vir2()就是这么做的。这个程序的最终运行结果如下:

```C++
 base vir1
 base vir2
 derived vir1
 derived vir2
 base vir1
 base vir2
```

​		如果构成继承关系的两个类中包含同名的虚函数，则情况非常复杂，当然要判断还是非常简单，还是那个原则：如果没有构成覆盖则为遮蔽。覆盖要求的是函数签名相同，而遮蔽只需要函数名相同。



例3:

```C++
#include<iostream>
using namespace std;

class base{
public :
    virtual void vir1(){cout << "base vir1" <<endl;}
    virtual void vir2(){cout << "base vir2" <<endl;}
};

class derived : public base{
public:
    virtual void vir1() override{cout << "derived vir1" << endl;}
    virtual void vir2(int){cout << "derived vir2" << endl;}
};

int main(){
    base *p = new derived;
    p->vir1();    // 多态
    p->vir2();    // 常规调用
    delete p;
    p = nullptr;
    derived d;
    d.vir1();      // 常规调用 
    d.vir2(5);     // 常规调用 
    d.base::vir1();
    d.base::vir2();
    return  0;
}
```

​		在这个程序中，定义了两个类，base类和derived类，这两个类构成继承关系，派生类和基类中包含同名的函数，并且同名的函数均为虚函数。针对这两个同名函数，我们一个一个来分析一下，首先来看一下vir1，基类和派生类中的vir1函数的函数签名是相同的，而且又是虚函数，构成了函数覆盖关系。再来看一下vir2函数，基类中的vir2函数和派生类中的vir2函数函数名相同，但函数参数不同，则它们的函数签名不同，因此派生类中的vir2函数和基类中的vir1函数不构成函数覆盖，既然函数名相同，那么可以构成函数遮蔽。

接着我们同样来看一下主函数，在主函数中，我们定义了一个基类类型的指针，指针指向派生类对象，之后通过该指针分别调用vir1和vir2函数。由于vir1是构成函数覆盖，因此通过基类指针调用vir1构成多态，由于p指针指向的是派生类对象，故调用的vir1函数是派生类中的vir1函数。派生类中的vir2函数和基类中的vir2函数只构成函数遮蔽，因此通过基类类型指针调用vir2函数并不会形成多态，最终调用的是基类中的vir2函数。之后定义了派生类对象d，通过派生类对象d调用的函数只能是派生类中的函数，当然也包括从基类中继承来的函数。d.vir1()和d.vir2(5)这两个函数调用语句调用的都是派生类中新增的成员函数，派生类中的vir1函数虽然和基类中的vir1函数构成覆盖关系，但是由于没有通过基类指针或引用来调用，因此也没有构成多态，如此一来，如果需要通过对象来调用从基类中继承过来的vir1函数，同样是需要域解析操作符。派生类中的vir2函数和基类中vir2函数构成遮蔽，因此通过对象和成员选择符调用的仍是派生类中新增的vir2函数，如果想调用基类中的vir2函数，则需要通过域解析操作符。例8程序运行结果如下:

```C++
derived vir1
base vir2
derived vir1
derived vir2
base vir1
base vir2
```

​		以上总结了函数名相同的所有情况，函数名相同利用的好可以为程序设计带来较大的便利，使用的不好则容易误导程序设计人员。一般来讲，函数名相同通常会用在以下几种情况中：



- 顶层函数的函数重载。对于程序设计人员而言，实现功能相同但所处理数据类型不同的函数时，采用函数重载的方式将会带来极大的方便。例如设计一个求绝对值函数，针对整型和double类型各设及一个abs函数，调用时而无需关注参数类型，这样的设计是很方便的。

- 类中的成员函数的重载，这种函数重载和顶层函数重载同样能给我们的程序带来方便。

- 类中的构造函数重载，设计多个构造函数，用于不同的初始化对象方式。

- 在继承层次中为了使用多态特性而采用相同函数签名。

除此之外函数名相同还会导致继承层次中的函数遮蔽，而函数遮蔽这一特性通常会使得程序难以理解，因此建议谨慎使用函数遮蔽机制。





## 抽象类和抽象成员函数

​		公共接口是指一系列成员函数的集合，支持该接口的类必须以合适的方式重新定义这些成员函数，否则就无法创建对象。在C++中，可以通过抽象基类来实现公共接口。介绍抽象基类之前，我们需要先来了解一下纯虚成员函数。

### 纯虚函数(必须是成员函数)

#### 纯虚成员函数的声明语法	

```C++
virtual 函数返回类型 函数名 (函数参数) = 0;
```

#### 纯虚函数的特点 

​		纯虚成员函数没有函数体，只有函数声明，在纯虚函数声明结尾加上“= 0”表明此函数为纯虚成员函数。包含纯虚成员函数的类即为抽象基类，之所以说它抽象，那是因为它无法实例化，也即无法用于创建对象。

```C++
class Abstract{
public:
    virtual void func() = 0;
};

int main(){
    Abstract a;		// 报错，提示Abstract类是一个抽象类，不能创建对象
    return 0;
}
```



### 抽象类

​		在一个类中只要有一个成员函数是纯虚函数，则该类即为抽象类(抽象基类)。

### 抽象类的特点

​		抽象类不能直接创建对象(不能实例化)，可以通过抽象基类来实现公共接口。只能通过子类继承，并在子类中实现抽象类中的抽象函数，子类才能实例化。

​		**纯虚成员函数可以被派生类继承，如果派生类不重新定义抽象基类中的所有（有多个则要重新定义多个）纯虚成员函数，则派生类同样会成为抽象基类，因而也不能用于创建对象。**

```C++
class Abstract{
public:
    virtual void func() = 0;
    virtual void func1() = 0;
};

class B : public Abstract{
public:
    virtual void func() override{
        
    }
};

int main(){
    // Abstract a;		// 报错，提示Abstract类是一个抽象类，不能创建对象
    B b;
    return 0;
}
```



## 补充

### C++中虚继承的作用及底层实现原理

​		虚继承和虚函数是完全无相关的两个概念。

​		虚继承是解决C++多重继承问题的一种手段，从不同途径继承来的同一基类，会在子类中存在多份拷贝。

#### 存在两个问题

​		其一，浪费存储空间；

​		第二，存在二义性问题，通常可以将派生类对象的地址赋值给基类对象，实现的具体方式是，将基类指针指向继承类（继承类有基类的拷贝）中的基类对象的地址，但是多重继承可能存在一个基类的多份拷贝，这就出现了二义性。

#### 虚继承可以解决多种继承前面提到的两个问题：

​		虚继承底层实现原理与编译器相关，一般通过虚基类指针和虚基类表实现，每个虚继承的子类都有一个虚基类指针（占用一个指针的存储空间，4字节）和虚基类表（不占用类对象的存储空间）（需要强调的是，虚基类依旧会在子类里面存在拷贝，只是仅仅最多存在一份而已，并不是不在子类里面了）；当虚继承的子类被当做父类继承时，虚基类指针也会被继承。

​		实际上，vbptr指的是虚基类表指针（virtual base table pointer），该指针指向了一个虚基类表（virtual table），虚表中记录了虚基类与本类的偏移地址；通过偏移地址，这样就找到了虚基类成员，而虚继承也不用像普通多继承那样维持着公共基类（虚基类）的两份同样的拷贝，节省了存储空间。

​		在这里我们可以对比虚函数的实现原理：他们有相似之处，都利用了虚指针（均占用类的存储空间）和虚表（均不占用类的存储空间）。

​		虚基类依旧存在继承类中，只占用存储空间；虚函数不占用存储空间。

​		虚基类表存储的是虚基类相对直接继承类的偏移；而虚函数表存储的是虚函数地址。

​    ![0](data:image/png;base64,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)

补充：

1、D继承了B,C也就继承了两个虚基类指针

2、虚基类表存储的是，虚基类相对直接继承类的偏移（D并非是虚基类的直接继承类，B,C才是）