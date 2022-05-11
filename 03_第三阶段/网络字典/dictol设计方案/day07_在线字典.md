# 一、需求分析

核心功能：客户端给服务器发送一个单词，然后服务器回给客户端该单词的英文释义

附加功能：

1. 注册用户

 	2. 登录用户
 	3. 查阅用户对应的搜词历史



原始材料：dict.txt 

# 二、设计

## 2.1 基本框架图

![在线词典架构图](.\在线词典架构图.png)



## 2.2 通信协议数据组织

用变长结构体来组织通过TCP传输的数据

```
struct DictOLPDU
{
	int len;
	int type;//1 reg-req 2. reg-rsp 3. login-req 4. login-rsp 5. searchword-req 6. searchword-rsp 7. history-req 8. history-rsp 
	char data[1];
};
```

type --- 1: 20字节用户名+20字节密码

type ----2 ：4字节的整数（0为OK，其它数字表示错误）

type ----3：20字节用户名+20字节密码

type ---- 4：4字节的整数（0为OK，其它数字表示错误）

type ----5：存放被搜单词（字符串）

type ----6：存放释义（字符串）

type ---- 7：不用data

type ---- 8：方案1----分开发送，每条历史记录发送一次，每次pdu的data部分组织为：前20字节为用户名，然后的24字节的时间字符串，最后是不定长的单词(历史记录分开发送)，最后发送一条空记录表示全部发送完毕，空记录的data 第一个字符如果为'\0'（历史记录的结束）

​                    方案2-----所有结果组织在一起，统一发送，data部分为'\0'结尾的字符串，该字符串中用'#'分隔单词和时间，用‘@’分隔不同历史记录



## 2.3 dictolpublic:在线词典公共模块

本模块编译成动态库文件：libdictolpublic.so

主要给客户端和服务器提供：

	1. 双方通信协议数据组织相关的函数
	2. 发送接收协议数据的函数
	3. 通信双方都可能用到的其它设施：如，一些配置宏、调式宏、一些简易封装函数

模块源码文件组成：

1. dictolprotocol.c：各种PDU数据组织函数，SendPDU、RecvPDU函数，DestroyDictOLPDU函数

 	2. dictolpublic.c：对read、write的二次封装函数，对fgets的二次封装函数
 	3. 对外头文件：
      	1. dictoldebug.h ：各模块调试用宏
      	2. dictolprotocol.h：PDU变长结构体设计，dictolprotocol.c对外函数声明
      	3. dictolpublic.h：包含上面两个头文件，dictolpublic.c对外函数声明

## 2.4 dictolclient:

本模块编译成可执行文件：dictolclient

作为在线词典网络服务的使用方，主要完成如下工作：

1. 接收用户在界面的输入，并完成对应的功能

 	2. 向服务器发送注册、登录、查词、查历史的网络服务请求
 	3. 接收服务器针对各种网络服务请求的回应，并做适当处理以告知用户操作结果

模块源码文件组成：

1. cmain.c：main  客户端Socket连接函数  主界面循环函数   功能界面循环函数

 	2. userregister.c：用户注册功能函数
 	3. userlogin.c：用户登录功能函数
 	4. queryword.c：查词功能函数
 	5. queryhistory.c：历史查询功能函数
 	6. view.c：界面相关函数
 	7. cprivate.h：客户端私有头文件，主要内容：客户端控制用结构体设计，各子模块间函数声明

## 2.5 dictolserver:

本模块编译成可执行文件：dictolserver

作为在线词典网络服务的提供方，主要完成如下工作：

1. 接收客户端注册、登录、查词、查历史等网络服务请求，并完成服务端相关的工作

 	2. 给客户端发送注册、登录、查词、查历史等网络服务请求的回应信息
 	3. 多进程并发支持
 	4. 用户数据的存储、查询、更改
 	5. 历史记录数据的存储、查询、更改
 	6. 单词释义的查询

模块源码文件组成：

1. main.c：main  创建服务端socket  支持多进程并发的主循环函数

 	2. handleclient.c：各子进程处理客户端socket数据的入口函数
 	3. wraprunsql.c：sqlite3_exec、sqlite3_get_table的二次封装解决读写锁忙的问题，打开数据库并建表函数
 	4. userhelper.c：数据库user表相关的操作函数
 	5. historyhelper.c：数据库history表相关的操作函数
 	6. sprivate.h：服务端私有头文件，主要为各子模块间提供函数声明
 	7. dict.txt：原始素材，用于查询指定单词释义
 	8. testdbhelper.c：不编译进dictolserver可执行文件，用于单独测试各数据库操作函数的正确性

