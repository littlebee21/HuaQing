#define GPA1CON (*(volatile unsigned int*)0x11400020)

#define ULCON2 (*(volatile unsigned int*)0x13820000)
#define UCON2 (*(volatile unsigned int*)0x13820004)
#define UBRDIV2 (*(volatile unsigned int*)0x13820028)
#define UFRACVAL2 (*(volatile unsigned int*)0x1382002c)


#define URXH2 (*(volatile unsigned int*)0x13820024)
#define UTXH2 (*(volatile unsigned int*)0x13820020)
#define UTRSTAT2 (*(volatile unsigned int*)0x13820010)

//本函数初始化串口
void uart_init(void)
{
	GPA1CON = (GPA1CON & (~0xff)) | 0x22; //将GPA1_0,GPA1_1作为串口2收发数据线
	ULCON2 = 0x3; //常规模式,无校验,1个停止位,8个数据位
	UCON2 = 0x5; //接收和发送都使用中断或查询模式
	//以下设置波特率为115200
	UBRDIV2 = 0x35;
	UFRACVAL2 = 0x5;
}

//本函数从串口接收一个字节做为返回值
unsigned char uart_getc()
{
	unsigned char c;
	while(!(UTRSTAT2 & 0x1)); //等待接收完成,收到数据是UTRSTAT2第0位会变为1,否则为0
	c=URXH2; //将接收到的数据存入c
	return c; //返回收到的数据
}

//本函数通过串口发送一个字节的数据c
void uart_putc(unsigned char c)
{
	while(!(UTRSTAT2 & 0x2)); //等待以前的数据发送完成,也就等待缓存为空
	UTXH2 = c;
}

//本函数通过串口发送一个字符串
void uart_puts(const char *str)
{
	while(*str != '\0')
		uart_putc(*str++);
}
