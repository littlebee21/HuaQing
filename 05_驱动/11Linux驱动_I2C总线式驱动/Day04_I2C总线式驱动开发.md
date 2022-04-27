

# 一、I2C总线背景知识

SOC芯片平台的外设分为：

1. 一级外设：外设控制器集成在SOC芯片内部
2. 二级外设：外设控制器由另一块芯片负责，通过一些通讯总线与SOC芯片相连

![00_SOC架构图](.\00_SOC架构图.jpg)



Inter-Integrated Circuit： 字面意思是用于“集成电路之间”的通信总线，简写：IIC(或者I2C)

![01_I2C概述](.\01_I2C概述.jpg)

![02_I2C连接](.\02_I2C连接.png)

![03_I2C时序](.\03_I2C时序.jpg)

![04_I2C协议01](.\04_I2C协议01.jpg)

![05_I2C协议02](.\05_I2C协议02.jpg)

i2c传输的要点就是： 传输一个字节 后面必然紧跟一个"响应"信号----应答信号.这个响应信号可能来自主机，或者是从机，具体是谁，就要看传输方向。
传输方向分两种情况(每种情况又有两种可能: A无应答和 B有应答)： 

1.主机->从机，主机对从机发一个字节之后，主机要读取从机的响应信号(主机读SDA线)

 	A) 主机读SDA为高电平，说明从机无应答（意味着从机接收完毕，主机发送停止信号）
 	 B) 主机读SDA为低电平，说明从机有应答。（可继续发送下一个字节）

2.从机->主机， 主机读取从机一个字节之后，主机要向从机发送一个响应信号(主机写SDA线)

​	 A) 主机写SDA为高电平，从机收到主机的无应答信号之后，从机停止传输，等待主机的停止信号。
​	 B) 主机写SDA为低电平，从机收到主机的应答信号之后，从机继续输出下一字节

# 二、Exynos4412 I2C收发实现之裸机版

I2CCON寄存器：控制寄存器

![I2CCON](.\I2CCON.jpg)

第7位：决定是否允许产生应答信号，无论发送还是接收前，需置1

第6位：传输时时钟线分频，一般选置1

第5位：决定是否开启发送或接收结束时发通知，无论发送还是接收前，需置1

第4位：接收或发送是否完毕可以通过检查此位是否为1，接收或发送完毕后需置0



I2CSTAT寄存器：状态寄存器

![I2CSTAT](.\I2CSTAT.jpg)

第6、7位：每次传输前需选择传输模式

第5位：置0产生将产生终止信号，传输前置1产生起始信号

第4位：使能数据输出，传输前需置1



I2CDS寄存器：数据寄存器，发送前被发送的数据存放处，接收后结果也从此处读取

## 2.1 发送

![06_write](.\06_write.png)

![07_发送流程](.\07_发送流程.jpg)

```c
void iic_write (unsigned char slave_addr, unsigned char addr, unsigned char data)
{
    //从设备寻址
	I2C5.I2CDS = slave_addr;
	I2C5.I2CCON = 1<<7 | 1<<6 | 1<<5;/*ENABLE ACK BIT, PRESCALER:512, ,ENABLE RX/TX */
	
    I2C5.I2CSTAT = 0x3 << 6 | 1<<5 | 1<<4;/*Master Trans mode ,START ,ENABLE RX/TX ,*/
	while(!(I2C5.I2CCON & (1<<4)));

	I2C5.I2CDS = addr;
	I2C5.I2CCON &= ~(1<<4);	//Clear pending bit to resume.
	while(!(I2C5.I2CCON & (1<<4)));

    //发送数据
	I2C5.I2CDS = data;	// Data
	I2C5.I2CCON &= ~(1<<4);	//Clear pending bit to resume.
	while(!(I2C5.I2CCON & (1<<4)));

	I2C5.I2CSTAT = 0xD0; //stop

	I2C5.I2CCON &= ~(1<<4);//Clear pending bit to resume.

	mydelay_ms(10);
}
```



## 2.2 接收

![09_read](.\09_read.png)

