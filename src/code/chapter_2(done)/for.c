/*
用途：计数1~n的和，n由用户输入
重点：for循环的使用，scanf的使用
操作：从标准输入读取数据
*/
#include <stdio.h>

int main(void)
{
	int n;
	int add = 0;
	int i;

	scanf("%d", &n);

	for(i = 1; i <= 10; i++)
		add += i;

	printf("the result is %d\n", add);

	return 0;
}
