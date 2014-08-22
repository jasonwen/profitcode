/*
用途：计算n的阶乘，n由用户输入
重点：scanf的使用，do while的使用
*/
#include <stdio.h>

int main(void)
{
	int n;
	int result = 1;
	int i;

	scanf("%d", &n); //从标准输入中读取n的值
	
	i = 1;
	do{
		result *= i;
		i++;
	}while(i <= n);

	printf("the result is %d\n", result);

	return 0;
}