![10_接收流程](.\10_接收流程.jpg)

```c
void iic_read(unsigned char slave_addr, unsigned char addr, unsigned char *data)
{
    //从设备寻址
	I2C5.I2CDS = slave_addr;

	I2C5.I2CCON = 1<<7 | 1<<6 | 1<<5;/*ENABLE ACK BIT, PRESCALER:512, ENABLE RX/TX Interrupt-enable */
	I2C5.I2CSTAT = 0x3 << 6 | 1<<5 | 1<<4;/*Master Trans mode ,START ,ENABLE RX/TX ,*/
	while(!(I2C5.I2CCON & (1<<4))); /*对应位为1表示slave_addr传输完成，线路处于挂起状态*/

	I2C5.I2CDS = addr;
	I2C5.I2CCON &= ~(1<<4);	//Clear pending bit to resume. 继续传输
	while(!(I2C5.I2CCON & (1<<4)));
    
	
    I2C5.I2CSTAT = 0xD0; //stop  第5位写0，表示要求产生stop信号

	//接收数据
	I2C5.I2CDS = slave_addr | 0x01;	// Read
	I2C5.I2CCON = 1<<7 | 1<<6 | 1<<5;/*ENABLE ACK BIT, PRESCALER:512, ENABLE RX/TX Interrupt-enable */

	I2C5.I2CSTAT = 2<<6 | 1<<5 | 1<<4;/*Master receive mode ,START ,ENABLE RX/TX , 0xB0*/
	while(!(I2C5.I2CCON & (1<<4)));

	I2C5.I2CCON &= ~((1<<7) | (1<<4));/* Resume the operation  & no ack*/
	while(!(I2C5.I2CCON & (1<<4)));

	I2C5.I2CSTAT = 0x90; //stop  第5位写0，表示要求产生stop信号
	I2C5.I2CCON &= ~(1<<4);		/*clean interrupt pending bit  */

	*data = I2C5.I2CDS;
	mydelay_ms(10);
}
```

# 三、Linux内核对I2C总线的支持

![LinuxI2C框架图](.\LinuxI2C框架图.png)



**I2C设备驱动：**即挂接在I2C总线上的二级外设的驱动，也称客户（client）驱动，实现对二级外设的各种操作，二级外设的几乎所有操作全部依赖于对其自身内部寄存器的读写，对这些二级外设寄存器的读写又依赖于I2C总线的发送和接收

**I2C总线驱动：**即对I2C总线自身控制器的驱动，一般SOC芯片都会提供多个I2C总线控制器，每个I2C总线控制器提供一组I2C总线（SDA一根+SCL一根），每一组被称为一个I2C通道，Linux内核里将I2C总线控制器叫做适配器（adapter），适配器驱动主要工作就是提供通过本组I2C总线与二级外设进行数据传输的接口，每个二级外设驱动里必须能够获得其对应的adapter对象才能实现数据传输

**I2C核心：**承上启下，为I2C设备驱动和I2C总线驱动开发提供接口，为I2C设备驱动层提供管理多个i2c_driver、i2c_client对象的数据结构，为I2C总线驱动层提供多个i2c_algorithm、i2c_adapter对象的数据结构

四大核心对象之间的关系图

![i2c四大核心对象之间的关联](.\i2c四大核心对象之间的关联.jpg)



i2c二级外设驱动开发涉及到核心结构体及其相关接口函数：

```c
struct i2c_board_info {
    char        type[I2C_NAME_SIZE];
    unsigned short  flags;
    unsigned short  addr;
    void        *platform_data;
    struct dev_archdata *archdata;
    struct device_node *of_node;
    int     irq;
};
/*用来协助创建i2c_client对象
重要成员
type：用来初始化i2c_client结构中的name成员
flags：用来初始化i2c_client结构中的flags成员
addr：用来初始化i2c_client结构中的addr成员
platform_data：用来初始化i2c_client结构中的.dev.platform_data成员
archdata：用来初始化i2c_client结构中的.dev.archdata成员
irq:用来初始化i2c_client结构中的irq成员

关键就是记住该结构和i2c_client结构成员的对应关系。在i2c子系统不直接创建i2c_client结构，只是提供struct i2c_board_info结构信息，让子系统动态创建，并且注册。
*/
```

