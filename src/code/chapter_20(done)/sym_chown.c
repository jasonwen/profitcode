#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(void)
{
	struct stat statbuf;
	char buf[1024];
	
	printf("before changing\n\n"); /* �����ʾ��Ϣ */

	if(stat("test.txt", &statbuf) == -1){ /* �õ�Ŀ���ļ���״̬��Ϣ */
		perror("fail to get status");
		exit(1);	
	}
	
	printf("the owner of test.txt is : %d\n", (unsigned int)statbuf.st_uid);
	printf("the group of test.txt is : %d\n", (unsigned int)statbuf.st_gid);

	if(lstat("sl", &statbuf) == -1){ /* ʹ��lstat�����õ��������ӵ�״̬��Ϣ */
		perror("fail to get status");
		exit(1);	
	}
	
	printf("the owner of sl is : %d\n", (unsigned int)statbuf.st_uid);
	printf("the group of sl is : %d\n", (unsigned int)statbuf.st_gid);
	
	if(chown("sl", 0, -1) == -1){ /* �ı�Ŀ���ļ��������� */
		perror("fail to change owner");
		exit(1);	
	}
	
	printf("after changing\n"); /* �����ʾ��Ϣ */

	if(stat("test.txt", &statbuf) == -1){ /* �ٴεõ�Ŀ���ļ����ļ�״̬��Ϣ */
		perror("fail to get status");
		exit(1);	
	}
	
	printf("the owner of test.txt is : %d\n", (unsigned int)statbuf.st_uid);
	printf("the group of test.txt is : %d\n", (unsigned int)statbuf.st_gid);

	if(lstat("sl", &statbuf) == -1){ /* ʹ��lstat�����õ��������ӱ�����ļ�״̬��Ϣ */
		perror("fail to get status");
		exit(1);	
	}
	
	printf("the owner of sl is : %d\n", (unsigned int)statbuf.st_uid);
	printf("the group of sl is : %d\n", (unsigned int)statbuf.st_gid);
	
	return 0;	
}
