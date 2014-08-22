#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

/* ���������룬���������û������û��������û��Ķ�Ȩ��ȫ����� */
#define READ_MASK S_IRUSR | S_IRGRP | S_IROTH
/* д�������룬���������û������û��������û���дȨ��ȫ����� */
#define WRITE_MASK S_IWUSR | S_IWGRP | S_IWOTH

int main(void)
{
	int fd;
	struct stat statbuf;

	/* ��һ���ļ���������ļ������ڣ���ʹ�ö�����������ΪȨ���ִ������ļ� */
	if((fd = open("test.txt", O_RDONLY | O_CREAT, READ_MASK)) == -1){
		perror("fail to open");
		exit(1);
	}
	
	printf("before changing model\n"); /* �����ʾ��Ϣ */
	 
	if(fstat(fd, &statbuf) == -1){ /* �ڴ򿪵��ļ��ϵõ��ļ�״̬ */
		perror("fail to get status");
		exit(1);	
	}
	
	if(statbuf.st_mode & S_IRUSR) /* �������û����ж��ļ���Ȩ�� */
		printf("user can read\n");
	if(statbuf.st_mode & S_IRGRP) /* ���û����ж��ļ���Ȩ�� */
		printf("group user can read\n");
	if(statbuf.st_mode & S_IROTH) /* �����û����ж��ļ���Ȩ�� */
		printf("other user can read\n");
	printf("\n");

	/* ʹ��д����Ȩ���ָı��ļ���Ȩ�ޣ�
* �ı���ļ��ĵ����ж�Ȩ����ʧ��
* ȡ����֮�������е�дȨ�� 
*/
	if(fchmod(fd, WRITE_MASK) == -1){
		perror("fail to change model");
		exit(1);	
	}
	
	printf("after changing model\n");
	
	if(fstat(fd, &statbuf) == -1){ /* �ٴ�ȥ�ļ���״̬ */
		perror("fail to get status");
		exit(1);	
	}
	
	printf("check the file by file-descriptor\n");

	/* ֱ��ʹ�ø��ļ���������ȡ���ļ�״̬������ļ�Ȩ���Ƿ���� */
	if(statbuf.st_mode & S_IWUSR) /* �������û�����д�ļ���Ȩ�� */
		printf("user can write\n");
	if(statbuf.st_mode & S_IWGRP) /* ���û�����д�ļ���Ȩ�� */
		printf("group user can write\n");
	if(statbuf.st_mode & S_IWOTH) /* �����û�����д�ļ���Ȩ�� */
		printf("other user can write\n");
printf("\n");
	
	/* �ٴδӴ�����ȡ�ø��ļ����ļ�״̬���������ϵ��ļ���Ȩ���Ƿ�Ҳ�Ѿ����� */
	if(stat("test.txt", &statbuf) == -1){
		perror("fail to get status"); 
		exit(1);	
	}

	printf("check the file in the disk\n");
	
	/* �����ϵ��ļ�Ȩ��Ҳ�Ѿ����� */
	if(statbuf.st_mode & S_IWUSR) /* �������û�����д�ļ���Ȩ�� */
		printf("user can write\n");
	if(statbuf.st_mode & S_IWGRP) /* ���û�����д�ļ���Ȩ�� */
		printf("group user can write\n");
	if(statbuf.st_mode & S_IWOTH) /* �����û�����д�ļ���Ȩ�� */
		printf("other user can write\n");	
	printf("\n");

	
	sleep(10); /* ����10���� */
	
	printf("done\n"); /* ��ӡ��ʾ��Ϣ */
	
	close(fd); /* �ļ��رգ����л����������ݳ�ϴ�������� */
 
	return 0;
}
