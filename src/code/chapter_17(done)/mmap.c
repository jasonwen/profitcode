#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	int fd;
	char *buf;
	int i;
	struct stat statbuf;

	if(stat("test.txt", &statbuf) == -1){ /* �õ�һ���ļ���״̬��Ϣ���õ��ļ��Ĵ�С */
		perror("fail to get stat");
		exit(1);
	}

	fd = open("test.txt", O_RDONLY); /* ��ֻ����ʽ���ļ� */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}

	/* ����һ���ڴ�ӳ�䣬��ʼ��ַ��ϵͳΪ�û�ѡ�񣬲���Ϊ����ֵ����
	* ������ӳ�����Ĵ�СΪ�򿪵��ļ��Ĵ�С
	* ����Ȩ��Ϊֻ��������Ϊ����д�����̣���ֹ�������д�������
	*/
	buf = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if(buf == MAP_FAILED){
		perror("fail to mmap");
		exit(1);
	}

	i = 0;
	while(i < statbuf.st_size){ /* ���ÿһ���ַ���ע��mmap����������ӡ�\0�������� */
		printf("%c", buf[i]);
		i++;
	}
	printf("\n");
	
	if(munmap(buf, statbuf.st_size) == -1){ /* �����ڴ�ӳ�� */
		perror("fail to munmap");
		exit(1);
	}

	close(fd); /* �ر��ļ� */
	
	return 0;
}