```c
struct i2c_client {
    unsigned short flags;
    unsigned short addr;
    char name[I2C_NAME_SIZE];
    struct i2c_adapter *adapter;
    struct i2c_driver *driver;
    struct device dev;
    int irq;
    struct list_head detected;
};
/*重要成员：
flags:地址长度，如是10位还是7位地址，默认是7位地址。如果是10位地址器件，则设置为I2C_CLIENT_TEN
addr：具体I2C器件如(at24c02)，设备地址,低7位
name:设备名，用于和i2c_driver层匹配使用的，可以和平台模型中的平台设备层platform_driver中的name作用是一样的。
adapter:本设备所绑定的适配器结构(CPU有很多I2C适配器，类似单片机有串口1、串口2等等，在linux中每个适配器都用一个结构描述)
driver：指向匹配的i2c_driver结构，不需要自己填充，匹配上后内核会完成这个赋值操作
dev:内嵌的设备模型，可以使用其中的platform_data成员传递给任何数据给i2c_driver使用。
irq：设备需要使用到中断时，把中断编号传递给i2c_driver进行注册中断，如果没有就不需要填充。(有的I2C器件有中断引脚编号，与CPU相连)
*/

/* 获得/释放 i2c_adapter 路径：i2c-core.c linux-3.5\drivers\i2c */
/*功能：通过i2c总线编号获得内核中的i2c_adapter结构地址，然后用户可以使用这个结构地址就可以给i2c_client结构使用，从而实现i2c_client进行总线绑定，从而增加适配器引用计数。
返回值：
NULL：没有找到指定总线编号适配器结构
非NULL：指定nr的适配器结构内存地址*/
struct i2c_adapter *i2c_get_adapter(int nr);


/*减少引用计数：当使用·i2c_get_adapter·后，需要使用该函数减少引用计数。（如果你的适配器驱动不需要卸载，可以不使用）*/
void i2c_put_adapter(struct i2c_adapter *adap);

/*
功能：根据参数adap，info，addr，addr_list动态创建i2c_client并且进行注册
参数：
adap：i2c_client所依附的适配器结构地址
info：i2c_client基本信息
addt_list: i2c_client的地址(地址定义形式是固定的，一般是定义一个数组，数组必须以I2C_CLIENT_END结束，示例：unsigned short ft5x0x_i2c[]={0x38,I2C_CLIENT_END};
probe:回调函数指针，当创建好i2c_client后，会调用该函数，一般没有什么特殊需求传递NULL。
返回值：
非NULL:创建成功，返回创建好的i2c_client结构地址
NULL：创建失败
*/
struct i2c_client * i2c_new_probed_device
(
 struct i2c_adapter *adap,
 struct i2c_board_info *info,
 unsigned short const *addr_list,
 int (*probe)(struct i2c_adapter *, unsigned short addr)
);
/*示例：
struct i2c_adapter *ad;
struct i2c_board_info info={""};

unsigned short addr_list[]={0x38,0x39,I2C_CLIENT_END};

//假设设备挂在i2c-2总线上
ad=i2c_get_adapter(2);

//自己填充board_info 
strcpy(inf.type,"xxxxx");
info.flags=0;
//动态创建i2c_client并且注册
i2c_new_probed_device(ad,&info,addr_list,NULL);

i2c_put_adapter(ad);
*/

/*注销*/
void i2c_unregister_device(struct i2c_client *pclt)


 struct i2c_client * i2c_new_device
 (
     struct i2c_adapter *padap,
     struct i2c_board_info const *pinfo
 );
/*示例：
struct i2c_adapter *ad;
struct i2c_board_info info={
	I2C_BOARD_INFO(name,二级外设地址)
};
//假设设备挂在i2c-2总线上
ad=i2c_get_adapter(2);

//动态创建i2c_client并且注册
i2c_new_device(ad,&info);

i2c_put_adapter(ad);
*/
```

