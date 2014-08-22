#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX 1024
#define PID 6
#define PATH_SIZE 128

int main(void)
{
	FILE *fp;
	pid_t pid;
	char pid_str[PID];
	char path[PATH_SIZE];
	char buf[MAX];

	pid = getpid(); /* �õ�����ID */
	sprintf(pid_str, "%d", pid); /* ������ID������ת��Ϊ�ַ��� */
	strcpy(path, "/proc/self/task/"); /* ƴ��·������"/proc/self/task/����ID"Ŀ¼�µ�status�ļ� */
	strcat(path, pid_str);
	strcat(path, "/status");

	fp = fopen(path, "r"); /* �򿪸��ļ�����ֻ���ķ�ʽ�� */
	if(fp == NULL){
		perror("fail to open");
		exit(1);
	}

	while(fgets(buf, MAX, fp) != NULL) /* ˳���ȡÿһ�У����Ҵ�ӡ */
		printf("%s", buf);

	fclose(fp); /* �ر��ļ� */

	return 0;
}
