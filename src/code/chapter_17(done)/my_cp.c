#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 64

/* linux cp����ļ�ʵ�֣������ʽ��cp des src
* �ɹ�����0��ʧ�ܷ���-1��ʧ��ԭ�򱣴���errno��
* argv[1] : Ŀ���ļ���des������ʹ�þ���·����
* argv[2]: Դ�ļ���src������ʹ�þ���·����
*/
int main(int argc, char* argv[])
{
	char buf[MAX];
	int in, out; /* �����ļ�������ļ� */
	int n;

	if(argc != 3)
		exit(1);

	if((in = open(argv[2], O_RDONLY)) == -1) {/* Դ�ļ���"ֻ��"�� */
		perror("fail to open");
		exit(1);
	}
	
	/* Ŀ���ļ������ļ��������򴴽������ļ������򸲸���ֻд�� */
	if((out = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT)) == -1){ 
		perror("fail to open");
		exit(1);
	}
	
	while((n = read(in, buf, MAX)) > 0) /* �����ļ� */
		if(write(out, buf, n) != n){ /* ʵ��д���ֽ���������n��д���� */
			perror("fail to write");
			exit(1);
		}
	
	if(n < 0){ /* ������� */
		perror("fail to read");
		exit(1);
	}

	printf("copy done\n"); /* �����ʾ��Ϣ */

	close(in); /* �ر������ļ� */
	close(out);

	return 0;
}
