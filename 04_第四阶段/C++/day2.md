# C++中的类



## 一  回忆C语言中的结构体

```C
struct Student{
    short x;
    char d;
    int a;
    char c;
    ...
}stu1;

struct Student stu;
stu.a = 100;
```



### C语言结构体的特点：

声明对象要加struct

空结构体大小为0

不能在结构体内初始化成员

结构体内成员都是可访问的

结构体内成员不能是函数

```C
enum{
	Admin,
    User
};
```



### C++结构体的特点

```C++
struct Student{
    short x;
    char d;
    int a = 20;
    char c;
};
```

声明对象时不需要加struct（Student stu;）

空结构体大小为1

能在结构体内初始化成员

C++结构体内的成员有访问权限(稍后详解)

结构体内成员可以是变量，也可以是函数





### C++中类和结构体的区别

```C++
struct A{
    
};
```

#### C++中的结构体和类中的成员都有三种访问权限：

public：公有权限

​		特点：在任何地方都能访问

protected：受保护访问权限

​		特点：子类对象(后面细说)

private：私有权限

​		特点：只有自身能访问，其他地方都不能访问(友元除外)



C++中结构体和类的继承权限：(三种)

public：			公有继承

protected：	 保护继承

private：		  私有继承



C++中的类和结构体的访问和继承权限有所不同：

##### 访问权限：

1. class中的默认的访问权限为private

2. struct中默认的访问权限为public

##### 继承权限：

1. class中默认的继承权限为private
2. struct中默认的继承权限为public



C++中的类有模板，结构体没有模板



- 再来分析C++中的结构体与类的区别：

- **先来说说C++中两者的相同之处**： 结构体中也可以包含函数；也可以定义public、private、protected数据成员；定义了结构体之后，可以用结构体名来创建对象。也就是说在C++当中，结构体中可以有成员变量，可以有成员函数，可以从别的类继承，也可以被别的类继承，可以有虚函数。

- **再来说说两者的区别**：对于成员访问权限以及继承方式，class中默认的是private，而struct中则是public。class还可以用于表示模板类型，struct则不行。

- 总的一句话：class和struct的语法基本相同，从声明到使用，都很相似，但是struct的约束要比class多，理论上，struct能做到的class都能做到，但class能做到的struct却不一定做的到。



注意：

​		类的成员函数如果在类内声明并实现，则该函数默认为内联函数，无论有没有inline关键字



一般没有特殊要求，将变量默认设置为私有的，函数设置为公有的



一、C++类的定义

C++中使用关键字 class 来定义类, 其基本形式如下:

```C++
class 类名{
public:
  //行为或属性 
protected:
  //行为或属性
private:
  //行为或属性
};
```

只有在派生类中才可以通过派生类对象访问基类的protected成员。



### 示例:

- 定义一个点(Point)类, 具有以下属性和方法:

- 属性: x坐标, y坐标
- 方法: 
  - 1.设置x, y的坐标值; 
  - 2.输出坐标的信息。

```C++
class Point{
private:
    float m_fxPos = 10.3;
    float m_fyPos = 15.5;
public:
    float getxPosValue();
    float getyPosValue();
    
    void setxPosValue(float x);
    void setyPosValue(float y);
};

// 分离编译
float Point::getxPosValue(){
    return m_fxPos;
}

float Point::getyPosValue(){
    return m_fyPos;
}
    
void Point::setxPosValue(float x){
    m_fxPos = x;
}

void Point::setyPosValue(float y){
    m_fyPos = y;
}   

int main(){
    Point *p = new Point;
    if(!p)	// 在这里可以不用这一步，因为new失败，编译器回产生一个bad_alloc
        return 0;
    cout << "xpos = " << p->getxPosValue() << endl;
    cout << "ypos = " << p->getyPosValue() << endl;
    p->setxPosValue(20.5);
    p->setyPosValue(30.6);
    cout << "xpos = " << p->getxPosValue() << endl;
    cout << "ypos = " << p->getyPosValue() << endl;
    
    delete p;
    p = nullptr;
    
    return 0;
}
```





开闭原则：



## 类的定义

几个重要名词：

(1) 类名

- 遵循一般的命名规则;字母，数字和下划线组合，不要以数字开头。

- - 约定: 一般类名以大写字母开头

(2) 类成员

- 类可以没有成员，也可以定义多个成员。成员可以是数据、函数或类型别名。所有的成员都必须在类的内部声明。

没有成员的类是空类，空类也占用空间(1byte)。

```C++
class People{
};
sizeof(People) = 1;  
```



(3) 成员函数

- 成员函数必须在类内部声明，可以在类内部定义，也可以在类外部定义。如果在类内部定义，就默认是内联函数。

(4) 构造函数

- 构造函数是一个特殊的、与类同名的成员函数，该函数没有返回值，用于给每个数据成员设置适当的初始值。

(5) 析构函数

- 析构函数是一个特殊的、与构造函数名类似的成员函数，需要在构造函数之前添加一个"~", 该函数没有返回值，用于释放该类的资源.



## 构造函数

类中最重要的成员函数：

​	构造函数(constructor)

​	特点:

​			构造函数是一个特殊的、与类同名的成员函数，该函数没有返回值。

​	作用：

​			用于给每个数据成员设置适当的初始值。



### 成员变量初始化的方式

1. 在类内声明时直接初始化(C++11中新增的)
2. 在类的构造函数中初始化(赋值)
3. 构造函数的参数列表初始化

![image-20220224160500869](https://gitee.com/ciyeer/picgo-image/raw/master/202202241605219.png)



### 成员变量初始化的顺序

​		是由变量声明的顺序决定的，在参数列表中的顺序不能决定成员变量初始化顺序

<img src="https://gitee.com/ciyeer/picgo-image/raw/master/202202241614727.png" alt="image-20220224161424515" style="zoom:50%;" />



一个空类：

```C++
class A{
public:
    A(){}
    // A(){}
    // 构造函数
    // 拷贝构造函数
    // 赋值函数
    // 析构函数
};
```

一个类中如果没有写构造函数，则编译器会为该类添加一个默认的不带参数的构造函数。

如果该类有一个构造函数，则编译器不再会为该类添加构造函数。



### 函数重载：

​	C++中支持函数重载，C语言不支持函数重载

1. 在相同作用域内

2. 函数名相同

3. 函数签名不同

   ​	函数签名：函数参数的类型或者个数



### 重载构造函数

