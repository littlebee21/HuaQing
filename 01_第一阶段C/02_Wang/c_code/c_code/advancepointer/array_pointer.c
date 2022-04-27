#include <stdio.h>

#define H 3
#define L 4
#define FUNC_VERSION
float get_ave(int tarr[][L],int hs);
int main(int argc,char *argv[])
{
	int arr[H][L] = {{1,2,3,4},
	                 {5,6,7,8},
			 {9,10,11,12}
	                };
	float ave = 0.0f;

#ifdef FUNC_VERSION
	ave = get_ave(arr,H);
#else
	int sum = 0;
	int i = 0;
	int (*parr)[L] = NULL;

	for(parr = arr;parr < arr+H;parr++)
	{
		for(i = 0;i < L;i++)
		{
			sum += *(*parr + i);
		}
	}

	ave = (float)sum / (H * L);
#endif

	printf("The ave is %.2f\n",ave);


	return 0;
}

/*
 * 二维数组作为函数形参类型时等价于指向一维数组的数组指针（将一整行（一维数组）看作是特殊元素）
 * 三维数组作为函数形参类型时等价于指向二维数组的数组指针（将一整层（二维数组）看作是特殊元素）
 * 。。。。。。。
 * N维数组作为函数形参类型时等价于指向N-1维数组的数组指针（将N-1维数组整体看作是特殊元素）
 *
 * N维数组作为函数形参类型时，第一维大小无需书写，写了不影响编译，但也没有任何实际的作用
 *                            其它维大小则都需书写，缺一不可
 * */
float get_ave(int tarr[][L],int hs)
{
	int (*parr)[L] = NULL;
	int sum  = 0;
	int i = 0;
	//int **pparr = tarr;  形参类型是int *tarr[]
	//int **ppparr = tarr;  形参类型是int **tarr[]
	//int (*parr)[3][4] = tarr;  形参类型是int tarr[][3][4]

	for(parr = tarr;parr < tarr+hs;parr++)
	{
		for(i = 0;i < L;i++)
		{
			sum += *(*parr + i);
		}
	}
	
	return (float)sum / (hs*L);

}