# 三、编码

 ![dictol代码目录结构](.\dictol代码目录结构.jpg)                                      





# 四、函数库

函数库顾名思义就是包含着很多函数定义的仓库（这些函数定义已经被预处理、编译、汇编成了二进制指令形式）

每个函数库以专门格式的普通文件存在

使用函数库时需要库文件+配套头文件

使用函数库的好处：

1. 代码隐藏，使用者无需关心实现细节
2. 多个程序共用



C、C++源码编译后以三种形式存在

1. 目标文件(Linux下.o，windows下.obj) -------- 与对应.c文件一对一
2. 库文件：多个目标文件的集合
3. 可执行文件：梳理完函数依赖的可以当作一个完整程序运行的文件  



两种函数库：

1. 静态库（static libraries）：全称静态链接库或静态函数库

   Linux下还被称为函数归档库(Archive library)，因此文件名以.a为标识

   Windows下文件名以.lib为标识

2. 动态库（dynamically loaded libraries）：全称动态链接库或动态函数库

   Linux下还被称为共享目标库，因此文件名以.so为标识

   windows下还被称为动态加载库，因此文件名以.dll为标识



## 4.1 静态链接

### 4.1.1、Linux下静态链接库文件的生成

1. 先编译生成每个.c对应的.o文件 （-c选项）------------gcc   x.c -o x.o  -c
2. ar加crv选项将多个.o文件组合成静态库文件 --------- ar crv libxxx.a x1.o x2.o  .... xn.o

静态库文件实际上是对多个.o文件的简单打包

### 4.1.2、Linux下链接生成可执行文件时使用静态库文件

1. gcc的-L 选项指定静态库文件所在目录的路径
2. gcc的-l 选项指定静态库名（静态库文件名为libxxx.a.?.?时库名为xxx）
3. gcc加链接选项-static
4. 生成可执行文件时主要完成：
   1. 组合数据段：将自身代码中的 和 所有动态库文件中的 全局数据 组合成程序运行过程中的数据区
   2. 生成代码段：将程序中所有函数（自定义+函数库的函数）定义组成程序配套的唯一的代码区

### 4.1.3、程序运行过程中不在需要静态库文件

### 4.1.4、多个程序共用同一个静态库

每个程序只有一份大代码区，这个代码区中既包含自定义函数又包含库函数

## 4.2 动态链接

### 4.2.1、Linux下动态链接库文件的生成

1. 先编译生成每个.c对应的.o文件
2. gcc加-fPIC  -shared选项将多个.o文件组合成动态库文件

注：PIC：Position-Independent Code 位置无关代码

### 4.2.2、Linux下链接生成可执行文件时使用动态库文件

1. gcc的-L 选项指定动态库文件所在目录的路径
2. gcc的-l 选项指定动态库名（动态库文件名为libxxx.so.?.?时库名为xxx）
3. 生成可执行文件时主要完成：
   1. 组合数据段：将自身代码中的 和 所有动态库文件中的 全局数据 组合成程序运行过程中的数据区
   2. 生成代码段：仅将自定义函数组合到程序代码区
   3. 在所有依赖的动态库文件中查找非自定义函数，找到则记录该函数在库文件中的相对位置

### 4.2.3、程序运行过程中仍然需要依赖动态库文件

采用动态链接的程序运行需要(因此动态链接的程序执行效率低一些)：

1. 检查动态库文件是否在内存中已经存在，如果不存在需要找到动态库文件并加载进内存

2. 根据动态库文件所在空间的首地址计算本程序中用到的各库函数在内存中的地址，方便函数调用

   

Linux下为了方便程序运行时能找到动态库文件，需要做如下设置：

1. 向/etc/ld.so.conf文件中添加动态库文件所在目录的绝对路径 ------- sudo vim /etc/ld.so.conf
2. 执行ldconfig命令让更新后的ld.so.conf生效  ------- sudo ldconfig
3. 运行程序

### 4.2.4、多个程序共用同一个动态库

每个程序有多块代码区：

1. 自定义函数的代码区（程序自己的代码区）
2. 动态库1的代码区
3. 动态库2的代码区
4. ...........
5. 动态库n的代码区

多个程序共用同一个动态库时，使用同一个动态库的代码区，即每个动态库的代码区在内存中仅有一份（因此非常节省内存）



## 4.3 静态链接与动态链接的比较

1. 可执行文件的大小：静态链接大、动态链接小

2. 多个运行的程序共用同一个函数库时的空间消耗：静态链接大、动态链接小

3. 程序运行时的效率：静态链接高、动态链接低