```c
struct i2c_driver {
    unsigned int class;

    /* Standard driver model interfaces */
    int (*probe)(struct i2c_client *, const struct i2c_device_id *);
    int (*remove)(struct i2c_client *);

    /* driver model interfaces that don't relate to enumeration  */
    void (*shutdown)(struct i2c_client *);
    int (*suspend)(struct i2c_client *, pm_message_t mesg);
    int (*resume)(struct i2c_client *);
	void (*alert)(struct i2c_client *, unsigned int data);

    /* a ioctl like command that can be used to perform specific functions
     * with the device.
     */
    int (*command)(struct i2c_client *client, unsigned int cmd, void *arg);

    struct device_driver driver;
    const struct i2c_device_id *id_table;

    /* Device detection callback for automatic device creation */
    int (*detect)(struct i2c_client *, struct i2c_board_info *);
    const unsigned short *address_list;
    struct list_head clients;
};
/*重要成员：
probe：在i2c_client与i2c_driver匹配后执行该函数
remove：在取消i2c_client与i2c_driver匹配绑定后后执行该函数
driver：这个成员类型在平台设备驱动层中也有，而且使用其中的name成员来实现平台设备匹配，但是i2c子系统中不使用其中的name进行匹配，这也是i2c设备驱动模型和平台设备模型匹配方法的一点区别
id_table:用来实现i2c_client与i2c_driver匹配绑定，当i2c_client中的name成员和i2c_driver中id_table中name成员相同的时候，就匹配上了。

补充：i2c_client与i2c_driver匹配问题
- i2c_client中的name成员和i2c_driver中id_table中name成员相同的时候
- i2c_client指定的信息在物理上真实存放对应的硬件，并且工作是正常的才会绑定上，并执行其中的probe接口函数这第二点要求和平台模型匹配有区别，平台模型不要求设备层指定信息在物理上真实存在就能匹配
*/

/*功能：向内核注册一个i2c_driver对象
返回值：0成功，负数 失败*/
#define i2c_add_driver(driver)     i2c_register_driver(THIS_MODULE, driver)
int i2c_register_driver(struct module *owner, struct i2c_driver *driver);

/*功能：从内核注销一个i2c_driver对象
返回值：无 */
void i2c_del_driver(struct i2c_driver *driver);
```

```c
struct i2c_msg {
    __u16 addr; /* slave address            */
    __u16 flags;
#define I2C_M_TEN       0x0010  /* this is a ten bit chip address */
#define I2C_M_RD        0x0001  /* read data, from slave to master */
    __u16 len;      /* msg length               */
    __u8 *buf;      /* pointer to msg data          */
};
/* 重要成员：
addr:要读写的二级外设地址
flags：表示地址的长度，读写功能。如果是10位地址必须设置I2C_M_TEN，如果是读操作必须设置有I2C_M_RD······，可以使用或运算合成。
buf：要读写的数据指针。写操作：数据源 读操作：指定存放数据的缓存区
len：读写数据的数据长度
*/

/*i2c收发一体化函数,收还是发由参数msgs的成员flags决定*/
int i2c_transfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
/*
功能：根据msgs进行手法控制
参数：
adap：使用哪一个适配器发送信息，一般是取i2c_client结构中的adapter指针作为参数
msgs：具体发送消息指针，一般情况下是一个数组
num:表示前一个参数msgs数组有多少个消息要发送的
返回值：
负数：失败
> 0 表示成功发送i2c_msg数量
*/

/*I2C读取数据函数*/
int i2c_master_recv(const struct i2c_client *client, char *buf, int count)
/*功能：实现标准的I2C读时序，数据可以是N个数据，这个函数调用时候默认已经包含发送从机地址+读方向这一环节了
参数：
client：设备结构
buf：读取数据存放缓冲区
count：读取数据大小 不大于64k
返回值：
失败：负数
成功：成功读取的字节数
*/
    
/*I2C发送数据函数*/
int i2c_master_send(const struct i2c_client *client, const char *buf, int count)
/*功能：实现标准的I2C写时序，数据可以是N个数据，这个函数调用时候默认已经包含发送从机地址+写方向这一环节了
参数：
client：设备结构地址
buf：发送数据存放缓冲区
count：发送数据大小 不大于64k
返回值：
失败：负数
成功：成功发送的字节数
*/

```

