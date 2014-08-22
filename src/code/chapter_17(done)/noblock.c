#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define MAX 100000
#define LEN 1024  /* ʹ�ú���Ϊ�������Ĵ�С */

int main(int argc, char *argv[ ])
{
	int fd1, fd2; 
	FILE *fp;
	char buf[MAX]; /* ���ļ��Ļ����� */
	int n, rest;
	char *p = buf;
	char content[LEN];

	if(argc != 3){ /* ȱ���ļ��� */
		printf("expect args\n");
		exit(1);
	}

	fd1 = open(argv[1], O_RDONLY); /* �����ļ� */
	if(fd1 == -1){
		perror("fail to read");
		exit(1);
	}

	fp = fopen(argv[2], "w"); /* �������ԭ����ļ���ʹ�ø�ʽ��I/O */
	if(fp == NULL){
		perror("fail to read");
		exit(1);
	}

	fd2 = open("test.txt", O_WRONLY); /* ����ļ��������ļ�test.txt�ļ� */
	if(fd2 == -1){
		perror("fail to read");
		exit(1);
	}

	rest = read(fd1, buf, MAX); /* ���ļ������ݵ������� */
	printf("get %d bytes from %s\n", rest, argv[1]);

	while(rest > 0){ /* ��Ҫ��������ݻ���ʣ��ʱ������� */
		errno = 0;
		n = write(fd2, p, rest); /* ������������� */
		
		fprintf(fp, "write %d, errno %s\n", n, strerror(errno)); /* ������ʧ�����������ԭ�� */
		if(rest > 0){ /* ����ʣ����ֽ��� */
			p += n;
			rest -= n;
		}
	}

	printf("done\n");

	return 0;
}