4. 变更库：静态链接麻烦、动态链接方便

   静态链接：需要重新链接生成可执行文件

   动态链接：头文件不变时不需重新生成可执行文件

   

# 五、Makefile

gcc 直接编译带来的问题：

1. 编译命令过长   ---- shell脚本也可以解决
2. 编译时间过长



Make工具

make命令用法：需要一个辅助文件（Makefile）协助来完成指定的制作过程

```shell
make      #默认用当前目录下Makefile或makefile的进行制作
make -f path_makefile_name  #使用指定目录下的指定名称的makefile文件进行制作
```

辅助文件Makefile的编写：

主体是一个或多个规则

规则的语法：

```
目标:依赖列表
<一个或多个水平制表符（table键）开头>命令1
<一个或多个水平制表符（table键）开头>命令2
......
<一个或多个水平制表符（table键）开头>命令n
```

1. 多道规则时，默认（make时不跟目标名）从第一道规则开始执行

2. 规则之间可以通过  一个规则的目标在另一个规则的依赖列表中  进行串联

3. 多道规则时，如果从指定的规则开始执行，可以用命令：make   目标名

4. 目标分为两种

   1. 真目标：实际需要生成同名文件的目标

   2. 伪目标：并不会生成指定文件，只是为了执行规则体里的命令

      clean   --- 用于清除生成的目标文件和中间文件

      all  ----- 用来作为第一规则，依赖为真正要制作的目标

5. 为了精简Makefile的内容，Makefile文件里支持变量定义，变量分为两种：

   1. 自定义变量

      定义语法：变量名 = 变量内容   变量定义语句确保同一行，要换行需要用续行符\

      引用语法：$(变量名)    所谓引用就是指出现$(变量名) 的地方会被对应的变量内容所替换

   2. 预定义变量

      $@: 当前规则的目标

      $^:当前规则的所有依赖

      $<：当前规则的第一个依赖

      %:所有同名的意思



生成可执行文件的通用模板：（头文件被修改了，需要make clean后再重新make）

```makefile
TARGET = ？？？？
CC = gcc

CFLAGS= -g -Wall 
INC =-I???/???1 -I???/???2 ....

LDFLAGS= -l???1 -l???2 ....
LIB = -L???/???1  -L???/???2 ....     


OBJS= ???/???1.o ???/???2.o .... ???/???n.o 

all:$(TARGET)

%.o:%.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIB)

clean:
	-rm ./$(OBJS) $(TARGET) -f

```

生成动态库文件的通用模板：

```makefile
TARGET = ？？？
INC=-I???/???1 -I???/???2 ....
LIB=-L???/???1  -L???/???2 .... 
CC = gcc
CFLAGS = -g -Wall
LDFLAGS= -l???1 -l???2 ....

OBJS= dictolpublic.o  dictolprotocol.o

all:lib$(TARGET).so

lib$(TARGET).so:$(OBJS)
	$(CC) -fPIC -shared -o lib$(TARGET).so $(OBJS) $(LIB) $(LDFLAGS)

%.o:%.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

install:lib$(TARGET).so	
	cp lib$(TARGET).so ../lib

clean:
	-rm $(OBJS) ./*.so *.o $(LIB)/lib$(TARGET).so -f
```



动态库参与应用程序编译

1. gcc的链接选项-L指定动态库文件所在的目录，用法：-L路径1   -L路径2 （一个-L选项后紧跟一个存放动态库文件的路径）
2. gcc的链接选项-l指定动态库名(libxyz.so动态库文件对应的动态库名为xyz)，用法：-lxyz  -l动态库名2 （一个-l选项后紧跟一个动态库名）



动态库参与应用程序运行前的准备：

1. sudo vim  /etc/ld.so.conf中新增一行添加动态库文件所在目录的绝对路径
2. 执行`sudo ldconfig`命令让更改后的ld.so.conf文件生效 
3. 运行应用程序



# 六、项目提示

提供三个头文件和dictolpublic.c

```c
//--------------wraprunsql.c------------------------

/*参照数据库笔记最后对sqlite3_exec进行二次封装*/
int my_sqlite3_exec(sqlite3 *pdb,const char *sqlstr,int (*callback)(void *,int,char **,char **),void *arg,char **errmsg);

/*参照数据库笔记最后对sqlite3_get_table进行二次封装*/
int my_sqlite3_get_table(sqlite3 *pdb,const char *sqlstr,char ***pret,int *prows,int *pcols,char **errmsg);

/*打开创建数据库操作引擎，判断user表是否存在，不存在则建user表，判断history表是否存在，不存在则建history表*/
sqlite3 *CreateSQLite3Engine(char *dbfile);
```

