#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

int main(void)
{
	DIR *dir;
	struct dirent * d_ptr;

	dir=opendir("/home/admin"); /* ��Ŀ¼ */
	if(dir == NULL){
		perror("fail to open dir");
		exit(1);
	}
	
	while((d_ptr = readdir(dir))!=NULL){ /* ˳�����Ŀ¼�е�ÿ���ļ����ļ��� */
		printf("dir name is :%s \n",d_ptr->d_name);
	}

	printf("read again\n");
	rewinddir(dir); /* Ŀ¼�ļ��Ķ�дλ�ù��� */
	
	while((d_ptr = readdir(dir))!=NULL){ /* �ٴ����ÿ���ļ� */
		printf("dir name is :%s\n",d_ptr->d_name);
	}

	closedir(dir); /* �ر�Ŀ¼ */

	return 0;
}
