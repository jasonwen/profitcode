#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define MAX 100000
#define LEN 1024

int main(int argc, char *argv[ ])
{
	int fd1, fd2; 
	FILE *fp;
	char buf[MAX]; /* ���ļ��Ļ����� */
	int n, rest;
	char *p = buf;
	char content[LEN];
	int flags;

	if(argc != 3){ /* ȱ���ļ��� */
		printf("expect args\n");
		exit(1);
	}

	fd1 = open(argv[1], O_RDONLY); /* �������ļ� */
	if(fd1 == -1){
		perror("fail to read");
		exit(1);
	}

	fd2 = open(argv[2], O_WRONLY); /* �����������Ϣ���ļ� */
	if(fd2 == -1){
		perror("fail to read");
		exit(1);
	}

	fp = fdopen(fd2, "w"); /* ���ļ�����ֻд�ķ�ʽ */
	if(fp == NULL){
		perror("fail to open");
		exit(1);
	}

	flags = fcntl(STDOUT_FILENO, F_GETFL, 0); /* ����׼�������Ϊ��������ʽ */
	if(flags == -1){
		perror("fail to fcntl");
		exit(1);
	}
	flags |= O_NONBLOCK; /* ���÷�������־ */
	if(fcntl(STDOUT_FILENO, F_SETFL, flags) == -1){ /* ���������ļ���״̬��־ */
		perror("fail to fcntl");
		exit(1);
	}

	rest = read(fd1, buf, MAX); /* �����ļ� */
	printf("get %d bytes from %s\n", rest, argv[1]);

	while(rest > 0){ /* ��Ҫ��������ݻ���ʣ��ʱ������� */
		errno = 0;
		n = write(STDOUT_FILENO, p, rest); /* ������������� */
		
		fprintf(fp, "write %d, errno %s\n", n, strerror(errno)); /* ������ʧ�����������ԭ�� */
		if(rest > 0){ /* ����ʣ����ֽ��� */
			p += n;
			rest -= n;
		}
	}

	printf("done\n");

	close(fd1); /* �ر��ļ� */

	fclose(fp);

	return 0;
}