```c
//------------------------userhelper.c-------------------------
/*检查用户是否已存在，不存在则插入新记录
返回0：插入OK
   1：该用户已存在
   2：其它错误
*/
int InsertNewUser(sqlite3 *pdb,char *username,char *password);

/*返回0：找到用户并且密码正确并且flag为0，表示可登录，改flag为1
  1：用户没找到，不能登录成功
  2：flag不为0，重复登录
  3：密码错误，不能登录成功
  4：其它错误
*/    
int CheckLogin(sqlite3 *pdb,char *username,char *password);

/*变更user表中指定用户的标记
  如能登录成功则flag置1
  该用户客户端断开tcp连接则flag置0
*/
int UpdateUserFlag(sqlite3 *pdb,char *username,int flag);
    
```



```c
//------------------historyhelper.c-------------------------
static int CheckRecordIsExist(sqlite3 *pdb,char *username,char *word);

static int InsertNewHistoryRecord(sqlite3 *pdb,char *username,char *word);

static int UpdateHistoryRecordTime(sqlite3 *pdb,char *username,char *word);

int InsertOrUpdateHistoryRecord(sqlite3 *pdb,char *username,char *word);

/*将指定用户的历史记录组合成一个字符串，存放到动态分配的空间里，返回该空间（记住不用该空间应及时free）
  字符串组合方式：用‘#’分隔单词和时间，用‘@’分隔不同记录
*/
char *GetUserAllHistoryRecords(sqlite3 *pdb,char *username)
```



```c
//服务端剩余代码结构
//------main.c----------
/*
1. 创建服务端管理tcp连接用的socket
2. 创建sqlite操作引擎（调用CreateSQLite3Engine函数）
3. 进入主循环
*/
int main(int argc,char * argv[])
    
int CreateServerSocket(char *op,unsigned short port)
    
/*
	while(1)
	{
		? = accept(....);
		多进程或者多线程中调用HandleClient函数与对应客户端进行数据交互，
		多线程时注意如何将描述符和数据库引擎地址两个值传递给线程入口函数
	}
*/
int mainloop(int servfd,sqlite3 *pdb)


//-------handleclient.c---------
/*
	int isLogin;//1 表示已登录，0 表示未登录
	char curUserName[NAME_LEN];//登录成功后用来保存用户名
	while(1)
	{
		用select超时检测描述符中是否有数据发来，如5分钟内无数据发来则断开连接，进程或线程退出，如有数据发来则继续向下执行注册和登录处理
		
		接收pdu
		
		switch(pdu->type)
		{
			case 注册:
				调用HandleReg函数处理注册
				break:
			case 登录:
				调用HandleLogin函数处理登录
				HandleLogin返回0表示登录处理OK，置isLogin为1
				登录成功获取已登录的用户名保存到curUserName数组中
				break;
			default:
				销毁PDU后不做任何处理
				break;
		}		
	}
	通过isLogin判断是否已登录，如已登录则进入事务处理循环，如未登录则关闭TCP连接，本函数返回进程或线程退出
	while(1)
    {//查词或查历史记录的事务循环
    	接收PDU
    	switch(pdu->type)
    	{
    		case 查词:
    			调用HandleQueryWord处理查词请求
    			break;
    		case 查历史记录:
    			调用HandleQueryHistory处理查历史记录请求
    			break;
    		default:
    			销毁pdu后不做任何处理
    			break;
    	}
    }
*/
int HandleClient(int fd,sqlite3 *pdb);


/*以下四个函数对应四种事务处理
  返回0表示处理成功，
  返回 > 0表示处理虽然失败，但允许继续下一轮的事务处理
  返回 < 0表示因一些错误引起的失败，不能继续下一轮的事务处理
  提醒：接收到的pdu，由这些函数负责销毁
*/
int HandleReg(int fd,sqlite3 *pdb,struct DictOLPDU *recvpdu);    
int HandleLogin(int fd,sqlite3 *pdb,struct DictOLPDU *recvpdu);
int HandleQueryWord(int fd,sqlite3 *pdb,struct DictOLPDU *recvpdu,char *username);
int HandleQueryHistory(int fd,sqlite3 *pdb,struct DictOLPDU *recvpdu,char *username);

/*HandleQueryWord时调用，用来从文件中查询单词释义，并创建发送给客户端的回应pdu*/
static struct DictOLPDU *QueryWordFromFile(char *word);
  
```



