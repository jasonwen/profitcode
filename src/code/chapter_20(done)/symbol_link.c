#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define MAX 1024

int main(void)
{
	int fd;
	int n;
	char buf[MAX];

	if(symlink("test.txt", "symbol_link") == -1){ /* ����һ���������ӣ�Ŀ���ļ���test.txt */
		perror("fail to create symbol link");
		exit(1);
	}
	
	printf("already create a symbol-link\n"); /* �����ʾ��Ϣ */
	
	if((fd = open("symbol_link", O_RDWR)) == -1){ /* ͨ���������Ӵ򿪸�Ŀ���ļ� */
		perror("fail to open");
		exit(1);
	}

	if((n = read(fd, buf, MAX)) == -1){ /* ��Ŀ���ļ������� */
		perror("fail to read");
		exit(1);
	}
	buf[n] = '\0';

	printf("file content is : %s\n", buf); /* ��ӡĿ���ļ������� */

	strcat(buf, ", admin");

	if(write(fd, buf, strlen(buf)) == -1){ /* ��Ŀ���ļ���� */
		perror("fail to write");
		exit(1);
	}

	printf("done\n"); /* �����ʾ��Ϣ */

	close(fd);

	return 0;
}
