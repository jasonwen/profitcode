#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	int fd;
	struct stat statbuf;
	pid_t pid;
	uid_t ruid, euid; /* ���̵�ʵ��ID����ЧID */
	
	if(stat("test.txt", &statbuf) == -1){ /* ȡ���ļ���״̬ */
		perror("fail to stat");
		exit(1);
	}

	/* �õ����̵�ʵ���û�ID����Ч�û�ID */
	euid = getuid(); 
	euid = geteuid();

	/* ��ӡ���̵�ʵ���û�ID����Ч�û�ID */
	printf("real id is : %u, effective id is : %u \n", (unsigned int)ruid, (unsigned int)euid);
	/* ��ӡ�ļ�������ID */
	printf("file owner is : %u\n", statbuf.st_uid);

	if(access("test.txt", R_OK) == -1){ /* �����ļ���Ȩ�� */
		perror("fail to access");
		exit(1);
	}
	
	printf("access successfully\n"); /* �����ʾ��Ϣ */

	if((fd = open("test.txt", O_RDONLY)) == -1){ /* �����Ȩ�޲��Գɹ������Դ��ļ� */
		perror("fail to open");
		exit(1);
	}
	
	printf("ready to read\n"); /* �����ʾ��Ϣ */

	close(fd); /* �ر��ļ� */
	
	return 0;
}
