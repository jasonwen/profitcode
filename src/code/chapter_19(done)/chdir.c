#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int fd;
	char *p = "hello world\n"; /* �����õ��ַ��� */

	if(chdir("/home/admin/tmp") == -1){ /* �ı���̵Ĺ���Ŀ¼ */
		perror("fail to change dir");
		exit(1);
	}
	
	printf("change dir successfully\n"); /* �����ʾ��Ϣ */

	if((fd = open("test.txt", O_CREAT | O_RDWR)) == -1){ /* ����һ���ļ������ļ��������޸ĺ��Ŀ¼ */
		perror("fail to open");
		exit(1);
	}

	if(write(fd, p, strlen(p)) == -1){ /* ����ļ���������� */
		perror("fail to write");
		exit(1);
	}

	close(fd); /* �ر��ļ� */

	return 0;
}
