#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/* �������Ĵ�С */
#define MAX 1024

int main(void)
{
	int fd;
	struct stat statbuf;
	char buf[MAX];
	int n;
	
	if(stat("test.txt", &statbuf) == -1){ /* �õ�Ŀ���ļ���״̬ */
		perror("fail to get status");
		exit(1);	
	}
	
	/* ��ӡ�ļ��������� */
	printf("test.txt, the number of links is : %d\n", statbuf.st_nlink);
	
	/* ��ǰĿ¼�´���һ������test2.txt���ļ������ļ���test.txt����һ��i��� */
	if(link("test.txt", "test2.txt") == -1){
		perror("fail to link");
		exit(1);	
	}
	
	/* �ٴ�ȡ��test.txt�ļ���״̬�����������Ѿ����� */
	if(stat("test.txt", &statbuf) == -1){
		perror("fail to get status");
		exit(1);	
	}
	
	printf("test.txt, the number of links is : %d\n", statbuf.st_nlink);
	
	/* �õ�test2.txt�ļ���״̬�����״̬�ṹʵ�������ļ�test.txt�� */
	if(stat("test2.txt", &statbuf) == -1){
		perror("fail to get status");
		exit(1);	
	}
	
	printf("test2.txt, the number of links is : %d\n", statbuf.st_nlink);
	printf("\n");
	
	if((fd = open("test.txt", O_RDWR)) == -1){ /* ���ļ�test.txt */
		perror("fail to open");
		exit(1);
	}
	
	strcpy(buf, "hello world"); /* �����ַ��� */
	
	if((n = write(fd, buf, strlen(buf))) == -1){ /* ���ļ�������ַ���"hello world" */
		perror("fail to write");
		exit(1);	
	}

	close(fd); /* �ر��ļ���������ַ���д�뵽�����ļ��� */
	
	if((fd = open("test2.txt", O_RDWR)) == -1){ /* ��test2.txt�ļ� */
		perror("fail to open");
		exit(1);
	}

	if((n = read(fd, buf, n)) == -1){ /* �����ļ������� */
		perror("fail to read");
		exit(1);	
	}
	buf[n] = '\0'; /* ����ַ���������־�����ڴ�ӡ */

	printf("content of test2.txt is : %s\n", buf); /* ���test2.txt�ļ��е����� */

	close(fd);
	
	/* ɾ��test2.txt��Ŀ¼�����������ļ�û���ܵ�Ӱ�죬
	* �Կ���ͨ����һ������test.txt���ø��ļ� 
	*/
	if(unlink("test2.txt") == -1){
		perror("fail to unlink");
		exit(1);	
	}
	
	if(stat("test.txt", &statbuf) == -1){ /* �õ�test.txt�ļ���״̬ */
		perror("fail to get status");
		exit(1);	
	}
	
	printf("test.txt, the number of links is : %d\n", statbuf.st_nlink); /* ��ӡ���ļ����Ӽ��� */
	
	/* ��test.txt�ļ������������Ա�����ļ���ϵͳɾ�� */
	if((fd = open("test.txt", O_RDWR)) == -1){
		perror("fail to open");
		exit(1);
	}
	
	if(unlink("test.txt") == -1){ /* ���ڸ��ļ������ü���Ϊ0�� */
		perror("fail to unlink");
		exit(1);	
	}
	
	if(fstat(fd, &statbuf) == -1){ /* �õ��ļ���״̬ */
		perror("fail to get status");
		exit(1);	
	}
	
	printf("test.txt, the number of links is : %d\n", statbuf.st_nlink);
	printf("\n");

	/* �����ļ���Ȼ�򿪣����и��ļ��Կ���Ӧ�� */
	if((n = read(fd, buf, n)) == -1){
		perror("fail to read");
		exit(1);	
	}
	buf[n] = '\0';

	printf("content of test.txt is : %s\n", buf); /* ������ */
	
	close(fd); /* �ر��ļ� */
	
	return 0;	
}
