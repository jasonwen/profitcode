#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	struct stat statbuf;
	
	if(stat("test.txt", &statbuf) == -1){ /* Ϊ�ı�������ǰ�ļ���״̬ */
		perror("fail to get status");
		exit(1);	
	}
	
	printf("before changing owner\n"); /* ��ӡ�ļ����������û�ID����ID */
	printf("the owner of test.txt is : %d\n", (unsigned int)statbuf.st_uid);
	printf("the group of test.txt is : %d\n", (unsigned int)statbuf.st_gid);
	printf("\n");
	
	if(chown("test.txt", 0, -1) == -1){ /* ���ļ����������޸�Ϊ���û������ı����û�ID */
		perror("fail to change owner");
		exit(1);	
	}
	
	if(stat("test.txt", &statbuf) == -1){ /* �ٴ�ȡ���ļ���״̬��Ϣ */
		perror("fail to get status");
		exit(1);	
	}
	
	printf("after changing owner\n");
	printf("the owner of test.txt is : %d\n", (unsigned int)statbuf.st_uid); /* ������ */
	printf("the group of test.txt is : %d\n", (unsigned int)statbuf.st_gid);
	printf("\n");
	
	if(chown("test.txt", 100, -1) == -1){ /* ���ļ����������޸ĸ�Ϊһ�����������ڵ��û� */
		perror("fail to change owner");
		exit(1);	
	}
	
	if(stat("test.txt", &statbuf) == -1){ /* �õ��ļ�״̬��Ϣ */
		perror("fail to get status");
		exit(1);	
	}
	
	printf("nonexsit owner\n");
	printf("the owner of test.txt is : %d\n", (unsigned int)statbuf.st_uid); /* ������ */
	printf("the group of test.txt is : %d\n", (unsigned int)statbuf.st_gid);
	
	return 0;	
}
