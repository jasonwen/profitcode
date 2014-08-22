#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;
	int i;

	fd = open("test.txt", O_RDWR); /* ��һ���ļ�����򿪷�ʽΪ��д */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}
	
	i = 0;
	while(i < 3){
		sleep(5); /* ���������� */

		printf("hello\n");
		if(write(fd, "hello\n", 6) == -1){ /* ���ļ����һ���ַ�����Ϊ��ʾ��Ϣ */
			perror("fail to write");
			exit(1);
		}
		
		if(fsync(fd) == -1){ /* �����Ϣ�����������ļ�ͬ������֤�����Ϣ��ʱд�ص������� */
			perror("fail to fsync");
			exit(1);
		}

		i++;
	}

	close(fd); /* �ر��ļ� */

	return 0;
}
