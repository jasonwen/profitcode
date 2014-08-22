#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#define MAX 1024

/* get_file_count�����Ĳ�����һ��·������ʾĿ¼���ĸ���
* �ú������ز���ָ��Ŀ¼��������ͨ�ļ�����Ŀ��
*/
int get_file_count(char *root)
{
	DIR * dir;
	struct dirent * ptr;
	int total = 0; /* �ļ����� */
	char path[MAX];
	
	dir = opendir(root); /* ��Ŀ¼ */
	if(dir == NULL){
		perror("fail to open dir");
		exit(1);
	}

	errno = 0;
	while((ptr = readdir(dir)) != NULL){ /* ˳���ȡÿһ��Ŀ¼�� */
		/* ����".."��"."����Ŀ¼ */
		if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
      		continue;
      	if(ptr->d_type == DT_DIR){ /* �����Ŀ¼����ݹ����get_file_count���� */
      		sprintf(path, "%s/%s", root, ptr->d_name);
      		total += get_file_count(path);
      	}
      	if(ptr->d_type == DT_REG) /* �������ͨ�ļ������������� */
      		total++;	
	}

	if(errno != 0){ /* ���errno��0����˵��Ŀ¼��Ŀ¼���Ѿ�ȫ������ */
		perror("fail to read dir");
		exit(1);
	}
	
	closedir(dir); /* ע��һ��Ҫ�ر�Ŀ¼ */

	return total; /* ������ͨ�ļ��� */
}

int main(int argc, char * argv[])
{
	int total;
	
	if(argc != 2){ /* �����в������� */
		printf("wrong usage\n");
		exit(1);
	}

	total = get_file_count(argv[1]); /* �õ��ļ���Ŀ */

	printf("%s has %d files\n", argv[1], total);

	return 0;
}
