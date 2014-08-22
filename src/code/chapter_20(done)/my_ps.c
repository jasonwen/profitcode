#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  
#include <sys/stat.h>  
#include <unistd.h>  
#include <dirent.h>  
#include <fcntl.h>

#define MAX 1024
#define PATH_SIZE 128

int main(void)
{  
	DIR *dir;
    	struct dirent	*entry; 
    	FILE *fp;
	char path[PATH_SIZE];
	char buf[MAX];

	printf("NAME\tPID\n"); /* �����ͷ */

    	if((dir = opendir( "/proc" ) ) == NULL ) { /* ��/procĿ¼ */
        	perror("fail to open dir");
			return -1; 
    	}  

	while((entry = readdir( dir ) ) != NULL){  
        	if(entry->d_name[0] == '.') /* ������ǰĿ¼��procĿ¼û�и�Ŀ¼ */ 
			continue;
		/* ����ϵͳ��ϢĿ¼�����н��̵�Ŀ¼ȫ�������֣���ϵͳ��ϢĿ¼ȫ���������� */
		if( '0' <= entry->d_name[0] && entry->d_name[0] <= '9')
			continue;
			
		/* ʹ��sprintf��ɲ���·������������%s����entry->d_name��ʾ�Ľ���ID��� */
		sprintf(path, "/proc/%s/task/%s/status", entry->d_name, entry->d_name);
		
		fp = fopen(path, "r"); /* ���ļ� */
		if(fp == NULL){
			perror("fail to open");
			exit(1);
		}

		while(fgets(buf, MAX, fp) != NULL){ /* ��ȡÿһ�� */
			if(buf[0] == 'N'
 			&& buf[1] == 'a'
			&& buf[2] == 'm'
			&& buf[3] == 'e')
				printf("%s\t", &buf[5]); /* ����'\t'�����״̬��Ϣ */
			
			if(buf[0] == 'P'
 			&& buf[1] == 'i'
			&& buf[2] == 'd'){
				printf("%s\n", &buf[4]); /* ���PID��ͽ���ѭ�� */
				break;
			}
		}

		fclose(fp); /* �ر�stattus�ļ� */
	}
    	
	closedir( dir ); /* �ر�Ŀ¼ */
    
	return 0;  
}
