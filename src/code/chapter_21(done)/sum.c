#include <stdio.h>
#include <stdlib.h>

#define MAX 1024

int main(void)
{
	FILE *fp;
	char buf[MAX];
	int n;
	char *p;
	int letter, number, blank;

	fp = fopen("text.txt", "rb"); /* �򿪸��ļ� */
	if(fp == NULL){
		perror("fail to open");
		exit(1);
	}

	letter = 0;
	number = 0;
	blank = 0;
	/* ѭ����ȡ�ļ������ݣ����ļ����ܴܺ󣬲���һ�ζ��뵽�������� */
	while((n = fread(buf, sizeof(char), MAX - 1, fp)) > 0){
		buf[n] = '\0'; /* �ֶ����ý����� */
		p = buf;

		while(*p != '\0'){ /* ����ÿ�ζ�����ļ����� */
			if(('a' <= *p && *p <= 'z') || ('A' <= *p && *p <= 'Z')) /* �ж�Ϊ��ĸ */
				letter++;
			if(*p == ' ') /* �ж�Ϊ�ո� */
				blank++;
			if('0' <= *p && *p <= '9') /* �ж�Ϊ���� */
				number++;
			p++;
		}
	}

	if(n == -1){ /* ���������� */
		perror("fail to read");
		exit(1);
	}

	/* ����������ĸ�����������Ϳո��� */
	printf("the sum of letter is : %d, the sum of number is : %d, 
		the sum of blank is : %d", letter, number, blank);

	return 0;
}
