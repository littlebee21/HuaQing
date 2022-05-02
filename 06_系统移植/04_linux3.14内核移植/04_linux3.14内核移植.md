# 一、内核初步编译

1. 解压源码 `tar xvf 压缩文件名`

2. 修改顶层Makefile的交叉编译器  200行

   1. ARCH ?= arm
   2. CROSS_COMPILE ?= arm-none-linux-gnueabi-

3. 导入exynos_defconfig配置 (生成顶层.config,创建 include/config空目录）

   ​	make exynos_defconfig   

   ​    备注：make savedefconfig可备份.config，用法

   ```shell
   make savedefconfig  #生成备份.config用的文件defconfig
   mv defconfig xxx_config #更名
   mv xxx_config arch/arm/configs #这些xxx_config一般保存在arch/arm/configs目录下
   ```

4. make menuconfig  （修改.config） 

   修改System Type --->

   ​     (3) S3C UART to use for low-levelmessages   为 (2) S3C UART to use for low-levelmessages

   返回时选择保存后退出menuconfig界面

   备注：如果make menuconfig出错，需要安装libncurses5-dev

   ```shell
   sudo apt-get instal libncurses5-dev
   ```

5. make uImage   （可以-j4进行多线程并行编译提高编译速度 数字4为CPU核数的2倍，不宜过大）

   ​	该步做了如下处理：

   1.  根据.config生成include/config/auto.conf
   2.  根据include/config/auto.conf生成include/generated/autoconf.h
   3.  在include/config、include/generated、arch/arm/include/generated三个目录下自动生成一些头文件
   4.  编译主机上用的一些工具
   5.  开始编译

   备注：如果出现 “mkimage command not find”错误，则做完如下处理后重新make uImage

   ```shell
   sudo  cp  ???/u-boot-2013.01/tools/mkimage  /sbin
   ```

6. make dtbs：

   1. cd  arch/arm/boot/dts/     
   2. cp ./exynos4412-origen.dts  ./exynos4412-fs4412.dts     
   3. vim Makefile 中cp69行，并改为exynos4412-fs4412.dtb   
   4. cd  ../../../../回内核源码顶层目录  
   5. make dtbs

7. 初步验证

   1. cp arch/arm/boot/uImage  /tftpboot

   2. cp arch/arm/boot/dts/exynos4412-fs4412.dtb /tftpboot

   3. 板子上电进入uboot命令行设置启动参数 

      ```shell
      uboot#setenv gatewayip 192.168.9.1
      uboot#setenv serverip 192.168.9.16
      uboot#setenv ipaddr 192.168.9.99
      uboot#setenv bootcmd tftp 41000000 uImage \; tftp 42000000 exynos4412-fs4412.dtb \; bootm 41000000 - 42000000
      
      uboot#setenv bootargs root=/dev/nfs nfsroot=192.168.9.16:/opt/fs4412_rootfs rw console=ttySAC2,115200  init=/linuxrc ip=192.168.9.99
      
      uboot# saveenv
      uboot# printenv
      ```



重新上电，自动启动，观察start kernel后能不能打印信息


# 二、网卡移植

## 2.1 make menuconfig配置

1. TCP/IP支持 

   Networking support  ---->   Networking options下

   <*>Packet socket

   <*>	Packet: sockets  monitoring interface

   <*>Unix domain sockets

   <*>TCP/IP networking

   <*>	IP: kernel level autoconfiguration

2. NFS支持

   File Systems  ------> Networking File Systems下 

   <*> NFS Client Support

   <*>		NFS client support for NFS version 2 

   <*>		NFS client support for NFS version 3

   <*>Root file system on NFS

3. DM9000网卡支持

   Device Drivers ------> Network device support  ------->  Ethernet driver support下

   <*> DM9000 support

# 三、设备树中添加网卡相关信息

## 3.1 修改设备树文件

arch/arm/boot/dts/exynos4412-fs4412.dts,在chosen节点后增加如下内容：

```
srom-cs1@5000000 {
	compatible = "simple-bus";
	#address-cells = <1>;
	#size-cells = <1>;
	reg = <0x5000000 0x1000000>;
	ranges;

	ethernet@5000000 {
		compatible = "davicom,dm9000";
		reg = <0x5000000 0x2 0x5000004 0x2>;
		interrupt-parent = <&gpx0>;
		interrupts = <6 4>;
		davicom,no-eeprom;
		mac-address = [00 0a 2d a6 55 a2];
	};
};
```

```
srom-cs1@5000000 {
	compatible = "simple-bus";#CPU系统内部总线
	#address-cells = <1>;
	#size-cells = <1>;
	reg = <0x5000000 0x1000000>; #srom控制器bank1连接了DM9000的内部存储  此处为bank1的起始地址 和 大小
	ranges;

	ethernet@5000000 {  #参照Documentation中的DM9000的设备树设置
		compatible = "davicom,dm9000";
		reg = <0x5000000 0x2 0x5000004 0x2>;
		interrupt-parent = <&gpx0>;
		interrupts = <6 4>;
		davicom,no-eeprom;
		mac-address = [00 0a 2d a6 55 a2];
	};
};
```



## 3.2 修改源码

修改文件 drivers/clk/clk.c 529行：

```
改  static bool clk_ignore_unused; 为static bool clk_ignore_unused = true;
```

# 四、uImage生成过程

源码编译生成----->elf格式的vmlinux---->objcopy生成Image--->解压代码+压缩后的Image组合生成zImage--->mkimge在zImage文件前加64字节的信息头生成uImage



# 五、交叉编译工具集合：

arm-linux-readelf (查看当前文件or库是由什么编译器所编译 )

arm-linux-ar 生成静态库.a文件  -c : 创建一个文档      -s : 在文档中添加索引      -r : 插入文件成员



arm-linux-strip (去掉其中的调试信息，执行文件大小or动态库将小的多)



arm-linux-objcopy 将ELF格式生成结果转化为二进制文件



arm-linux-ld 链接器

arm-linux-gcc 编译器

arm-linux-as 汇编器



arm-linux-addr2line: 根据指令地址得出代码位置       

```
 arm-linux-addr2line  -e   elf格式的可执行文件/或动态库文件   地址  
 nm ./可执行文件
```

​     

arm-linux-objdump （反汇编代码）	

```
arm-linux-objdump -s -d  可执行文件  > ???.s
```

