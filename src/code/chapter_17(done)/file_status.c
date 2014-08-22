#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int fd;
	int flag;
	char *p = "1st linux"; /* ����ʹ�õ��ַ��� */
	char *q = "2nd linux";

	fd = open("test.txt", O_WRONLY); /* ���ļ�ֻд�� */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}

	if(write(fd, p, strlen(p)) == -1){ /* ���������ݣ������ݻḲ�ǲ��־ɵ����� */
		perror("fail to write");
		exit(1);
	}

	flag = fcntl(fd, F_GETFL, 0); /* ��ʹ��F_GETFL����õ��ļ�״̬��־ */
	if(flag == -1){
		perror("fail to fcntl");
		exit(1);
	}
	flag |= O_APPEND; /* ���ļ�״̬��־���"׷��д"ѡ�� */
	if(fcntl(fd, F_SETFL, flag) == -1){ /* ���ļ�״̬�޸�Ϊ׷��д */
		perror("fail to fcntl");
		exit(1);
	}

	if(write(fd, q, strlen(q)) == -1){ /* �ٴ����������ݣ������ݻ�׷���ھ����ݵĺ��� */
		perror("fail to write");
		exit(1);
	}

	close(fd); /* �ر��ļ� */

	return 0;
}