# 四、MPU6050

三轴角速度+三轴加速度+温度传感器

![MPU6050原理图](.\MPU6050原理图.jpg)



```c
#define SMPLRT_DIV  0x19 //陀螺仪采样率，典型值：0x07(125Hz)
#define CONFIG   0x1A //低通滤波频率，典型值：0x06(5Hz)
#define GYRO_CONFIG  0x1B //陀螺仪自检及测量范围，典型值：0xF8(不自检，+/-2000deg/s)
#define ACCEL_CONFIG 0x1C //加速计自检、测量范围，典型值：0x19(不自检，+/-G)
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H  0x41
#define TEMP_OUT_L  0x42
#define GYRO_XOUT_H  0x43
#define GYRO_XOUT_L  0x44
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48
#define PWR_MGMT_1  0x6B //电源管理，典型值：0x00(正常启用)
```

# 五、应用层直接使用I2C通道

## 5.1 预备工作：

### 5.1.1 exynos4412平台每个i2c通道的信息是通过设备树提供的，因此需要首先在exynos4412-fs4412.dts中增加5通道的节点：

![i2c通道5设备树节点](.\i2c通道5设备树节点.jpg)

不要忘记：

1. 回内核源码顶层目录执行：make  dtbs
2. 将新生成的dtb拷贝到/tftpboot

### 5.1.2 i2c总线驱动层提供了一个字符设备驱动，以便于应用层可以直接通过它去使用i2c总线通讯去操作二级外设，但需要

内核编译时添加此字符设备驱动代码(i2c-dev.c),因此需要修改make menuconfig的配置：

![menuconfig之i2c-dev支持](.\menuconfig之i2c-dev支持.jpg)

不要忘记：

1. 回内核源码顶层目录执行：make  uImage
2. 将新生成的uImage拷贝到/tftpboot

### 5.2 应用层直接使用i2c总线的代码实现

5.2.1 调用read、write实现接收、发送

见实例代码

5.2.2 调用ioctl实现接收、发送

见实例代码

缺点：

1. 需要应用程序开发人员查阅原理图和芯片手册，增加了他们的开发负担
2. 开发出的应用程序缺乏可移植性

# 六、I2C总线二级外设驱动开发方法

1. 查阅原理图以便得知二级外设挂在哪条I2C总线上、二级外设的身份标识（二级外设自身的地址）

2. 参照platform样式搭建二级外设驱动框架

3. 查询二级外设芯片手册以便得知驱动需要用到的寄存器地址

   注意：

   1. 此处寄存器是指二级外设内部的寄存器，每个寄存器在芯片手册里有个对应编号（也被称为地址），但不是内存地址，特别提醒此寄存器不是SOC芯片内部参与内存统一编址的寄存器，更不是ARM核-CPU的寄存器
   2.  通过调用i2c_tranfer函数完成与相应寄存器的数据交互

4. 参照字符驱动完成其余代码编写

5. 创建对应的i2c_client对象

   linux-3.14\Documentation\i2c\instantiating-devices
   
   匹配方式：
   
   1. 名称匹配
   
   2. 设备树匹配
   
   3. ACPI匹配
   
      Advanced Configuration and Power Management Interface 高级配置和电源管理接口 
   
      PC机平台采用的一种硬件配置接口



i2c二级外设驱动框架：

