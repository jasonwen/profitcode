#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define MAX 1024

int main(void)
{
	int fd;
	off_t off;
	char buf[MAX];

	fd = open("test.txt", O_RDWR); /* ��һ���ļ� */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}

	printf("before reading\n"); /* �����ʾ��Ϣ */

	off = lseek(fd, 0, SEEK_CUR); /* ����lseek�����õ���ǰ�ļ��Ķ�дλ�� */
	if(off == -1){
		perror("fail to lseek");
		exit(1);
	}
	
	printf("the offset is : %d\n", off); /* �����ʾ��Ϣ */

	if(read(fd, buf, 5) == -1){ /* ��ȡ5���ֽڵ��ļ����� */
		perror("fail ot read");
		exit(1);
	}

	printf("after reading\n"); /* �����ʾ��Ϣ */
	
	off = lseek(fd, 0, SEEK_CUR); /* �ٴε���lseek�����õ���ǰ�ļ��Ķ�дλ�� */
	if(off == -1){
		perror("fail to lseek");
		exit(errno);
	}
	
	printf("the offset is : %d\n", off); /* ������ */

	close(fd); /* �ر��ļ� */

	return 0;
}
