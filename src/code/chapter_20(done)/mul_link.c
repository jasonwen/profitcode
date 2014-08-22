#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX 1024

int main(void)
{
	int fd;
	char buf[MAX];
	int n;

if(symlink("test.txt", "sl") == -1){ /* ����һ���������ӣ�ָ��test.txt�ļ� */
		perror("fail to create symbol link");
		exit(1);
	}
	
	/* �ٴδ���һ���������ӣ�ָ��sl���ʹ��γ���һ��������������sl2->sl->test.txt
	* test.txt�ļ���Ŀ���ļ���Ҳ�Ǹ÷������������ص� 
	*/
if(symlink("sl", "sl2") == -1){ 
		perror("fail to create symbol link");
		exit(1);
	}
		
	if((fd = open("sl2", O_RDWR)) == -1){ /* �򿪵�ʵ������Ŀ���ļ�test.txt */
		perror("fail to open");
		exit(1);
	}

	printf("already create symbol-links\n");

	if((n = read(fd, buf, MAX)) == -1){ /* ���ļ������� */
		perror("fail to read");
		exit(1);
	}
	buf[n] = '\0';

	printf("file content is : %s\n", buf); /* ������*/

	strcat(buf, ", admin");

	if(write(fd, buf, strlen(buf)) == -1){ /* ����ļ�д���� */
		perror("fail to write");
		exit(1);
	}

	printf("done\n"); /* �����ʾ��Ϣ */

	close(fd);

	return 0;
}