```c
//其它struct file_operations函数实现原理同硬编驱动

static int mpu6050_probe(struct i2c_client *pclt,const struct i2c_device_id *pid)
{
    //做硬编驱动模块入口函数的活
}

static int mpu6050_remove(struct i2c_client *pclt)
{
    //做硬编驱动模块出口函数的活
}

/*名称匹配时定义struct i2c_device_id数组*/
static struct i2c_device_id mpu6050_ids = 
{
    {"mpu6050",0},
    //.....
    {}
};

/*设备树匹配时定义struct of_device_id数组*/
static struct of_device_id mpu6050_dts =
{
    {.compatible = "invensense,mpu6050"},
    //....
    {}
};

/*通过定义struct i2c_driver类型的全局变量来创建i2c_driver对象，同时对其主要成员进行初始化*/
struct i2c_driver mpu6050_driver = 
{
	.driver = {
        .name = "mpu6050",
        .owner = THIS_MODULE,
        .of_match_table = mpu6050_dts,
    },
    .probe = mpu6050_probe,
    .remove = mpu6050_remove,
    .id_table = mpu6050_ids,
};

/*以下其实是个宏，展开后相当于实现了模块入口函数和模块出口函数*/
module_i2c_driver(mpu6050_driver);

MODULE_LICENSE("GPL");
```



# 七、I2C总线二级外设驱动开发之名称匹配

这种匹配方式需要自己创建i2c_client对象

创建i2c_client对象有三种方式：

1. i2c_register_board_info

   ```
   1.当开发板上电内核跑起来的时候，肯定是架构相关的程序首先运行，也就是mach-xxx.c
   2. mach-xxx.c文件里首先会定义i2c_board_info的结构体数组，在mach-xxx.c的初始化函数里调用
   i2c_register_board_info函数把i2c_board_inifo链接进内核的i2c_board_list链表当中去
   3.在驱动i2c目录下和开发板板对应的驱动文件i2c-xxx.c里，创建i2c_adapter对象
   4.这种方式严重依赖平台，缺乏灵活性，基本会被遗弃
   ```

   

2. i2c_new_device：明确二级外设地址的情况下可用

   i2c二级外设client框架：

   ```c
   #include <linux/kernel.h>
   #include <linux/module.h>
   #include <linux/i2c.h>
   
   static struct i2c_board_info mpu6050_info = 
   {
   	I2C_BOARD_INFO("mpu6050",二级外设地址)   
   };
   
   static struct i2c_client *mpu6050_client;
   static int __init mpu6050_dev_init(void)
   {
       struct i2c_adapter *padp = NULL;
       padp = i2c_get_adapter(i2c通道编号);
       mpu6050_client = i2c_new_device(padp,&mpu6050_info);
       i2c_put_adapter(padp);
       return 0;
   }
   module_init(mpu6050_dev_init);
   
   static void __exit mpu6050_dev_exit(void)
   {
       i2c_unregister_device(mpu6050_client);
   }
   module_exit(mpu6050_dev_exit);
   MODULE_LICENSE("GPL");
   ```

   

3. i2c_new_probed_device

   i2c二级外设client框架：不明确二级外设地址，但是知道是可能几个值之一的情况下可用

   ```c
   #include <linux/kernel.h>
   #include <linux/module.h>
   #include <linux/i2c.h>
   
   static const unsigned short addr_list[] = 
   {
   	0x68,
       //.....
       I2C_CLIENT_END
   };
   
   static struct i2c_client *mpu6050_client;
   static int __init mpu6050_dev_init(void)
   {
       struct i2c_adapter *padp = NULL;
       struct i2c_board_info mpu6050_info = {""};
       
       strcpy(mpu6050_info.type,"mpu6050");
       
       padp = i2c_get_adapter(i2c通道编号);
       mpu6050_client = i2c_new_probed_device(padp,&mpu6050_info,addr_list,NULL);
       i2c_put_adapter(padp);
       if(mpu6050_client != NULL)
       {
           return 0;
       }
       else
       {
       	return -ENODEV;
       }
   }
   module_init(mpu6050_dev_init);
   
   static void __exit mpu6050_dev_exit(void)
   {
       i2c_unregister_device(mpu6050_client);
   }
   module_exit(mpu6050_dev_exit);
   MODULE_LICENSE("GPL");
   ```

   



# 八、I2C总线二级外设驱动开发之设备树匹配

![mpu6050设备树节点](.\mpu6050设备树节点.jpg)

