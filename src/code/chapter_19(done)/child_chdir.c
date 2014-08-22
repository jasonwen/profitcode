#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 1024

int main(void)
{
	pid_t pid;
	char buf[MAX];

	if(getcwd(buf, MAX) == NULL){ /* �õ��޸ĺ�Ĺ���Ŀ¼ */
		perror("fail to get pwd");
		exit(1);
	}

	printf("the parent��s pwd is : %s\n", buf);

	pid = fork(); /* ����һ���ӽ��� */

	if(pid == -1){
		perror("fail to fork");
		exit(1);
	}else if(pid == 0){
		printf("the child\n");

		if(chdir("/home/usr/") == -1){ /* �ı���̵Ĺ���Ŀ¼ */
			perror("fail to change dir");
			exit(1);
		}

		if(getcwd(buf, MAX) == NULL){ /* �õ��ӽ��̵Ĺ���Ŀ¼ */
			perror("fail to get pwd");
			exit(1);
		}

		printf("the child��s pwd is : %s\n", buf); /* ��ӡ�ӽ����޸ĺ�Ĺ���Ŀ¼ */
	}else{
		if(wait(NULL) == -1){ /* ���⽩ʬ���� */
			perror("fail to wait");
			exit(1);
		}

		if(getcwd(buf, MAX) == NULL){ /* �ٴεõ������̵Ĺ���Ŀ¼ */
			perror("fail to get pwd");
			exit(1);
		}

		printf("the parent��s pwd is : %s\n", buf); /* �����ʾ��Ϣ */
	}

	return 0;
}
