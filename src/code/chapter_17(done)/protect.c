#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/* SIGBUS�źŵĴ����������һ����ʾ��Ϣ */
void sigbus_handler(int signo)
{
	printf("permission denied\n");
}

int main(void)
{
	int fd;
	char *buf;
	struct stat statbuf;

	if(signal(SIGBUS, sigbus_handler) == SIG_ERR){ /* ����SIGBUS���źŴ������ */
		perror("can��t set handler for SIGALRM");
		exit(0);
	}

	if(stat("test.txt", &statbuf) == -1){ /* �õ�һ���ļ���״̬��Ϣ���õ��ļ��Ĵ�С */
		perror("fail to get stat");
		exit(1);
	}

	fd = open("test.txt", O_WRONLY); /* �Կ�д��ʽ���ļ� */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}

	/* ����һ���ڴ�ӳ�����������Ȩ��Ϊֻ�� */
	buf = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if(buf == MAP_FAILED){
		perror("fail to mmap");
		exit(1);
	}
	
	printf("try to write\n");
	strcpy(buf, "China\n"); /* ����дһ��ֻ����ӳ���� */

	/* ��ӳ�����ķ���Ȩ�޸ı�Ϊ�ɶ���д */
	if(mprotect(buf, statbuf.st_size, PROT_READ | PROT_WRITE) == -1){
		perror("fail to alter permission");
		exit(1);
	}

	printf("write again\n");
	strcpy(buf, "China\n"); /* �ٴ�дһ��ֻ����ӳ���� */

	if(munmap(buf, statbuf.st_size) == -1){ /* �����ڴ�ӳ�� */
		perror("fail to munmap");
		exit(1);
	}

	close(fd); /* �ر��ļ� */
	
	return 0;
}
