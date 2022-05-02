# 一、下载并解压u-boot源码

下载地址：[ftp://ftp.denx.de/pub/u-boot/](ftp://ftp.denx.de/pub/u-boot/)

拷贝u-boot-2013.01undo.tar.bz2到ubuntu指定目录下

解压uboot源码：

```sh
$ cd  ~/fs4412
$ tar xvf u-boot-2013.01undo.tar.bz2
```

# 二、修改顶层Makefile------指定交叉工具链

```sh
$ cd ./u-boot-2013.01
$ vim Makefile
```

复制Makefile 184~186三行  粘贴到186行下面，用‘#’注释掉184~186，并将新拷贝的三行修改为：

```makefile
ifeq(arm,$(ARCH))
CROSS_COMPILE ?= arm-none-linux-gnueabi-
endif
```

# 三、查看CPU支持

开发板CPU为exynos4412：**armv7**架构，**cortex-A9**系列，32bit，cpu4核心 1.4GHZ主频

查看arch/arm/cpu/armv7下是否有相应支持：arch/arm/cpu/armv7/exynos说明已支持



# 四、创建新开发板的支持目录及相关配置

找一个最类似的 board 配置修改, 这里我们参考的是 board/samsung/origen/

## 4.1 创建新开发板的支持目录

```sh
$ cp -rf board/samsung/origen board/samsung/fs4412
$ mv board/samsung/fs4412/origen.c board/samsung/fs4412/fs4412.c
$ vim board/samsung/fs4412/Makefile
修改 origen.o 为 fs4412.o
```

## 4.2 创建新开发板的配置头文件

```sh
在board目录下进行操作：
$ cp include/configs/origen.h include/configs/fs4412.h
$ vim include/configs/fs4412.h
修改104行
#define CONFIG_SYS_PROMPT "ORIGEN #"
为
#define CONFIG_SYS_PROMPT "fs4412 #"
修改133行
#define CONFIG_IDENT_STRING "for ORIGEN"
为
#define CONFIG_IDENT_STRING "for fs4412"
```

## 4.3 顶层目录boards.cfg里添加新开发板的支持

```sh
$ vim boards.cfg
参考284行
#Target ARCH CPU BoardName Vendor SOC 
origen arm armv7 origen samsung exynos
并在后面新增
fs4412 arm armv7 fs4412 samsung exynos
```

# 五、初步编译u-boot

```sh
$ make distclean
$ make fs4412_config #在include目录下生成下一步编译过程中用到的config.h和config.mk
$ make   #先生成u-boot然后objcopy产生u-boot.bin镜像文件
```

**备注：**

1. **编译完成后生成的 u-boot.bin 就是可执行的镜像文件**
2. **但是该文件还不能在我们板子上运行，因为三星exynos对bootloader有特殊的加密启动要求，需要对u-boot.bin进一步加工**



# 六、确认uboot已被执行

在 arch/arm/cpu/armv7/start.S 134 行后添加点灯代码

```assembly
#if 1
	ldr r0, =0x11000c40 @GPX2_7 led2
	ldr r1, [r0]
	bic r1, r1, #0xf0000000
	orr r1, r1, #0x10000000
	str r1, [r0]
	ldr r0, =0x11000c44
	mov r1,#0xff
	str r1, [r0]
#endif
```

参考资料：

1. led2电路图

   ![led2电路图](.\led2电路图.jpg)

2. GPX2_7资料

   ![GPX2_7控制寄存器](.\GPX2_7控制寄存器.jpg)

   ![GPX2_7数据寄存器](.\GPX2_7数据寄存器.jpg)

# 七、三星加密启动支持

exynos 需要三星提供的初始引导加密后，我们的 u-boot,才能被引导运行

## 7.1 将sdfuse_q目录拷贝到 u-boot-2013.01 源码目录下

注：sdfuse_q 三星提供的加密处理

```
cd ~/fs4412
unzip sdfuse_q.zip
cp sdfuse_q ./u-boot-2013.01/ -r
```



## 7.2 将 CodeSign4SecureBoot 目录拷贝到 u-boot-2013.01 源码目录下

注：CodeSign4SecureBoot 三星提供的安全启动方式

```
1. u-boot移植相关.zip文件导入到ubuntu
2. cd ~/fs4412
3. mkdir u-boot-porting-file
4. cp ????/u-boot移植相关.zip ./u-boot-porting-file
5. cd u-boot-porting-file
6. unzip u-boot移植相关.zip
7. cp CodeSign4SecureBoot  ~/fs4412/u-boot-2013.01/ -r
8. cp ./build.sh  ~/fs4412/u-boot-2013.01/
9. cd  ~/fs4412/u-boot-2013.01
10. chmod 777 build.sh
```



## 7.3 在顶层Makefile文件的445行下添加 ------ 可跳过

```makefile
		@#./mkuboot
		@split -b 14336 u-boot.bin bl2 此处 bl2 是字母’l’， 不是数字 1
		@+make -C sdfuse_q/
		@#cp u-boot.bin u-boot-4212.bin
		@#cp u-boot.bin u-boot-4412.bin
		@#./sdfuse_q/add_sign
		@./sdfuse_q/chksum
		@./sdfuse_q/add_padding
		@rm bl2a*
		@echo
		#注：命令前@表示只显示结果，不显示命令自身；命令前-表示出错不停止，忽略错误；命令前-表示使该命令行可以通过指定-n、-q或-t选项来执行
```

**注意：**

1. **是 tab  键缩进的，否则 makefile  编译报错**
2. 
3. 关键步骤作用：
   1. split -b 14336 u-boot.bin bl2 :将u-boot.bin分隔成14KBytes大小的多个小块文件，这些小块文件名称以bl2开头
   2. chksum程序将第一小块bl2aa文件制作为checksum_bl2_14k.bin ---- 其实就是将最后四字节改成前面（14K-4）个字节的和
   3. add_padding程序将u-boot.bin扩充成328KBytes，新扩充部分全部填0 ------ 意味着编译生成的u-boot.bin大小不能超过328KBytes



## 7.4 编译并生成最终的u-boot-fs4412.bin：

```sh
$  cd  ~/fs4412/u-boot-2013.01/
$  make
$  ./build.sh

#注意：注意如果执行了 make distclean  需重新执行如下步骤后再make和build：
#1. 重新拷贝目录CodeSign4SecureBoot到u-boot源码顶层目录
#2. make fs4412_config
```

**备注：**

1. **build.sh 脚本方式~~完成编译并~~自动完成对u-boot.bin添加三星加密方式 **，过程如下：
   1.  ~~先执行make fs4412_config ----- 完成针对fs4412开发板的配置~~
   2. ~~再多线程方式执行make ----- 生成checksum_bl2_14k.bin和328K大的u-boot.bin~~
   3. cat E4412_N.bl1.SCP2G.bin bl2.bin all00_padding.bin u-boot.bin tzsw_SMDK4412_SCP_2GB.bin > u-boot-fs4412.bin组合最终符合fs4412开发板的u-boot镜像文件
2. **编译生成所需文件 u-boot_fs4412.bin**



## 7.5 烧写新的 u-boot_fs4412.bin

复位，发现灯有点亮，说明我们的 u-boot 有运行到



## 7.6 exynos4412 启动过程

exynos4412启动流程：

![exynos4412启动流程](.\exynos4412启动流程.jpg)

说明：

1. iROM：exynos4412芯片内部集成，64K，物理起始地址0x0000 0000，出厂已固化了一段程序（BL0）
2. iRAM：exynos4412芯片内部集成，256K，物理起始地址0x0202 0000，可当内存用
3. BL1：存放于指定外存的固定位置，大小为15K，由BL0从外存中读到iRAM的0x0202 1400位置运行，完成BL2程序的加载运行，对应的bin文件由SAMSUNG提供
4. BL2：存放于指定外存的固定位置，大小为16K，由BL1从外存中读到iRAM的0x0202 5000位置运行，完成实际Bootloader的加载运行，对应的bin文件可自行制作或使用SAMSUNG提供的现成bin文件
5. 实际Bootloader即如uboot，存放于指定外存的固定位置，大小为328K，由BL2从外存中读到DRAM中运行，完成操作系统的加载运行，对应的bin文件自行制作
6. 最终开发板使用的bin文件组成：BL1+BL2+u-boot.bin+TZSW(TrustZone一种安全机制的支持，SAMSUNG提供)，bootloader组成如下图所示：

![exynos4412bootloader组成](.\exynos4412bootloader组成.jpg)



exynos4412物理地址空间映射：

![exynos4412物理地址空间映射](.\exynos4412物理地址空间映射.jpg)

exynos4412 Internal RAM Map:

![exynos4412IRAMMap](.\exynos4412IRAMMap.jpg)



# 八、串口信息打印支持

## 8.1 添加临时栈  

```shell
$vim board/samsung/fs4412/lowlevel_init.S
```

在lowlevel_init:后添加： ok

```assembly
ldr sp,=0x02060000 @use iRam stack in bl2  
```

## 8.2 添加关闭看门狗代码  

在beq wakeup_reset后添加

```assembly
    #if 1 /*for close watchdog */
    /* PS-Hold high */
    ldr r0, =0x1002330c
    ldr r1, [r0]
    orr r1, r1, #0x300
    str r1, [r0]  

    ldr r0, =0x11000c08
    ldr r1, =0x0
    str r1, [r0]
    /* Clear MASK_WDT_RESET_REQUEST */
    ldr r0, =0x1002040c
    ldr r1, =0x00
    str r1, [r0]
    #endif 
```

##  8.3 添加串口初始化代码

在 uart_asm_init: 的str r1, [r0, #EXYNOS4_GPIO_A1_CON_OFFSET]后添加：

```assembly
    ldr r0, =0x10030000
    ldr r1, =0x666666
    ldr r2, =CLK_SRC_PERIL0_OFFSET
    str r1, [r0, r2]
    ldr r1, =0x777777
    ldr r2, =CLK_DIV_PERIL0_OFFSET
    str r1, [r0, r2]
```

##  8.4 注释掉tzpc_init

注释掉bl uart_asm_init下的bl tzpc_init  ok

## 8.5 重新编译 u-boot

```shell
$  make
$ ./build.sh
```


烧写新的 u-boot_fs4412.bin，重新加电后会看到串口信息  

# 九、网卡支持

## 9.1 添加网络初始化代码  

```shell
$vim board/samsung/fs4412/fs4412.c
```

在 struct exynos4_gpio_part2 *gpio2; 后添加：

```c
#ifdef CONFIG_DRIVER_DM9000
#define EXYNOS4412_SROMC_BASE 0X12570000
#define DM9000_Tacs (0x1)
#define DM9000_Tcos (0x1)
#define DM9000_Tacc (0x5)
#define DM9000_Tcoh (0x1)
#define DM9000_Tah (0xC)
#define DM9000_Tacp (0x9)
#define DM9000_PMC (0x1)

struct exynos_sromc 
{
    unsigned int bw;
    unsigned int bc[6];
};

/*
* s5p_config_sromc() - select the proper SROMC Bank and configure the
* band width control and bank control registers
* srom_bank - SROM
* srom_bw_conf - SMC Band witdh reg configuration value
* srom_bc_conf - SMC Bank Control reg configuration value
*/
void exynos_config_sromc(u32 srom_bank, u32 srom_bw_conf, u32 srom_bc_conf)
{
    unsigned int tmp;
    struct exynos_sromc *srom = (struct exynos_sromc *)(EXYNOS4412_SROMC_BASE);
    /* Configure SMC_BW register to handle proper SROMC bank */
    tmp = srom->bw;
    tmp&= ~(0xF << (srom_bank * 4));
    tmp |= srom_bw_conf;
    srom->bw = tmp;
    /* Configure SMC_BC register */
    srom->bc[srom_bank] = srom_bc_conf;
}

static void dm9000aep_pre_init(void)
{
    //unsigned int tmp;
    unsigned char smc_bank_num = 1;
    unsigned int smc_bw_conf=0;
    unsigned int smc_bc_conf=0;
    /* gpio configuration */
    writel(0x00220020, 0x11000000 + 0x120);//GPY0CON  5-EBI_WEn 4-EBI_OEn 1-SROM_CSn[1] 
    writel(0x00002222, 0x11000000 + 0x140);//GPY1CON  3-EBI_DATA_RDn 2-SROM_WAITn 1-EBI_BEn[1] 0-EBI_BEn[0]
    /* 16 Bit bus width */
    writel(0x22222222, 0x11000000 + 0x180);//GPY3CON
    writel(0x0000FFFF, 0x11000000 + 0x188);//GPY3PUD
    writel(0x22222222, 0x11000000 + 0x1C0);//GPY5CON
    writel(0x0000FFFF, 0x11000000 + 0x1C8);//GPY5PUD
    writel(0x22222222, 0x11000000 + 0x1E0);//GPY6CON
    writel(0x0000FFFF, 0x11000000 + 0x1E8);//GPY6PUD
    smc_bw_conf &= ~(0xf<<4);
    smc_bw_conf |= (1<<7) | (1<<6) | (1<<5) | (1<<4);
    smc_bc_conf = ((DM9000_Tacs << 28)
    | (DM9000_Tcos << 24)
    | (DM9000_Tacc << 16)
    | (DM9000_Tcoh << 12)
    | (DM9000_Tah << 8)
    | (DM9000_Tacp << 4)
    | (DM9000_PMC));
    exynos_config_sromc(smc_bank_num,smc_bw_conf,smc_bc_conf);
}
#endif
```

在 gd->bd->bi_boot_params = (PHYS_SDRAM_1 + 0x100UL); 后添加 ：

```c
#ifdef CONFIG_DRIVER_DM9000
	dm9000aep_pre_init();
#endif
```

在文件末尾添加：

```c
#ifdef CONFIG_CMD_NET
#include <netdev.h>
int board_eth_init(bd_t *bis)
{
    int rc = 0;

    #ifdef CONFIG_DRIVER_DM9000
    rc = dm9000_initialize(bis);
    #endif
    
    return rc;
}
#endif
```

## 9.2 修改配置文件添加网络相关配置 

```shell
$ vim include/configs/fs4412.h   
#注意：该文件中不能出现//行注释，因为该文件会被链接脚本包含，而链接脚本内不支持//注释
```

修改#undef CONFIG_CMD_PING为#def ine CONFIG_CMD_PING

修改#undef CONFIG_CMD_NET为#def ine CONFIG_CMD_NET

在文件末尾#endif /* __CONFIG_H */前面添加：

```c
#ifdef CONFIG_CMD_NET
    #define CONFIG_NET_MULTI
    #define CONFIG_DRIVER_DM9000 1
	/*SROMC BANK1 memory addr 0x05000000*/
    #define CONFIG_DM9000_BASE 0x05000000  
    #define DM9000_IO CONFIG_DM9000_BASE
    #define DM9000_DATA (CONFIG_DM9000_BASE + 4)
    #define CONFIG_DM9000_USE_16BIT
    #define CONFIG_DM9000_NO_SROM 1
    #define CONFIG_ETHADDR 11:22:33:44:55:66
    #define CONFIG_IPADDR 192.168.9.99
    #define CONFIG_SERVERIP 192.168.9.16
    #define CONFIG_GATEWAYIP 192.168.9.1
    #define CONFIG_NETMASK 255.255.255.0
#endif
```

##   9.3 重新编译 u-boot  

```shell
$ make
$ ./build.sh  
```

烧写新的 u-boot_fs4412.bin重新加电后，在u-boot命令行设置好网络参数后接上网线用：

```shell
FS4412 # ping 主机ip地址
```

  来验证网络是否正常

# 十、EMMC支持

EMMC  =  Flash + Flash控制器

## 10.1 初始化 EMMC

### a. 添加器件支持代码

```shell
$cd ~/fs4412/u-boot-2013.01
$cp  ~/fs4412/u-boot-porting-file/movi/movi.c  arch/arm/cpu/armv7/exynos/
$cp  ~/fs4412/u-boot-porting-file/movi/movi.h include/
$vim arch/arm/cpu/armv7/exynos/Makefile
```


在 pinmux.o 后添加 movi.o  



### b. 修改板级文件：

```shell
$vim board/samsung/fs4412/fs4412.c
```

#### b1. 在#include <asm/arch/mmc.h>后面添加

```c
#include <asm/arch/clk.h>
#include "origen_setup.h"
```

#### b2. 在#ifdef CONFIG_GENERIC_MMC后面添加：

```c
u32 sclk_mmc4; /*clock source for emmc controller*/
#define __REGMY(x) (*((volatile u32 *)(x)))
#define CLK_SRC_FSYS __REGMY(EXYNOS4_CLOCK_BASE + CLK_SRC_FSYS_OFFSET)
#define CLK_DIV_FSYS3 __REGMY(EXYNOS4_CLOCK_BASE + CLK_DIV_FSYS3_OFFSET)
int smdk_s5p_mshc_init(void);
int emmc_init(void)
{
    u32 tmp;
    u32 clock;
    u32 i;
    int ret = 0;
    
    /* setup_hsmmc_clock */
    /* MMC4 clock src = SCLKMPLL */
    tmp = CLK_SRC_FSYS & ~(0x000f0000);
    CLK_SRC_FSYS = tmp | 0x00060000;
    /* MMC4 clock div */
    tmp = CLK_DIV_FSYS3 & ~(0x0000ff0f);
    clock = get_pll_clk(MPLL)/1000000;
    for(i=0 ; i<=0xf; i++) {
	    sclk_mmc4=(clock/(i+1));
    	if(sclk_mmc4 <= 160) //200
    	{
    		CLK_DIV_FSYS3 = tmp | (i<<0);
    		break;1
    	}
    }
    emmcdbg("[mjdbg] sclk_mmc4:%d MHZ; mmc_ratio: %d\n",sclk_mmc4,i);
    sclk_mmc4 *= 1000000;
    /*
     * MMC4 EMMC GPIO CONFIG
     * GPK0[0] SD_4_CLK
     * GPK0[1] SD_4_CMD
     * GPK0[2] SD_4_CDn
     * GPK0[3:6] SD_4_DATA[0:3]
    */
    writel(readl(0x11000048)&~(0xf),0x11000048); //SD_4_CLK/SD_4_CMD pull-down enable
    writel(readl(0x11000040)&~(0xff),0x11000040);//cdn set to be output
    writel(readl(0x11000048)&~(3<<4),0x11000048); //cdn pull-down disable
    writel(readl(0x11000044)&~(1<<2),0x11000044); //cdn output 0 to shutdown the emmc power
    writel(readl(0x11000040)&~(0xf<<8)|(1<<8),0x11000040);//cdn set to be output
    udelay(100*1000);
    writel(readl(0x11000044)|(1<<2),0x11000044); //cdn output 1
    writel(0x03333133, 0x11000040);
    writel(0x00003FF0, 0x11000048);
    writel(0x00002AAA, 0x1100004C);
    #ifdef CONFIG_EMMC_8Bit
    writel(0x04444000, 0x11000060);
    writel(0x00003FC0, 0x11000068);
    writel(0x00002AAA, 0x1100006C);
    #endif
    #ifdef USE_MMC4
    ret = smdk_s5p_mshc_init();
    #endif
    
    return ret;
}
```

#### b3. 将 int board_mmc_init(bd_t *bis)函数内容改写为 

#### 到这

```c
int board_mmc_init(bd_t *bis)
{
    int i, err;
    
    #ifdef CONFIG_EMMC
    err = emmc_init();
    #endif
    
    return err;
}
```

#### b4. 在末尾添加:  

```c
#ifdef CONFIG_BOARD_LATE_INIT
#include <movi.h>
int chk_bootdev(void)//mj for boot device check
{
    char run_cmd[100];
    struct mmc *mmc;
    int boot_dev = 0;
    //int cmp_off = 0x10;
    ulong start_blk, blkcnt;
    
    mmc = find_mmc_device(0);
    if (mmc == NULL)
    {
        printf("There is no eMMC card, Booting device is SD card\n");
        boot_dev = 1;
        return boot_dev;
    }
    start_blk = (24*1024/MOVI_BLKSIZE);
    blkcnt = 0x10;
    sprintf(run_cmd,"emmc open 0");
    run_command(run_cmd, 0);
    sprintf(run_cmd,"mmc read 0 %lx %lx %lx",(unsigned long)CFG_PHY_KERNEL_BASE,start_blk,blkcnt);
    run_command(run_cmd, 0);
    /* switch mmc to normal paritition */
    sprintf(run_cmd,"emmc close 0");
    run_command(run_cmd, 0);
    return 0;
}

int board_late_init (void)
{
    int boot_dev =0 ;
    //char boot_cmd[100];
    boot_dev = chk_bootdev();
    if(!boot_dev)
    {
	    printf("\n\nChecking Boot Mode ... EMMC4.41\n");
    }
    return 0;
}
#endif
```

## 10.2  添加相关命令支持

```shell
$ cd ~/fs4412/u-boot-2013.01
$ cp ~/fs4412/u-boot-porting-file/movi/cmd_movi.c common/
$ cp ~/fs4412/u-boot-porting-file/movi/cmd_mmc.c common/
$ cp ~/fs4412/u-boot-porting-file/movi/cmd_mmc_fdisk.c common/

#修改 Makefile
$ vim common/Makefile
```

在COBJS-$(CONFIG_CMD_MMC) += cmd_mmc.o后添加：

```makefile
COBJS-$(CONFIG_CMD_MMC) += cmd_mmc_fdisk.o
COBJS-$(CONFIG_CMD_MOVINAND) += cmd_movi.o
```

## 10.3 添加驱动

```shell
$ cp ~/fs4412/u-boot-porting-file/movi/mmc.c drivers/mmc/
$ cp ~/fs4412/u-boot-porting-file/movi/s5p_mshc.c drivers/mmc/
$ cp ~/fs4412/u-boot-porting-file/movi/mmc.h include/
$ cp ~/fs4412/u-boot-porting-file/movi/s5p_mshc.h include/

#修改 Makefile
$vim drivers/mmc/Makefile
```

添加

```makefile
COBJS-$(CONFIG_S5P_MSHC) += s5p_mshc.o
```

## 10.4 添加 EMMC 相关配置

```shell
$vim include/configs/fs4412.h
```

在文件最后一行#endif  /\*__CONFIG_H\*/前添加：

```c
#define CONFIG_EVT1 1 /* EVT1 */

#ifdef CONFIG_EVT1
	/* eMMC44_CH4 (OMPIN[5:1] = 4) */
	#define CONFIG_EMMC44_CH4 

	#ifdef CONFIG_SDMMC_CH2
		#define CONFIG_S3C_HSMMC
		#undef DEBUG_S3C_HSMMC
		#define USE_MMC2
	#endif

	#ifdef CONFIG_EMMC44_CH4
		#define CONFIG_S5P_MSHC
		#define CONFIG_EMMC 1
		#define USE_MMC4
		/* #define CONFIG_EMMC_8Bit */
		#define CONFIG_EMMC_EMERGENCY
		/* #define emmcdbg(fmt,args...) printf(fmt ,##args) */ /* for emmc debug */
		#define emmcdbg(fmt,args...)
	#endif
#endif /*end CONFIG_EVT1*/

#define CONFIG_CMD_MOVINAND
#define CONFIG_CLK_1000_400_200
#define CFG_PHY_UBOOT_BASE CONFIG_SYS_SDRAM_BASE + 0x3e00000
#define CFG_PHY_KERNEL_BASE CONFIG_SYS_SDRAM_BASE + 0x8000
#define BOOT_MMCSD 0x3
#define BOOT_EMMC43 0x6
#define BOOT_EMMC441 0x7
#define CONFIG_BOARD_LATE_INIT  
```

## 10.5 重新编译 u-boot

```shell
$ make
$ ./build.sh
```

烧写新的 u-boot_fs4412.bin复位后进入u-boot命令行执行：

```shell
FS4412 #  mmcinfo  
```

看到如下显示就OK了

![EMMC移植结果](.\EMMC移植结果.jpg)