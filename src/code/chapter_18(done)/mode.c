#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char * argv[])
{
	char *str;
	int i;
	struct stat buf; /* �洢�ļ�״̬��Ϣ */
	
	for(i = 1; i < argc; i++){
		printf("%s ", argv[i]);

		if(stat(argv[i], &buf) == -1){ /* �õ��ļ���״̬ */
			perror("fail to stat");
			continue;
		}

		if(S_ISREG(buf.st_mode)) /* ��ͨ�ļ� */
			printf("regular file \n");
		else if(S_ISDIR(buf.st_mode)) /* Ŀ¼�ļ� */
			printf( "directory file\n");
		else if(S_ISCHR(buf.st_mode)) /* �ַ������ļ� */
			printf( "character special file\n");
		else if(S_ISBLK(buf.st_mode)) /* �������ļ� */
			printf( "block special file\n");
		else if(S_ISFIFO(buf.st_mode)) /*�����ܵ��ļ� */
			printf( "FIFO file\n");
		else if(S_ISSOCK(buf.st_mode)) /* �׽����ļ� */
			printf( "socket file\n");
		else if(S_ISLNK(buf.st_mode)) /* ���������ļ� */
			printf( "symbolic link file\n");
		else /* δ֪���� */
			printf( "unkonw\n");
}
	
return 0;
}