```c
//最后的技术提示-------客户端代码框架
//------------------cprivate.h---------------
#include "dictolpublic.h"

//客户端总控用结构体
struct DictOLClientCTL
{
   int sockfd;
   char acClientUserName[NAME_LEN];//登录后本客户端的用户名,将作为消息发送者
};
//各.c文件给其它.c文件提供的函数声明
    

//--------------cmain.c----------------------
/*对struct DictOLClientCTL类型对象memset,置描述符成员为-1*/
static void InitClientCTL(struct DictOLClientCTL * pstClient);

/*关闭描述符成员*/
static void EndClientCTL(struct DictOLClientCTL * pstClient);

/*创建TCP socket并连接服务器，成功返回0*/
static int ConnectServer(struct DictOLClientCTL * pstClient,char *ip,int port);

/*主界面循环
int op;//用户选择的操作
int exitflag;//1 表示将退出循环，意味着客户端程序退出，0 表示不退出循环
while(1)
{
	op = DisplayMainUI();
	switch(op)
    {
    	case 1://注册处理
    		Do_UserRegister(pstClient);
    		break;
    	case 2://登录处理
    		ret = Do_UserLogin(pstClient);
    		if(0 == ret) //登录成功
    		{//进入事务界面循环
    			ret = FunctionUILoop();
    			if(ret < 0)
    			{//事务处理出错,应中止客户端继续执行
    				exitflag = 1;
    			}
    		}
    		else if(ret < 0)
    		{//因一些错误引起的登录失败，应中止客户端继续执行
    			exitflag = 1;
    		}
    	case 0:
    		exitflag = 1;//用户在主界面自己选择的程序退出
    		break;
    }
    if(exitflag)
    {
    	break;
    }
}//end while(1)
*/
static void MainUILoop(struct DictOLClientCTL *pstClient);

/*事务界面循环
int op;//用户选择的操作
int exitflag;//1 表示将退出循环，意味着客户端程序退出，0 表示不退出循环
while(1)
{
	op = DisplayFunctionUI();
	switch(op)
    {
    	case 1://查词处理
    		ret = Do_QueryWord(pstClient);
    		if(ret < 0)
    		{//因一些错误引起的处理失败，应中止事务循环
    			exitflag = 1;
    		}
    		break;
    	case 2://查史处理
    		ret = Do_QueryHistroy(pstClient);
    		if(ret < 0)
    		{//因一些错误引起的处理失败，应中止事务循环
    			exitflag = 1;
    		}
    	case 0:
    		exitflag = 1;//用户在本界面自己选择的程序退出
    		ret = -1;
    		break;
    }
    if(exitflag)
    {
    	break;
    }
}//end while(1)
*/
static int FunctionUILoop(struct DictOLClientCTL *pstClient);

/*
	struct DictOLClientCTL stClient;
	
	InitClientCTL(&stClient);
	
	ret = ConnectServer(&stClient,argv[1],port);
	if(0 == ret)
    {
    	MainUILoop(&stClient);
    }
    else
    {
    	PrintClientError("Can't into ClientMainLoop Function\n");
    }
	
	EndClientCTL(&stClient);

*/
int main(int argc,char *argv[])


//-----------------queryhistory.c------------------------------
int Do_QueryHistory(struct DictOLClientCTL * pstClient)

//-----------------queryword.c---------------------------------
int Do_QueryWord(struct DictOLClientCTL * pstClient)
    
//-----------------userlogin.c--------------------------------
int Do_UserLogin(struct DictOLClientCTL * pstClient)

//-----------------userregister.c------------------------------
int Do_UserRegister(struct DictOLClientCTL * pstClient)
    
//-----------------view.c----- 用户操作界面和程序结果输出的函数
int DisplayMainUI()
{
    int cmd = -1;
	char buf[8] = "";
    do
    {
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@1.Register    @@@@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@2.Login       @@@@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@0.Exit        @@@@@@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@Please Input Your Choice@@@@@@@@@@@\n");
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		MyGetString(buf,8);
        sscanf(buf,"%d",&cmd);
        if(cmd < 0 || cmd > 2)
        {
            printf("Your input is invalid,please redo it\n");
            continue;
        }
        else
        {
            break;
        }
    }while(1);

    return cmd;
}

/*类似于DisplayMainUI*/
int DisplayFunctionUI()
    
char *InputWord(char *pstr,int size)
{
    char *pret = NULL;

    printf("Please input a word:\n");

    pret = MyGetString(pstr,size);

    return pret;
}

/*类似于InputWord*/
char *InputUserName(char *pstr,int size)

/*类似于InputWord*/
char *InputPassword(char *pstr,int size)
    
/*其它调用printf完成结果输出的函数*/
```

