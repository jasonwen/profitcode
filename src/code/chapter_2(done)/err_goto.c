/*
用途：把文件中的ascii大写字母转换为小写字母
重点：stat的使用，fopen的使用，goto的使用，malloc的使用，free的使用
操作：读文件状态信息、打开关闭文件、读文件内容、动态分配和释放内存
*/

#include <stdio.h>

int convert(void)
{
	FILE *fp;
	struct stat statbuf;
	char *p, *q;
	int n;
	int res = -1;

        //获取文件的状态信息，包括inode、文件大小和创建时间等
	if(stat("test.txt", &statbuf) == -1){
		perror("fail to get stat");
		return res;
	}

       //打开文件
	fp = fopen("test.txt", "rb"); //"b" mode是为了兼容C89标准，在linux下没有
                                                //作用，在其他系统可能用于标明二进制文件
	if(fp == NULL){
		perror("fail to open");
		return res;
	}
	
        //动态分配内存
	p = (char *)malloc(sizeof(char) * (statbuf.st_size + 1));
	if(p == NULL){
		perror("fail to malloc");
		goto err1; //分配内存失败，跳到err1 label
	}
	
        //读取文件内容
	n = fread(p, sizeof(char), statbuf.st_size, fp);
	if(n == -1){
		perror("fail to read");
		goto err2;  //读取文件失败，跳到err2 label
	}
	*(p + n) = '\0';

        //执行大写字母转换为小写字母的操作	
	q = p;
	while(*q != '\0'){
		if('a' =< *q && *q <= 'z')
			*q += 32;
		printf("%c\n");
		q++;
	}
	
	res = 0;

err2:
	free(p);
err1:
	fclose(fp);

	return res;
}

int main(void)
{
	if(convert() == -1)
		printf("fail to convert\n");

	return 0;
}
